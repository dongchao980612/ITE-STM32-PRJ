#include "lcd.h"
#include "delay.h"
#include "font.h"  // 需要字体文件

// SPI初始化
void SPI1_Init(void) {
    SPI_InitTypeDef SPI_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;
    
    // 使能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_SPI1, ENABLE);
    
    // 配置SPI引脚：SCK(PA5) 和 MOSI(PA7)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // 配置控制引脚：DC, RES, CS
    GPIO_InitStruct.GPIO_Pin = LCD_DC_PIN | LCD_RES_PIN | LCD_CS_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // 配置背光引脚
    GPIO_InitStruct.GPIO_Pin = LCD_BL_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_BL_PORT, &GPIO_InitStruct);
    
    // SPI配置
    SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx;  // 单线发送
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;      // 时钟空闲低电平
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;    // 第一个边沿采样
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;  // 36MHz
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init(SPI1, &SPI_InitStruct);
    
    SPI_Cmd(SPI1, ENABLE);
    
    // 初始状态
    LCD_CS_H();   // 片选拉高（不选中）
    LCD_DC_H();   // 数据模式
    LCD_BL_L();   // 背光关闭
    LCD_RES_H();  // 复位拉高
}

// SPI发送一个字节
void SPI1_SendByte(uint8_t data) {
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, data);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    SPI_I2S_ReceiveData(SPI1);
}

// 写寄存器命令
void LCD_WriteReg(uint8_t reg) {
	LCD_CS_L();
    LCD_DC_L();  // 命令模式
    SPI1_SendByte(reg);
	LCD_CS_H();
}

// 写数据
void LCD_WriteData(uint8_t data) {
	LCD_CS_L();
    LCD_DC_H();  // 数据模式
    SPI1_SendByte(data);
	LCD_CS_H();
}

// 写16位数据
void LCD_WriteData16(uint16_t data) {
    LCD_DC_H();
    SPI1_SendByte(data >> 8);
    SPI1_SendByte(data & 0xFF);
}

// 硬件复位
void LCD_Reset(void) {
    LCD_RES_L();
    Delay_ms(100);
    LCD_RES_H();
    Delay_ms(100);
}

// 设置显示窗口
void LCD_SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    LCD_WriteReg(0x2A);  // 列地址设置
    LCD_WriteData(x1 >> 8);
    LCD_WriteData(x1 & 0xFF);
    LCD_WriteData(x2 >> 8);
    LCD_WriteData(x2 & 0xFF);
    
    LCD_WriteReg(0x2B);  // 行地址设置
    LCD_WriteData(y1 >> 8);
    LCD_WriteData(y1 & 0xFF);
    LCD_WriteData(y2 >> 8);
    LCD_WriteData(y2 & 0xFF);
    
    LCD_WriteReg(0x2C);  // 开始写GRAM
}

