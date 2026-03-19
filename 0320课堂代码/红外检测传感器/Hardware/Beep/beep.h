#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"                  // Device header

#define BEEP_PORT 	GPIOB
#define BEEP_CLK 		RCC_APB2Periph_GPIOB
#define BEEP_PIN   	GPIO_Pin_9


void Beep_Init(void);
void Beep_On(void);
void Beep_Off(void);

#endif
