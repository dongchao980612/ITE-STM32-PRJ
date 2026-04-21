#ifndef __OLED_CONFIG_H
#define __OLED_CONFIG_H

#define OLED_CMD_DISPLAY_OFF         0xAE    // 关闭显示
#define OLED_CMD_DISPLAY_ON          0xAF    // 开启显示

#define OLED_CMD_SET_CLOCK_DIV       0xD5    // 设置时钟分频
#define OLED_CMD_SET_MUX_RATIO       0xA8    // 设置多路复用率
#define OLED_CMD_SET_DISPLAY_OFFSET  0xD3    // 设置显示偏移
#define OLED_CMD_SET_START_LINE      0x40    // 设置显示起始行

#define OLED_CMD_SEG_REMAP           0xA1    // 列地址映射（左右方向）
#define OLED_CMD_COM_SCAN_DIR        0xC8    // 行扫描方向（上下方向）

#define OLED_CMD_SET_COM_PINS        0xDA    // 设置COM引脚硬件配置
#define OLED_CMD_SET_CONTRAST        0x81    // 对比度设置
#define OLED_CMD_SET_PRECHARGE       0xD9    // 预充电周期
#define OLED_CMD_SET_VCOMH           0xDB    // VCOMH 电平

#define OLED_CMD_DISPLAY_NORMAL      0xA6    // 正常显示
#define OLED_CMD_DISPLAY_INVERSE     0xA7    // 反色显示

#define OLED_CMD_DISPLAY_ALL_ON      0xA4    // 按显存显示（非全屏亮）
#define OLED_CMD_CHARGE_PUMP         0x8D    // 电荷泵（必须开）

#define OLED_CMD_DISPLAY_OFF      	0xAE
#define OLED_CMD_DISPLAY_ON       	0xAF
#define OLED_CMD_SET_PAGE_ADDR    	0xB0    // 页地址基址（0xB0~0xB7）
#define OLED_CMD_SET_COL_HIGH     	0x10    // 列地址高4位基址
#define OLED_CMD_SET_COL_LOW      	0x00    // 列地址低4位基址


#endif
