#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"

int main()
{
	
		Led_Init();
	
    while (1)
    {
			// Led_On();
			// Delay_ms(500);
			
			// Led_Off();
			// Delay_ms(500);
			Led_Turn();
			Delay_ms(500);
			
    }
}
