#include "key.h"
#include "delay.h"



void Key_Init(void)
{
    // 步骤1：开启GPIO时钟
    RCC_APB2PeriphClockCmd(KEY_CLK, ENABLE);

    // 步骤2：配置GPIO模式
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin =  KEY_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//  上拉输入模式
	
		// 步骤3：初始化结构体
    GPIO_Init(KEY_PORT, &GPIO_InitStructure);
}

KeyStatus Key_GetValue(void)
{
    KeyStatus key_status = RELEASED;

    key_status = (KeyStatus)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN);

    if(key_status == PRESSED)
    {
        Delay_ms(DELAY_INTERVAL);
        key_status = (KeyStatus)GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN);

        if(key_status == PRESSED)
        {
            return PRESSED;
        }
    }

    return key_status;
}

