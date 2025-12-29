## 开发环境
- 实验器材：STM32F103C8T6开发板

- 芯片版本：STM32F103C8T6

- Keil版本：5.24

- 外设库版本：STM32F10x_StdPeriph_Lib_V3.5.0

- 启动文件：startup_stm32f10x_md.s

## 总览
|  章节   | 文件夹  | 完成时间|
|  ----  | ----  |  ---- |
| 工程模板  | 00Template |  2025-12-29 |
| 输出  | 02GPIO | 2025-12-29 |
| 输入  |  |    |
| OLED显示  |  |  |
| 普通定时器  |  |   |
| 通用定时器  |  |   |
| 串口  |  |   |
| IIC  |  |   |
| ADC  |  |   |
| DMA  |  |   |
## 实验  
###  模板文件 00Template

### 实验一：GPIO输出 01GPIO

```c
// LED.H
/**
  * @file    LED.h 
  * @author  dongchao
  * @version V1.0.0
  * @date    2025-12-29
  * @brief   LED操作函数声明头文件
  *
  * @attention
	* 本代码仅作开发指导用途，旨在为开发者提供编码参考以节省开发时间。
  * 使用本代码引发的任何直接/间接损失，代码编写者不承担相关责任。
  * Copyright (c) 2025 dongchao
  */ 
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h" 


typedef enum
{
    LEDMode_OFF = 0,
    LEDMode_ON = 1,
} LEDMode_TypeDef;


#define LED_PORT 	GPIOB
#define LED_CLK 	RCC_APB2Periph_GPIOB
#define LED_PIN   GPIO_Pin_12


void Led_Init(void);
void Led_On(void);
void Led_Off(void);
void Led_Turn(void);

#endif

/******************* (C) COPYRIGHT 2025 dongchao *****END OF FILE****/

```