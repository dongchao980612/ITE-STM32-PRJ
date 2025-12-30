#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "delay.h"
#include "wifi.h"
#include <stdio.h>

int main(void)
{
    My_USART_Init();
    My_WIFI_Init();
		printf("WIFI init over !\r\n");
	
    while (1)
    {


    }
}
