/**
  * @file    Delay.h 
  * @author  dongchao
  * @version V1.0.0
  * @date    2025-12-29
  * @brief   微秒/毫秒/秒级延时函数声明头文件
  *
  * @attention
	* 本代码仅作开发指导用途，旨在为开发者提供编码参考以节省开发时间。
  * 使用本代码引发的任何直接/间接损失，代码编写者不承担相关责任。
  * Copyright (c) 2025 dongchao
  */ 
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H
	
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);

#endif

/******************* (C) COPYRIGHT 2025 dongchao *****END OF FILE****/
