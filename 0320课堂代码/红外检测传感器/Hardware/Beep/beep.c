#include "beep.h"

void Beep_Init(void)
{
    // 步骤1：开启GPIOC时钟
    RCC_APB2PeriphClockCmd(BEEP_CLK, ENABLE);

    // 步骤2：配置GPIO模式
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin =  BEEP_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_Init(BEEP_PORT, &GPIO_InitStructure);
	
		GPIO_SetBits(BEEP_PORT, BEEP_PIN);
	
}

void Beep_On(void)
{
    GPIO_SetBits(BEEP_PORT, BEEP_PIN);  // 鸣叫
}

void Beep_Off(void)
{
    GPIO_ResetBits(BEEP_PORT, BEEP_PIN);  // 静音
}


