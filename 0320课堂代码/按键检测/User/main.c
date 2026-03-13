#include "stm32f10x.h"                  // Device header

#include "delay.h"
#include "led.h"
#include "key.h"


int main()
{

    Led_Init();
    Key_Init();

    while (1)
    {
        if(Key_GetValue() == PRESSED)
        {
            Led_On();    // µãÁÁ
        }
        else
        {
            Led_On();  // Ï¨Ãð
        }

    }


}
