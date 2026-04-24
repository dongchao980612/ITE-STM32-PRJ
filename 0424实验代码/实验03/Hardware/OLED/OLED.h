#ifndef __OLED_H
#define __OLED_H



// OLED设备地址（7位地址左移1位）
#define OLED_ADDRESS      0x78   

// 控制字节
#define OLED_COMMAND_MODE 0x00    // 写命令
#define OLED_DATA_MODE    0x40    // 写数据

// OLED屏幕参数
#define OLED_WIDTH        128     // 列数
#define OLED_HEIGHT       64      // 行数
#define OLED_PAGE_NUM     8       // 8页模式（每页8行)


// 函数声明
void OLED_Init(void);
void OLED_WriteCommand(uint8_t Command);
void OLED_WriteData(uint8_t Data);
void OLED_SetCursor(uint8_t Y, uint8_t X);

void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

void OLED_Clear(void);



#endif
