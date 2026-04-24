#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"                  // Device header

/* ----------------  Timer2  -------------- */
#define TIMER_INSTANCE               TIM2
#define TIMER_CLK                    RCC_APB1Periph_TIM2

#define TIMER_COUNTER_MODE           TIM_CounterMode_Up
#define TIMER_PERIOD                 (10000u - 1u)
#define TIMER_PRESCALER              (7200u - 1u)


/* ----------------  NVIC  ---------------- */
#define TIMER_NVIC_PRIORITY_GROUP    NVIC_PriorityGroup_2
#define TIMER_IRQ_CHANNEL            TIM2_IRQn
#define TIMER_PREEMPTION_PRIO        2
#define TIMER_SUB_PRIO               1


void Timer_Init(void);


#endif
