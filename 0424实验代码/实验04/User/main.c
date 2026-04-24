#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "led.h"
#include "counter.h"
#include "usart.h"

#include <stdio.h>

extern  PersonStatus person_status;

int main()
{
    OLED_Init();
		Serial_Init();
    Led_Init();
    Counter_Init();
	
    OLED_ShowString(1, 1, "Human Detection");	


    while (1)
    {
        if(Get_Person_Status() == PERSON)
        {
            Led_On();
            OLED_ShowString(2, 1, "Human Detected");
						printf("Human Detected...\n");
        }
        else
        {
            Led_Off();
            OLED_ShowString(2, 1, "No Human Detected");
        }
    }

    return 0;
}
