#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "timer.h"

int main()
{
	
		Led_Init();
	  Timer_Init();
	
    while (1)
    {

    }
}


// ÖÐ¶Ïº¯ÊýÄ£°å
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIMER2_INSTANCE, TIM_IT_Update) == SET)
    {
        Led_Turn();
        TIM_ClearITPendingBit(TIMER2_INSTANCE, TIM_IT_Update);
    }
}

