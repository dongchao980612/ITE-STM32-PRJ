#include "stm32f10x.h"                  // Device header
#include "i2c.h"
#include "oled.h"
#include "counter.h"
#include "led.h"
#include "delay.h"

int main()
{
    OLED_Init();
    Led_Init();
    Counter_Init();
    OLED_ShowString(1, 1, "Human Detection");	


    while (1)
    {
        if(Get_Person_Status() == PERSON)
        {
            Led_On();
            OLED_ShowString(2, 1, "Human Detected");
        }
        else
        {
            Led_Off();
            OLED_ShowString(2, 1, "No Human Detected");
        }
    }


}