// JZY-1.54 IPS 初始化序列（ST7789V3）
void LCD_Init(void) {
    SPI1_Init();

    LCD_Reset();  // 硬件复位
    // 必须的延时
    Delay_ms(120);
  	
 
    // ST7789V3初始化命令序列
    LCD_WriteReg(0x11);  // 退出睡眠模式
    Delay_ms(120);
 	#if 0    
    LCD_WriteReg(0x36);  // 内存数据访问控制
    LCD_WriteData(0x00); // 正常竖屏模式
    
    LCD_WriteReg(0x3A);  // 像素格式设置
    LCD_WriteData(0x05); // 16位RGB565
    
    LCD_WriteReg(0xB2);  // 端口配置
    LCD_WriteData(0x0C);
    LCD_WriteData(0x0C);
    LCD_WriteData(0x00);
    LCD_WriteData(0x33);
    LCD_WriteData(0x33);
    
    LCD_WriteReg(0xB7);  // 门控制
    LCD_WriteData(0x35);
    
    LCD_WriteReg(0xBB);  // VCOM设置
    LCD_WriteData(0x19);
    
    LCD_WriteReg(0xC0);  // LCM控制
    LCD_WriteData(0x2C);
    
    LCD_WriteReg(0xC2);  // VDV和VRH命令使能
    LCD_WriteData(0x01);
    
    LCD_WriteReg(0xC3);  // VRH设置
    LCD_WriteData(0x12);
    
    LCD_WriteReg(0xC4);  // VDV设置
    LCD_WriteData(0x20);
    
    LCD_WriteReg(0xC6);  // 帧率控制
    LCD_WriteData(0x0F);
    
    LCD_WriteReg(0xD0);  // 电源控制
    LCD_WriteData(0xA4);
    LCD_WriteData(0xA1);
    
    LCD_WriteReg(0xE0);  // 正极伽马校正
    LCD_WriteData(0xD0);
    LCD_WriteData(0x04);
    LCD_WriteData(0x0D);
    LCD_WriteData(0x11);
    LCD_WriteData(0x13);
    LCD_WriteData(0x2B);
    LCD_WriteData(0x3F);
    LCD_WriteData(0x54);
    LCD_WriteData(0x4C);
    LCD_WriteData(0x18);
    LCD_WriteData(0x0D);
    LCD_WriteData(0x0B);
    LCD_WriteData(0x1F);
    LCD_WriteData(0x23);
    
    LCD_WriteReg(0xE1);  // 负极伽马校正
    LCD_WriteData(0xD0);
    LCD_WriteData(0x04);
    LCD_WriteData(0x0C);
    LCD_WriteData(0x11);
    LCD_WriteData(0x13);
    LCD_WriteData(0x2C);
    LCD_WriteData(0x3F);
    LCD_WriteData(0x44);
    LCD_WriteData(0x51);
    LCD_WriteData(0x2F);
    LCD_WriteData(0x1F);
    LCD_WriteData(0x1F);
    LCD_WriteData(0x20);
    LCD_WriteData(0x23);
    
    LCD_WriteReg(0x21);  // 显示反转开
    LCD_WriteReg(0x29);  // 显示开
    
    Delay_ms(100);
    #endif 
    // 打开背光
    LCD_BL_H();
    
    // 清屏
    LCD_Clear(BLACK);
}

// 清屏
void LCD_Clear(uint16_t color) {
    uint32_t i;
    LCD_SetWindow(0, 0, LCD_WIDTH-1, LCD_HEIGHT-1);
    
    LCD_CS_L();  // 选中设备
    
    for(i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++) {
        LCD_WriteData16(color);
    }
    
    LCD_CS_H();  // 释放设备
}

// 画点
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color) {
    if(x >= LCD_WIDTH || y >= LCD_HEIGHT) return;
    
    LCD_SetWindow(x, y, x, y);
    LCD_WriteData16(color);
}

// 填充矩形
void LCD_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    uint32_t i, j;
    
    if(x1 >= LCD_WIDTH) x1 = LCD_WIDTH - 1;
    if(x2 >= LCD_WIDTH) x2 = LCD_WIDTH - 1;
    if(y1 >= LCD_HEIGHT) y1 = LCD_HEIGHT - 1;
    if(y2 >= LCD_HEIGHT) y2 = LCD_HEIGHT - 1;
    
    LCD_SetWindow(x1, y1, x2, y2);
    
    LCD_CS_L();
    for(i = y1; i <= y2; i++) {
        for(j = x1; j <= x2; j++) {
            LCD_WriteData16(color);
        }
    }
    LCD_CS_H();
}


// 显示单个字符(8x16)
void LCD_ShowChar(uint16_t x, uint16_t y, char ch, uint16_t color) {
    uint8_t i, j;
    const uint8_t* font_data;
    
    // 获取字符点阵数据
    font_data = Font_GetChar((uint8_t)ch);
    
    // 逐行逐列绘制
    for(i = 0; i < FONT_HEIGHT; i++) {           // 16行
        uint8_t line = font_data[i];            // 获取一行数据
        for(j = 0; j < FONT_WIDTH; j++) {        // 8列
            if(line & (0x80 >> j)) {            // 判断该点是否需要点亮
                LCD_DrawPoint(x + j, y + i, color);
            } else {
                // 如果需要背景色，可以在这里设置背景色
                // LCD_DrawPoint(x + j, y + i, bg_color);
            }
        }
    }
}

// 显示字符串(8x16字体)
void LCD_ShowString(uint16_t x, uint16_t y, const char *str, uint16_t color) {
    uint16_t x_pos = x;
    
    while(*str != '\0') {
        // 如果到达屏幕右侧，换行（简单处理）
        if(x_pos > LCD_WIDTH - FONT_WIDTH) {
            x_pos = x;
            y += FONT_HEIGHT;
            
            // 如果到达屏幕底部，停止显示
            if(y > LCD_HEIGHT - FONT_HEIGHT) {
                break;
            }
        }
        
        // 显示当前字符
        LCD_ShowChar(x_pos, y, *str, color);
        
        // 移动到下一个字符位置
        x_pos += FONT_WIDTH;
        
        // 指向下一个字符
        str++;
    }
}

