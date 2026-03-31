#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "led.h"


void Timer_Init(void)
{
    // 开启时钟
    RCC_APB1PeriphClockCmd(TIMER_CLK, ENABLE);

    // 配置内部时钟
    TIM_InternalClockConfig(TIMER_INSTANCE);

    // 配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    // 计数模式
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIMER_COUNTER_MODE;
    // 周期
    TIM_TimeBaseInitStructure.TIM_Period = TIMER_PERIOD;
    TIM_TimeBaseInitStructure.TIM_Prescaler = TIMER_PRESCALER;

    TIM_TimeBaseInit(TIMER_INSTANCE, &TIM_TimeBaseInitStructure);

    TIM_ClearFlag(TIMER_INSTANCE, TIM_FLAG_Update); 					// 清空更新中断标志位
    TIM_ITConfig(TIMER_INSTANCE, TIM_IT_Update, ENABLE);


    /*NVIC中断分组*/
    NVIC_PriorityGroupConfig(TIMER_NVIC_PRIORITY_GROUP);				//配置NVIC为分组2

    /*NVIC配置*/
    NVIC_InitTypeDef NVIC_InitStructure;																		//定义结构体变量
    NVIC_InitStructure.NVIC_IRQChannel = TIMER_IRQ_CHANNEL;				//选择配置NVIC的TIM2_IRQn线
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;													//指定NVIC线路使能
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;								//指定NVIC线路的抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;											//指定NVIC线路的响应优先级为1
    NVIC_Init(&NVIC_InitStructure);


    //  启动定时器
    TIM_Cmd(TIMER_INSTANCE, ENABLE);
}





