#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "usart.h"
#include<stdio.h>

int main()
{
    char buff[100];  // 接收字符串

    My_USART_Init();
    Delay_ms(100);
    printf("===== 串口已就绪 =====\r\n");

    while (1)
    {
        printf("\n\n请输入字符串：\r\n");
        scanf("%s", buff);
        printf("你输入的：%s\r\n", buff);
    }


}
