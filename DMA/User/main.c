#include "stm32f10x.h" // Device header
#include "stm32f10x_conf.h"
#include "i2c.h"
#include "oled.h"
#include "dma.h"
#include "delay.h"
#include <string.h>

extern const uint8_t DMA_DST_ORIGIN[TEST_DATA_LEN]; // 只读保存原始值

int main()
{
    OLED_Init();


    DMA_M2M_Init();

   OLED_ShowString(1, 1, "DMA Test");  // 第1行显示固定标题

    while (1)
    {
			  memcpy(DMA_DST_BUF, DMA_DST_ORIGIN, TEST_DATA_LEN);
        OLED_ShowString(3, 1, "Before: ");          // 提示文字
        OLED_ShowString(3, 8, (char*)DMA_DST_BUF);  // 显示 DST
        Delay_s(1); // 停留1秒，便于观察

        DMA_M2M_Transfer();

        OLED_ShowString(3, 1, "After:  ");     // 提示文字
        OLED_ShowString(3, 8, (char*)DMA_DST_BUF); // 显示 SRC
        Delay_s(1); // 停留1秒，便于观察

    }

}
