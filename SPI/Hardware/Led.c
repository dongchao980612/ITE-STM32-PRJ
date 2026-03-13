/**
	* @file    LED.h 
  * @author  dongchao
  * @version V1.0.0
  * @date    2025-12-29
  * @brief   LED操作函数实现文件
  *
  * @attention
	* 本代码仅作开发指导用途，旨在为开发者提供编码参考以节省开发时间。
  * 使用本代码引发的任何直接/间接损失，代码编写者不承担相关责任。
  * Copyright (c) 2025 dongchao
  */ 

/* Includes ------------------------------------------------------------------*/
#include "led.h"

/**
  * @brief  初始化LED PB12
  * @param  无
  * @retval 无
  */
void Led_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(LED_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin =  LED_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

/**
  * @brief  点亮LED
  * @param  无
  * @retval 无
  */
void Led_On(void)
{
    GPIO_SetBits(LED_PORT, LED_PIN);
}

/**
  * @brief  关闭LED
  * @param  无
  * @retval 无
  */
void Led_Off(void)
{
    GPIO_ResetBits(LED_PORT, LED_PIN);
}

/**
  * @brief  翻转LED
  * @param  无
  * @retval 无
  */
void Led_Turn()
{
    if(GPIO_ReadOutputDataBit(LED_PORT, LED_PIN) == LEDMode_ON)
    {
        Led_Off();
    }
    else
    {
        Led_On();
    }
}

/******************* (C) COPYRIGHT 2025 dongchao *****END OF FILE****/
