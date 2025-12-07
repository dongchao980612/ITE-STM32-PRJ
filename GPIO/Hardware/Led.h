#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"                  // Device header


typedef enum
{
    LEDMode_OFF = 0,
    LEDMode_ON = 1,
} LEDMode_TypeDef;


#define LED_PORT 	GPIOB
#define LED_CLK 	RCC_APB2Periph_GPIOB
#define LED_PIN   GPIO_Pin_12

/*
	@brief : 初始化LED PB12
*/
void Led_Init(void);

/*
	@brief : 点亮LED
*/
void Led_On(void);

/*
	@brief : 熄灭LED
*/
void Led_Off(void);

/*
	@brief : 翻转LED
*/
void Led_Turn(void);

#endif

