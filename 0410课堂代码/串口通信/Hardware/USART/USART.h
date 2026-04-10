#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"                  // Device header

/* ----------------  USART1  -------------- */
#define USART_INSTANCE								USART1
#define USART_CLk											RCC_APB2Periph_USART1

#define GPIO_TX_CLK 									RCC_APB2Periph_GPIOA
#define GPIO_TX_PORT 									GPIOA
#define GPIO_TX_PIN										GPIO_Pin_9

#define GPIO_RX_CLK 									RCC_APB2Periph_GPIOA
#define GPIO_RX_PORT 									GPIOA
#define GPIO_RX_PIN										GPIO_Pin_10

void My_USART_Init(void);

#endif

