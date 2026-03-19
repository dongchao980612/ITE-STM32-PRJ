#ifndef __COUNTER_H
#define __COUNTER_H

#include "stm32f10x.h"                  // Device header

/* GPIO */
#define COUNTER_PORT 	GPIOB
#define COUNTER_CLK 	RCC_APB2Periph_GPIOB
#define COUNTER_PIN   GPIO_Pin_11

/* AFIO */
#define COUNTER_AFIO_PORT   GPIO_PortSourceGPIOB
#define COUNTER_AFIO_CLK    RCC_APB2Periph_AFIO
#define COUNTER_AFIO_PIN    GPIO_PinSource11

/* EXIT */
#define COUNTER_EXIT_LINE    EXTI_Line11

/* NVIC */
#define COUNTER_NVIC_GROUP     NVIC_PriorityGroup_2
#define COUNTER_EXIT_IQRN     EXTI15_10_IRQn


typedef enum
{
    NO_PERSON = 0,  // 无人
    PERSON = 1 // 有人
} PersonStatus;


#define DETECT_DELAY  20  // 消抖延时（ms）


void Counter_Init(void);                // 红外检测初始化
PersonStatus Get_Person_Status(void);   // 获取人体检测状态


#endif

