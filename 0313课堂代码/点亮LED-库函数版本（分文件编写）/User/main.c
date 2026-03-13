#include "stm32f10x.h"                  // Device header

#include "delay.h"
#include "led.h"


int main()
{

    Led_Init();

    while (1)
    {
        Led_On();  // Ï¨Ãð
        Delay_ms(500);
        Led_On();  // µãÁÁ
        Delay_ms(500);
    }


}
