#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "led.h"


void Timer_Init(void)
{
    // 开启时钟
    RCC_APB1PeriphClockCmd(TIMER2_CLK, ENABLE);

    // 配置内部时钟
    TIM_InternalClockConfig(TIMER2_INSTANCE);

    // 配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    //  时钟分频
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIMER2_CLK_DIV;
    // 计数模式
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIMER2_COUNTER_MODE;
    // 周期
    TIM_TimeBaseInitStructure.TIM_Period = TIMER2_PERIOD;
    TIM_TimeBaseInitStructure.TIM_Prescaler = TIMER2_PRESCALER;
    // 重复计数器
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = TIMER2_REPETITION_COUNTER;
    TIM_TimeBaseInit(TIMER2_INSTANCE, &TIM_TimeBaseInitStructure);

    TIM_ClearFlag(TIMER2_INSTANCE, TIM_FLAG_Update); 					// 清空更新中断标志位
    TIM_ITConfig(TIMER2_INSTANCE, TIM_IT_Update, ENABLE);


    /*NVIC中断分组*/
    NVIC_PriorityGroupConfig(TIMER2_NVIC_PRIORITY_GROUP);				//配置NVIC为分组2

    /*NVIC配置*/
    NVIC_InitTypeDef NVIC_InitStructure;																		//定义结构体变量
    NVIC_InitStructure.NVIC_IRQChannel = TIMER2_IRQ_CHANNEL;				//选择配置NVIC的TIM2_IRQn线
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;													//指定NVIC线路使能
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;								//指定NVIC线路的抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;											//指定NVIC线路的响应优先级为1
    NVIC_Init(&NVIC_InitStructure);


    //  启动定时器
    TIM_Cmd(TIMER2_INSTANCE, ENABLE);
}


uint16_t Timer2_GetCounter(void)
{
    return TIM_GetCounter(TIM2);
}




