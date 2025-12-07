#ifndef __PWM_H
#define __PWM_H

/*-------------  GPIO  -------------*/
#define PWM_PORT_GPIO         GPIOA
#define PWM_PORT_CLK          RCC_APB2Periph_GPIOA
#define PWM_PIN               GPIO_Pin_0

/*-------------  TIM2  -------------*/
#define PWM_TIMER2_INSTANCE      TIM2
#define PWM_TIMER2_CLK           RCC_APB1Periph_TIM2

#define PWM_TIMER2_CLKDIV        TIM_CKD_DIV1
#define PWM_TIMER2_CNTMODE       TIM_CounterMode_Up
#define PWM_TIMER2_PERIOD					(200u - 1u)
#define PWM_TIMER2_PRESCALER      (360u - 1u)

#define PWM_REP               0
#define PWM_PULSE             0             /* 初始占空比 0 % */



/*
	@brief : 初始化PWM
*/
void PWM_Init(void);


/*
	@brief : 动态修改占空比
*/
void PWM_SetCompare1(uint16_t Compare);


#endif

