#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"                  // Device header

#define KEY_PORT 	GPIOB
#define KEY_CLK 	RCC_APB2Periph_GPIOB
#define KEY_PIN   GPIO_Pin_10

#define DELAY_INTERVAL  20

typedef enum
{
    PRESSED = 0,
    RELEASED
} KeyStatus;


void Key_Init(void);
KeyStatus Key_GetValue(void);


#endif
