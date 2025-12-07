#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "pwm.h"

int main()
{

    // Led_Init();
    PWM_Init();

    while (1)
    {
        for (int i = 0; i <= 100; i++)
        {
            PWM_SetCompare1(i);
            Delay_ms(10);
        }

        for (int i = 0; i <= 100; i++)
        {
            PWM_SetCompare1(100 - i);
            Delay_ms(10);
        }
    }
}