// 带背景色的字符显示
void LCD_ShowCharWithBg(uint16_t x, uint16_t y, char ch, uint16_t color, uint16_t bg_color) {
    uint8_t i, j;
    const uint8_t* font_data;
    
    font_data = Font_GetChar((uint8_t)ch);
    
    for(i = 0; i < FONT_HEIGHT; i++) {
        uint8_t line = font_data[i];
        for(j = 0; j < FONT_WIDTH; j++) {
            if(line & (0x80 >> j)) {
                LCD_DrawPoint(x + j, y + i, color);      // 前景色
            } else {
                LCD_DrawPoint(x + j, y + i, bg_color);   // 背景色
            }
        }
    }
}

// 带背景色的字符串显示
void LCD_ShowStringWithBg(uint16_t x, uint16_t y, const char *str, uint16_t color, uint16_t bg_color) {
    uint16_t x_pos = x;
    
    while(*str != '\0') {
        if(x_pos > LCD_WIDTH - FONT_WIDTH) {
            x_pos = x;
            y += FONT_HEIGHT;
            if(y > LCD_HEIGHT - FONT_HEIGHT) break;
        }
        
        LCD_ShowCharWithBg(x_pos, y, *str, color, bg_color);
        x_pos += FONT_WIDTH;
        str++;
    }
}

// 显示数字（十进制）
void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint16_t color) {
    uint8_t t, temp;
    uint8_t enshow = 0;
    char buffer[12];
    
    // 将数字转换为字符串
    for(t = 0; t < len; t++) {
        temp = (num / LCD_Pow(10, len - t - 1)) % 10;
        if(enshow == 0 && t < (len - 1)) {
            if(temp == 0) {
                buffer[t] = ' ';
                continue;
            } else {
                enshow = 1;
            }
        }
        buffer[t] = temp + '0';
    }
    buffer[len] = '\0';
    
    LCD_ShowString(x, y, buffer, color);
}

// 计算10的幂（用于显示数字）
uint32_t LCD_Pow(uint8_t m, uint8_t n) {
    uint32_t result = 1;
    while(n--) {
        result *= m;
    }
    return result;
}

// 显示带小数点的数字
void LCD_ShowFloat(uint16_t x, uint16_t y, float num, uint8_t int_len, uint8_t frac_len, uint16_t color) {
    uint32_t int_part = (uint32_t)num;
    uint32_t frac_part = (uint32_t)((num - int_part) * LCD_Pow(10, frac_len));
    
    // 显示整数部分
    LCD_ShowNum(x, y, int_part, int_len, color);
    
    // 显示小数点
    LCD_ShowChar(x + int_len * FONT_WIDTH, y, '.', color);
    
    // 显示小数部分
    LCD_ShowNum(x + (int_len + 1) * FONT_WIDTH, y, frac_part, frac_len, color);
}

// 居中显示字符串
void LCD_ShowStringCenter(uint16_t y, const char *str, uint16_t color) {
    uint16_t len = 0;
    const char *p = str;
    
    // 计算字符串长度
    while(*p++) len++;
    
    // 计算居中位置
    uint16_t x = (LCD_WIDTH - len * FONT_WIDTH) / 2;
    
    // 显示字符串
    LCD_ShowString(x, y, str, color);
}

// 在指定区域内显示字符串（自动换行）
void LCD_ShowStringInArea(uint16_t x, uint16_t y, uint16_t width, uint16_t height, 
                          const char *str, uint16_t color) {
    uint16_t x_pos = x;
    uint16_t y_pos = y;
    
    while(*str != '\0') {
        // 换行判断
        if(x_pos > x + width - FONT_WIDTH) {
            x_pos = x;
            y_pos += FONT_HEIGHT;
            
            // 超出区域判断
            if(y_pos > y + height - FONT_HEIGHT) {
                break;
            }
        }
        
        // 显示字符
        LCD_ShowChar(x_pos, y_pos, *str, color);
        
        x_pos += FONT_WIDTH;
        str++;
    }
}
