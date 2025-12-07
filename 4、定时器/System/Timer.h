#ifndef __TIMER_H
#define __TIMER_H

/* ----------------  timer2  -------------- */
#define TIMER2_INSTANCE               TIM2
#define TIMER2_CLK                    RCC_APB1Periph_TIM2

#define TIMER2_CLK_DIV                TIM_CKD_DIV1
#define TIMER2_COUNTER_MODE           TIM_CounterMode_Up
#define TIMER2_PERIOD                 (10000u - 1u)
#define TIMER2_PRESCALER              (7200u - 1u)
#define TIMER2_REPETITION_COUNTER     0

/* ----------------  NVIC  ---------------- */
#define TIMER2_NVIC_PRIORITY_GROUP    NVIC_PriorityGroup_2
#define TIMER2_IRQ_CHANNEL            TIM2_IRQn

/* 中断优先级 */
#define TIMER2_PREEMPTION_PRIO        2
#define TIMER2_SUB_PRIO               1


void Timer_Init(void);


#endif
