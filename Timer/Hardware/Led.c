#include "led.h"


/*
	@brief : ≥ı ºªØLED PB12
*/
void Led_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(LED_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin =  LED_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

/*
	@brief : µ„¡¡LED
*/
void Led_On(void)
{
    GPIO_SetBits(LED_PORT, LED_PIN);
}

/*
	@brief : œ®√LED
*/
void Led_Off(void)
{
    GPIO_ResetBits(LED_PORT, LED_PIN);
}

void Led_Turn()
{
    if(GPIO_ReadOutputDataBit(LED_PORT, LED_PIN) == LEDMode_ON)
    {
        Led_Off();
    }
    else
    {
        Led_On();
    }
}

