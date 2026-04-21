#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"

//==================== SPI Òý½Å¶¨Òå£¨SPI1£©====================
#define SPI_INSTANCE            SPI1 
#define SPI_RCC                 RCC_APB2Periph_SPI1

#define SPI_SCK_PIN             GPIO_Pin_5
#define SPI_SCK_PORT            GPIOA
#define SPI_SCK_RCC             RCC_APB2Periph_GPIOA

#define SPI_MOSI_PIN            GPIO_Pin_7
#define SPI_MOSI_PORT           GPIOA
#define SPI_MOSI_RCC            RCC_APB2Periph_GPIOA

#define SPI_MISO_PIN            GPIO_Pin_6
#define SPI_MISO_PORT           GPIOA
#define SPI_MISO_RCC            RCC_APB2Periph_GPIOA


void SPI1_Init(void);
uint8_t SPI1_ReadWriteByte(uint8_t data);

#endif

