#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"                  // Device header

#define LED_PORT 	GPIOB
#define LED_CLK 	RCC_APB2Periph_GPIOB
#define LED_PIN   GPIO_Pin_13

/*
	@brief :≥ı ºªØLED PB13
*/
void Led_Init(void);

/*
	@brief :µ„¡¡LED
*/
void Led_On(void);

/*
	@brief:œ®√LED
*/
void Led_Off(void);

#endif

