#ifndef __LCD_H
#define __LCD_H

#include "stm32f10x.h"

// 屏幕参数（ST7789 240×240）
#define LCD_WIDTH  240
#define LCD_HEIGHT 240

// JZY-1.54 IPS 引脚定义（根据您的丝印）
#define LCD_SCL_PIN    GPIO_Pin_5    // 丝印"SCL" = SPI_SCK
#define LCD_SCL_PORT   GPIOA

#define LCD_SDA_PIN    GPIO_Pin_7    // 丝印"SDA" = SPI_MOSI（必须用PA7！）
#define LCD_SDA_PORT   GPIOA

#define LCD_DC_PIN     GPIO_Pin_4    // 丝印"DC"
#define LCD_DC_PORT    GPIOA

#define LCD_RES_PIN    GPIO_Pin_6    // 丝印"RES"（原代码PA7改为PA6）
#define LCD_RES_PORT   GPIOA

#define LCD_CS_PIN     GPIO_Pin_3    // 丝印"CS"
#define LCD_CS_PORT    GPIOA

#define LCD_BL_PIN     GPIO_Pin_0    // 丝印"BLK"
#define LCD_BL_PORT    GPIOB

// 快速引脚操作
#define LCD_DC_H()     GPIO_SetBits(LCD_DC_PORT, LCD_DC_PIN)
#define LCD_DC_L()     GPIO_ResetBits(LCD_DC_PORT, LCD_DC_PIN)

#define LCD_RES_H()    GPIO_SetBits(LCD_RES_PORT, LCD_RES_PIN)
#define LCD_RES_L()    GPIO_ResetBits(LCD_RES_PORT, LCD_RES_PIN)

#define LCD_BL_H()     GPIO_SetBits(LCD_BL_PORT, LCD_BL_PIN)
#define LCD_BL_L()     GPIO_ResetBits(LCD_BL_PORT, LCD_BL_PIN)

#define LCD_CS_H()     GPIO_SetBits(LCD_CS_PORT, LCD_CS_PIN)
#define LCD_CS_L()     GPIO_ResetBits(LCD_CS_PORT, LCD_CS_PIN)

// 颜色定义（RGB565）
#define WHITE         0xFFFF
#define BLACK         0x0000
#define RED           0xF800
#define GREEN         0x07E0
#define BLUE          0x001F
#define YELLOW        0xFFE0
#define MAGENTA       0xF81F
#define CYAN          0x07FF

// 函数声明
void LCD_Init(void);
void LCD_Reset(void);
void LCD_Clear(uint16_t Color);
void LCD_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_ShowChar(uint16_t x, uint16_t y, char ch, uint16_t color);
void LCD_ShowString(uint16_t x, uint16_t y, const char *str, uint16_t color);
void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint16_t color);
void LCD_SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_WriteReg(uint8_t reg);
void LCD_WriteData(uint8_t data);
void LCD_WriteData16(uint16_t data);
uint32_t LCD_Pow(uint8_t m, uint8_t n);

void SPI1_Init(void);
void SPI1_SendByte(uint8_t data);

#endif

