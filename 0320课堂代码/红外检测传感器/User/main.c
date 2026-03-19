#include "stm32f10x.h"                  // Device header

#include "delay.h"
#include "led.h"
#include "counter.h"
#include "beep.h"

int main()
{

    Led_Init();
    Beep_Init();
    Counter_Init();

    while (1)
    {
        if(Get_Person_Status() == PERSON)
        {
            Beep_On();
            Led_On();    // 有人，点亮LED
        }
        else
        {
            Beep_Off();
            Led_Off();   // 没人，熄灭LED
        }
    }

}
