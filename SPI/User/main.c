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
	


#include "stm32f10x.h"
#include "delay.h"
#include "lcd.h"

int main(void) {
    
    // 背光测试（先看背光是否正常）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    // 背光闪烁测试
    for(int i = 0; i < 3; i++) {
        GPIO_SetBits(GPIOB, GPIO_Pin_0);
        Delay_ms(300);
        GPIO_ResetBits(GPIOB, GPIO_Pin_0);
        Delay_ms(300);
    }
    GPIO_SetBits(GPIOB, GPIO_Pin_0);  // 保持背光亮

    // LCD初始化
    LCD_Init();
    Delay_ms(500);
    #if 0 
    // 测试1：显示纯色
    LCD_Clear(RED);
    Delay_ms(1000);
    
    LCD_Clear(GREEN);
    Delay_ms(1000);
    
    LCD_Clear(BLUE);
    Delay_ms(1000);
    
    LCD_Clear(WHITE);
    Delay_ms(1000);
    
    // 测试2：画对角线和边框
    LCD_Clear(BLACK);
    
    // 画边框
    for(int i = 0; i < LCD_WIDTH; i++) {
        LCD_DrawPoint(i, 0, YELLOW);
        LCD_DrawPoint(i, LCD_HEIGHT-1, YELLOW);
    }
    for(int i = 0; i < LCD_HEIGHT; i++) {
        LCD_DrawPoint(0, i, YELLOW);
        LCD_DrawPoint(LCD_WIDTH-1, i, YELLOW);
    }
    
    // 画对角线
    for(int i = 0; i < 240; i++) {
        LCD_DrawPoint(i, i, RED);
        LCD_DrawPoint(i, 239-i, BLUE);
    }
    
    Delay_ms(2000);
    
    // 测试3：显示文字
    LCD_Clear(BLACK);
    LCD_Fill(20, 20, 220, 100, CYAN);  // 蓝色背景
    
    // 显示欢迎信息
    LCD_ShowString(30, 50, "JZY-1.54 IPS", RED);
    LCD_ShowString(30, 70, "240x240 LCD", GREEN);
    LCD_ShowString(30, 90, "STM32F103", YELLOW);
    
    // 显示小方块
    for(int i = 0; i < 8; i++) {
        LCD_Fill(30+i*25, 150, 50+i*25, 170, MAGENTA);
        Delay_ms(200);
    }
    #endif 
    while(1) {
        // 呼吸灯效果
        for(int i = 0; i < 240; i += 10) {
            LCD_Fill(i, 200, i+8, 230, WHITE);
            Delay_ms(50);
        }
        for(int i = 240; i > 0; i -= 10) {
            LCD_Fill(i-8, 200, i, 230, BLACK);
            Delay_ms(50);
        }
    }
}
