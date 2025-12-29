/**
  * @file    main.c 
  * @author  dongchao
  * @version V1.0.0
  * @date    2025-12-29
  * @brief   GPIO输出实验， 
	*          1、点亮LED
	*          2、翻转LED
  *
  * @attention
	* 本代码仅作开发指导用途，旨在为开发者提供编码参考以节省开发时间。
  * 使用本代码引发的任何直接/间接损失，代码编写者不承担相关责任。
  * Copyright (c) 2025 dongchao
  */ 
	
#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "led.h"

int main()
{

		Led_Init();
	
    while (1)
    {
			// Led_On();
			// Delay_ms(500);
			
			// Led_Off();
			// Delay_ms(500);
			Led_Turn();
			Delay_ms(500);
			
    }
}
