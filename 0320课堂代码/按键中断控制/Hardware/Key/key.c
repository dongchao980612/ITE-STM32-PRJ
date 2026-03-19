#include "key.h"
#include "delay.h"

static KeyStatus key_status = RELEASED;

void Key_Init(void)
{
    // 步骤1：开启GPIOB时钟
    RCC_APB2PeriphClockCmd(KEY_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(KEY_AFIO_CLK, ENABLE);
    // 开启AFIO的时钟，外部中断必须开启AFIO的时钟



    // 步骤2：配置GPIO模式
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin =  KEY_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//  上拉输入模式

    GPIO_Init(KEY_PORT, &GPIO_InitStructure);


    // 步骤2： AFIO选择中断引脚 PB11
    GPIO_EXTILineConfig(KEY_AFIO_PORT, KEY_AFIO_PIN);//将外部中断的11号线映射到GPIOB，即选择PD11为外部中断引脚

    // 步骤3： EXTI初始化
    EXTI_InitTypeDef EXTI_InitStructure;						//定义结构体变量
    EXTI_InitStructure.EXTI_Line = KEY_EXIT_LINE;					//选择配置外部中断的1号线
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;		//指定外部中断线为上、下降沿触发
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//指定外部中断线为中断模式

    EXTI_InitStructure.EXTI_LineCmd = ENABLE;  // 必须在EXTI_Init前设置
    EXTI_Init(&EXTI_InitStructure);								//将结构体变量交给EXTI_Init，配置EXTI外设

    // 步骤4： NVIC中断分组
    NVIC_PriorityGroupConfig(KEY_NVIC_GROUP);				//配置NVIC为分组2


    // 步骤5： NVIC配置
    NVIC_InitTypeDef NVIC_InitStructure;						//定义结构体变量
    NVIC_InitStructure.NVIC_IRQChannel = KEY_EXIT_IQRN;		//选择配置NVIC的EXTI11线

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//指定NVIC线路的抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//指定NVIC线路的响应优先级为1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能

    NVIC_Init(&NVIC_InitStructure);								//将结构体变量交给NVIC_Init，配置NVIC外设
}

KeyStatus Key_GetValue(void)
{
    KeyStatus key_status = RELEASED;

    key_status = (KeyStatus)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN);

    if(key_status == PRESSED)
    {
        Delay_ms(DELAY_INTERVAL);
        key_status = (KeyStatus)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN);

        if(key_status == PRESSED)
        {
            return PRESSED;
        }
    }

    return key_status;
}

KeyStatus Get_Key_Status(void)
{
    return key_status;
}

void EXTI15_10_IRQHandler(void)
{

    if (EXTI_GetITStatus(KEY_EXIT_LINE) == SET)        // 判断是否是外部中断1号线触发的中断
    {
        // 软件消抖（避免抖动导致多次更新）
        Delay_ms(DELAY_INTERVAL);
        
  
        key_status = (KeyStatus)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN);
        
        // 清除中断标志位
        EXTI_ClearITPendingBit(KEY_EXIT_LINE);

    }
}
