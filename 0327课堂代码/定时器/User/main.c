#include "stm32f10x.h"                  // Device header

#include "delay.h"
#include "led.h"
#include "key.h"
#include "timer.h"

int main()
{

    Led_Init();
    Key_Init();
    Timer_Init();

    while (1)
    {

    }

}

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIMER_INSTANCE, TIM_IT_Update) == SET)
    {
        Led_Turn();
        TIM_ClearITPendingBit(TIMER_INSTANCE, TIM_IT_Update);
    }
}
