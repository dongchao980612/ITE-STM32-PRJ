#include "stm32f10x.h"                  // Device header

#include "delay.h"
#include "timer.h"
#include "oled.h"
#include "key.h"
#include "led.h"

int sec = 0;

int main()
{
    OLED_Init();
    Key_Init();
    Timer_Init();
    Led_Init();


    OLED_ShowString(1, 1, "Show Count:");
    OLED_ShowString(2, 1, "Cnt:");
    OLED_ShowString(3, 1, "Sec:");

    while(1)
    {
        if( TIM_GetCounter(TIMER_INSTANCE) < 5000 )
        {
            Led_On();  // 0 ~ 0.5Ãë ÁÁ
        }
        else
        {
            Led_Off(); // 0.5 ~ 1Ãë Ãð
        }

        if(Key_GetValue() == PRESSED)
        {
            sec = 0;
        }

        OLED_ShowNum(2, 5, TIM_GetCounter(TIMER_INSTANCE), 5);
        OLED_ShowNum(3, 5, sec, 5);

    }

    return 0;
}

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIMER_INSTANCE, TIM_IT_Update) == SET)
    {
        sec++;

        TIM_ClearITPendingBit(TIMER_INSTANCE, TIM_IT_Update);
    }
}