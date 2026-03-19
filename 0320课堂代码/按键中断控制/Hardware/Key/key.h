#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"                  // Device header

/* GPIO */
#define KEY_PORT 	GPIOB
#define KEY_CLK 	RCC_APB2Periph_GPIOB
#define KEY_PIN   GPIO_Pin_11

/* AFIO */
#define KEY_AFIO_PORT   GPIO_PortSourceGPIOB
#define KEY_AFIO_CLK    RCC_APB2Periph_AFIO
#define KEY_AFIO_PIN    GPIO_PinSource11

/* EXIT */
#define KEY_EXIT_LINE    EXTI_Line11

/* NVIC */
#define KEY_NVIC_GROUP     NVIC_PriorityGroup_2
#define KEY_EXIT_IQRN     EXTI15_10_IRQn
		
		
#define DELAY_INTERVAL  20

typedef enum
{
    PRESSED = 0,
    RELEASED
} KeyStatus;



void Key_Init(void);

KeyStatus Key_GetValue(void);
KeyStatus Get_Key_Status(void);


#endif
