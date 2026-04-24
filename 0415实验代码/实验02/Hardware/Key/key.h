#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"                  // Device header

#define KEY_PORT 	GPIOB
#define KEY_CLK 	RCC_APB2Periph_GPIOB
#define KEY_PIN   GPIO_Pin_10

#define KEY_EXTI_LINE      EXTI_Line10
#define KEY_GPIO_PORTSOURCE GPIO_PortSourceGPIOB
#define KEY_GPIO_PINSOURCE GPIO_PinSource10
#define KEY_EXTI_IRQn      EXTI15_10_IRQn

typedef enum
{
    PRESSED = 0,
    RELEASED
} KeyStatus;


void Key_Init(void);
KeyStatus Key_GetValue(void);


#endif
