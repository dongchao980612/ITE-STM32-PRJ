#include "stm32f10x.h"                  // Device header

#include "delay.h"
#include "led.h"
#include "key.h"


int main()
{
    Led_Init();   
    Key_Init(); 
	
    int led_flag = 0;  // LED×´Ì¬±êÖ¾£º0-Ï¨Ãð£¬1-µãÁÁ
    uint8_t last_key = RELEASED; 

    while (1)
    {
        uint8_t curr_key = Key_GetValue();
        

        if (curr_key == PRESSED && last_key == RELEASED)
        {
            led_flag = !led_flag; 
            led_flag ? Led_On() : Led_Off(); 
        }
        
        last_key = curr_key; 
    }
}