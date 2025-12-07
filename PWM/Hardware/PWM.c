#include "stm32f10x.h"                  // Device header
#include "pwm.h"


/*
	@brief : 初始化PWM
*/
void PWM_Init(void)
{
    //  开 GPIOA 时钟(APB2) 与 TIM2 时钟(APB1)
    RCC_APB2PeriphClockCmd(PWM_PORT_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(PWM_TIMER2_CLK, ENABLE);


    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
    GPIO_InitStructure.GPIO_Pin = PWM_PIN;		//或者 GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(PWM_PORT_GPIO, &GPIO_InitStructure);


    /* 3. 让 TIM2 使用内部时钟(默认即可，显性写出可读性好) */
    TIM_InternalClockConfig(PWM_TIMER2_INSTANCE);


    // 定时器初始化
    TIM_InternalClockConfig(PWM_TIMER2_INSTANCE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = PWM_TIMER2_CLKDIV;  //采样分频=1 
    TIM_TimeBaseInitStructure.TIM_CounterMode = PWM_TIMER2_CNTMODE;  // 向上计数
    TIM_TimeBaseInitStructure.TIM_Period = PWM_TIMER2_PERIOD;  //  ARR = 99
    TIM_TimeBaseInitStructure.TIM_Prescaler = PWM_TIMER2_PRESCALER;  //   PSC = 
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = PWM_REP;
    TIM_TimeBaseInit(PWM_TIMER2_INSTANCE, &TIM_TimeBaseInitStructure);

		// 输出比较单元,决定占空比模式
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure); //初始化其他未配置的结构体成员

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //输出比较模式
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出比较极性
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //  基本/通用定时器无效，写 0
    TIM_OCInitStructure.TIM_Pulse = PWM_PULSE;		// CCR

    TIM_OC1Init(PWM_TIMER2_INSTANCE, &TIM_OCInitStructure);  //  3


    TIM_Cmd(PWM_TIMER2_INSTANCE, ENABLE);
}

/*
	@brief : 动态修改占空比
*/
void PWM_SetCompare1(uint16_t Compare)
{
    TIM_SetCompare1(PWM_TIMER2_INSTANCE, Compare);
}
