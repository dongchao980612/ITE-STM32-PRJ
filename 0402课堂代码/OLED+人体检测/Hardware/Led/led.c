#include "led.h"

void Led_Init(void)
{
    // 步骤1：开启GPIOC时钟
    RCC_APB2PeriphClockCmd(LED_CLK, ENABLE);

    // 步骤2：配置GPIO模式
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin =  LED_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_Init(LED_PORT, &GPIO_InitStructure);
	
		GPIO_SetBits(LED_PORT, LED_PIN);
	
}

void Led_On(void)
{
    GPIO_ResetBits(LED_PORT, LED_PIN);  // 点亮
}

void Led_Off(void)
{
    GPIO_SetBits(LED_PORT, LED_PIN);  // 熄灭
}


