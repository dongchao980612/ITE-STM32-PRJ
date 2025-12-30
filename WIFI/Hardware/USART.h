#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"                  // Device header

// 串口波特率
#define USART_INSTANCE 					USART1
#define USART1_BAUDRATE          9600
#define USART_CLK 							RCC_APB2Periph_USART1

// 串口引脚（可根据硬件修改）
#define USART1_TX_PIN            GPIO_Pin_9
#define USART1_RX_PIN            GPIO_Pin_10
#define USART1_GPIO_PORT         GPIOA
#define USART1_GPIO_CLK          RCC_APB2Periph_GPIOA



// 中断优先级配置（分组2下）
#define USART1_PREEMPT_PRIORITY  1   // 抢占优先级
#define USART1_SUB_PRIORITY      1   // 子优先级
#define USART1_MODE              (USART_Mode_Rx | USART_Mode_Tx) // 串口模式（默认收发使能）

// 其他固定配置（如需修改可改为宏）
#define USART1_PARITY            USART_Parity_No
#define USART1_STOPBITS          USART_StopBits_1
#define USART1_WORDLENGTH        USART_WordLength_8b
#define USART1_HWCONTROL         USART_HardwareFlowControl_None


void My_USART_Init(void);
void My_USART_SendByte(uint8_t Byte);
void My_USART_SendArray(uint8_t *Array, uint16_t Length);
void My_USART_SendString(char *String);
void My_USART_SendNumber(uint32_t Number, uint8_t Length);
void My_Printf(char *format, ...);

#endif

