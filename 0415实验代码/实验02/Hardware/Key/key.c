#include "key.h"


// 全局按键检测状态
static KeyStatus key_status = RELEASED;

void Key_Init(void)
{
    // 步骤1：开启GPIO时钟
    RCC_APB2PeriphClockCmd(KEY_CLK | KEY_GPIO_PORTSOURCE, ENABLE);

    // 步骤2：配置GPIO模式
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin =  KEY_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//  上拉输入模式

    GPIO_Init(KEY_PORT, &GPIO_InitStructure);

    // 步骤3：映射中断引脚 PB10 → EXTI10
    GPIO_EXTILineConfig(KEY_GPIO_PORTSOURCE, KEY_GPIO_PINSOURCE);

    // 步骤4：配置中断
    EXTI_InitTypeDef EXTI_InitStruct;

    // 中断分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    EXTI_InitStruct.EXTI_Line = KEY_EXTI_LINE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // 双边沿
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    // 步骤5：配置中断优先级
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = KEY_EXTI_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);


}

KeyStatus Key_GetValue(void)
{
	return key_status;
}

// EXTI10~15 共用一个中断
void EXTI15_10_IRQHandler(void)
{
	// 1. 检查中断标志位（确认触发）
    if(EXTI_GetITStatus(KEY_EXTI_LINE) != RESET)
    {
        // 2. 读取硬件状态，更新检测状态
        if((KeyStatus)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == PRESSED)
        {
					key_status = PRESSED;
  
        }
        else
        {
					key_status = RELEASED;

        }

        // 3. 清除中断标志
        EXTI_ClearITPendingBit(KEY_EXTI_LINE);
    }
}
