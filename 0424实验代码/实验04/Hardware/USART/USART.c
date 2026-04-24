#include "usart.h"
#include <stdio.h>


void Serial_Init(void)
{

    /*开启时钟*/
    RCC_APB2PeriphClockCmd(SERIAL_CLk, ENABLE);	//开启USART1的时钟
    RCC_APB2PeriphClockCmd(GPIO_TX_CLK, ENABLE);	//开启GPIOA的时钟

    /* GPIO TX 初始化：复用推挽输出 */
    GPIO_InitTypeDef GPIO_InitStructure;
	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_TX_PORT, &GPIO_InitStructure);


    /* GPIO TX 初始化：上拉输入 */
    GPIO_InitStructure.GPIO_Pin = GPIO_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIO_RX_PORT, &GPIO_InitStructure);


    /*USART初始化*/
    USART_InitTypeDef USART_InitStructure;					//定义结构体变量
    USART_InitStructure.USART_BaudRate = 9600;				//波特率
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制，不需要

    USART_InitStructure.USART_Mode = USART_Mode_Tx;

    USART_InitStructure.USART_Parity = USART_Parity_No;		//奇偶校验，不需要
    USART_InitStructure.USART_StopBits = USART_StopBits_1;	//停止位，选择1位
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//字长，选择8位
    USART_Init(USART1, &USART_InitStructure);				//将结构体变量交给USART_Init，配置USART1

    /*USART使能*/
    USART_Cmd(SERIAL_INSTANCE, ENABLE);

}


int fputc(int ch, FILE *f)
{

    USART_SendData(SERIAL_INSTANCE, (uint8_t)ch);

    while (USART_GetFlagStatus(SERIAL_INSTANCE, USART_FLAG_TXE) == RESET);

    return ch;
}
