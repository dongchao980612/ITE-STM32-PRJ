/**
  * @file    Delay.c
  * @author  dongchao
  * @version V1.0.0
  * @date    2025-12-29
  * @brief   微秒/毫秒/秒级延时函数实现文件
  *
  * @attention
	* 本代码仅作开发指导用途，旨在为开发者提供编码参考以节省开发时间。
  * 使用本代码引发的任何直接/间接损失，代码编写者不承担相关责任。
  * Copyright (c) 2025 dongchao
  */

/* Includes ------------------------------------------------------------------*/
#include "delay.h"

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
    SysTick->LOAD = 72 * xus;				//设置定时器重装值
    SysTick->VAL = 0x00;					//清空当前计数值
    SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器

    while(!(SysTick->CTRL & 0x00010000));	//等待计数到0

    SysTick->CTRL = 0x00000004;				//关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
    while(xms--)
    {
        Delay_us(1000);
    }
}

/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
    while(xs--)
    {
        Delay_ms(1000);
    }
}


/******************* (C) COPYRIGHT 2025 dongchao *****END OF FILE****/
