#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"                  // Device header

#define LED_PORT 	GPIOC
#define LED_CLK 	RCC_APB2Periph_GPIOC
#define LED_PIN   GPIO_Pin_3


void Led_Init(void);
void Led_On(void);
void Led_Off(void);

#endif
