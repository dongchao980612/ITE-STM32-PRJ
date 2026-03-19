#include "counter.h"
#include "delay.h"

// 全局人体检测状态
static PersonStatus person_status = NO_PERSON;

void Counter_Init(void)
{
    // 步骤1：开启时钟（GPIOB + AFIO）
    RCC_APB2PeriphClockCmd(COUNTER_CLK | COUNTER_AFIO_CLK, ENABLE);

    // 步骤2：配置GPIO为上拉输入
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = COUNTER_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入，默认高电平（无人）
    GPIO_Init(COUNTER_PORT, &GPIO_InitStructure);

    // 步骤3：AFIO映射 - PB11关联到EXTI11线
    GPIO_EXTILineConfig(COUNTER_AFIO_PORT, COUNTER_AFIO_PIN);

    // 步骤4：配置EXTI中断线（核心：下降沿触发）
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = COUNTER_EXIT_LINE;          
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; // 来人=下降沿，没人=上升沿
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;             // 中断模式
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                       // 使能中断线
    EXTI_Init(&EXTI_InitStructure);

    // 步骤5：配置NVIC中断优先级
    NVIC_PriorityGroupConfig(COUNTER_NVIC_GROUP);  // 全局优先级分组
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = COUNTER_EXIT_IQRN;          // EXTI15_10通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;        // 抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;               // 响应优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                   // 使能中断通道
    NVIC_Init(&NVIC_InitStructure);
}

// 获取人体检测状态（供主函数调用）
PersonStatus Get_Person_Status(void)
{
    return person_status;
}

// EXTI15_10中断服务函数（PB11属于此通道）
void EXTI15_10_IRQHandler(void)
{
    // 1. 检查中断标志位（确认是EXTI11触发）
    if (EXTI_GetITStatus(COUNTER_EXIT_LINE) == SET)
    {
        // 2. 软件消抖（避免传感器抖动导致误触发）
        Delay_ms(DETECT_DELAY);
        
        // 3. 读取硬件状态，更新人体检测状态
        if (GPIO_ReadInputDataBit(COUNTER_PORT, COUNTER_PIN) == 1)
        {
            // 高电平 = 有人
            person_status = PERSON;
        }
        else
        {
            // 低电平 = 无人
            person_status = NO_PERSON;
        }
        
        // 4. 必须清除中断标志位（否则反复进入中断）
        EXTI_ClearITPendingBit(COUNTER_EXIT_LINE);
    }
}

