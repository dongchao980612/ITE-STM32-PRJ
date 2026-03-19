#include "stm32f10x.h"                  // Device header

#include "delay.h"
#include "beep.h"


int main()
{

    Beep_Init();

    while (0)
    {
        Beep_On();  // Ãù½Ð
        Delay_ms(1000);
        Beep_Off();  // ¾²Òô
        Delay_ms(1000);
    }
}