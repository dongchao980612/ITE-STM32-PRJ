#ifndef __WIFI_H
#define __WIFI_H

#include "stm32f10x.h"                  // Device header

// 1. 串口基础配置
#define WIFI_USART                USART2                  // WIFI使用的串口外设
#define WIFI_USART_CLK            RCC_APB1Periph_USART2   // WIFI串口时钟（USART2挂APB1）
#define WIFI_USART_BAUDRATE       115200    // WIFI串口波特率




// 2. GPIO引脚配置
#define WIFI_GPIO_PORT            GPIOA                   // WIFI串口GPIO端口
#define WIFI_GPIO_CLK             RCC_APB2Periph_GPIOA    // WIFI GPIO时钟
#define WIFI_TX_PIN               GPIO_Pin_2              // WIFI_TX引脚（PA2）
#define WIFI_RX_PIN               GPIO_Pin_3              // WIFI_RX引脚（PA3）

#define WIFI_USART_WORDLENGTH     USART_WordLength_8b     // 字长：8位
#define WIFI_USART_STOPBITS       USART_StopBits_1        // 停止位：1位
#define WIFI_USART_PARITY         USART_Parity_No         // 校验位：无
#define WIFI_USART_HWCONTROL      USART_HardwareFlowControl_None // 硬件流控：无
#define WIFI_USART_MODE           (USART_Mode_Tx | USART_Mode_Rx) // 模式：收发使能


// 3. 中断配置
#define WIFI_USART_IRQn           USART2_IRQn            // WIFI串口中断通道
#define WIFI_IRQ_PREEMPT_PRIORITY 2                      // 抢占优先级
#define WIFI_IRQ_SUB_PRIORITY     1                      // 子优先级
#define WIFI_USART_IT_TYPE        (USART_IT_RXNE | USART_IT_IDLE) // 使能的中断类型（接收+空闲）

void My_WIFI_Init(void);
void My_WIFI_SendByte(uint8_t Byte);
void My_WIFI_SendString(uint8_t *Array, uint16_t Length);

#endif

