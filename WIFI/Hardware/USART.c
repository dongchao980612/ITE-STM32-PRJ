#include "usart.h"
#include "wifi.h"
#include <stdio.h>
#include <stdarg.h>


void My_USART_Init(void)
{

    /*开启时钟*/
    RCC_APB2PeriphClockCmd(USART_CLK, ENABLE);	//开启USART1的时钟
    RCC_APB2PeriphClockCmd(USART1_GPIO_CLK, ENABLE);	//开启GPIOA的时钟

    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART1_GPIO_PORT, &GPIO_InitStructure);					//将PA9引脚初始化为复用推挽输出

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART1_GPIO_PORT, &GPIO_InitStructure);					//将PA10引脚初始化为上拉输入

    /*USART初始化*/
    USART_InitTypeDef USART_InitStructure;					//定义结构体变量
    USART_InitStructure.USART_BaudRate = USART1_BAUDRATE;				//波特率
    USART_InitStructure.USART_HardwareFlowControl = USART1_HWCONTROL;	//硬件流控制，不需要
    USART_InitStructure.USART_Mode = USART1_MODE;  // 配置工作模式，收发一起
    USART_InitStructure.USART_Parity = USART1_PARITY;		//奇偶校验，不需要
    USART_InitStructure.USART_StopBits = USART1_STOPBITS;	//停止位，选择1位
    USART_InitStructure.USART_WordLength = USART1_WORDLENGTH;		//字长，选择8位
    USART_Init(USART1, &USART_InitStructure);				//将结构体变量交给USART_Init，配置USART1



    /*中断输出配置*/
    USART_ITConfig(USART_INSTANCE, USART_IT_RXNE, ENABLE);			//开启串口接收数据的中断

    /*NVIC中断分组*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			//配置NVIC为分组2

    /*NVIC配置*/
    NVIC_InitTypeDef NVIC_InitStructure;					//定义结构体变量
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		//选择配置NVIC的USART1线
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//指定NVIC线路使能
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = USART1_PREEMPT_PRIORITY;		//指定NVIC线路的抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = USART1_SUB_PRIORITY;		//指定NVIC线路的响应优先级为1
    NVIC_Init(&NVIC_InitStructure);							//将结构体变量交给NVIC_Init，配置NVIC外设

    /*USART使能*/
    USART_Cmd(USART1, ENABLE);								//使能USART1，串口开始运行

}
void My_USART_SendByte(uint8_t Byte)
{

    USART_SendData(USART_INSTANCE, Byte);		//将字节数据写入数据寄存器，写入后USART自动生成时序波形

    while (USART_GetFlagStatus(USART_INSTANCE, USART_FLAG_TXE) == RESET);	//等待发送完成
}
void My_USART_SendArray(uint8_t *Array, uint16_t Length)
{
    uint16_t i;

    for (i = 0; i < Length; i ++)		//遍历数组
    {
        My_USART_SendByte(Array[i]);		//依次调用Serial_SendByte发送每个字节数据
    }
}

/**
  * 函    数：串口发送一个字符串
  * 参    数：String 要发送字符串的首地址
  * 返 回 值：无
  */
void My_USART_SendString(char *String)
{
    uint8_t i;

    for (i = 0; String[i] != '\0'; i ++)//遍历字符数组（字符串），遇到字符串结束标志位后停止
    {
        My_USART_SendByte(String[i]);		//依次调用Serial_SendByte发送每个字节数据
    }
}

/**
  * 函    数：次方函数（内部使用）
  * 返 回 值：返回值等于X的Y次方
  */
uint32_t My_USART_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;	//设置结果初值为1

    while (Y --)			//执行Y次
    {
        Result *= X;		//将X累乘到结果
    }

    return Result;
}

/**
  * 函    数：串口发送数字
  * 参    数：Number 要发送的数字，范围：0~4294967295
  * 参    数：Length 要发送数字的长度，范围：0~10
  * 返 回 值：无
  */
void My_USART_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;

    for (i = 0; i < Length; i ++)		//根据数字长度遍历数字的每一位
    {
        My_USART_SendByte(Number / My_USART_Pow(10, Length - i - 1) % 10 + '0');	//依次调用Serial_SendByte发送每位数字
    }
}



/**
  * 函    数：使用printf需要重定向的底层函数
  * 参    数：保持原始格式即可，无需变动
  * 返 回 值：保持原始格式即可，无需变动
  */
int fputc(int ch, FILE *f)
{
    My_USART_SendByte(ch);			//将printf的底层重定向到自己的发送字节函数
    return ch;
}


//重定fgetc()函数
int fgetc(FILE *f)
{
    while (USART_GetFlagStatus(USART_INSTANCE, USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(USART_INSTANCE);
}

/**
  * 函    数：自己封装的prinf函数
  * 参    数：format 格式化字符串
  * 参    数：... 可变的参数列表
  * 返 回 值：无
  */
void My_Printf(char *format, ...)
{
    char String[100];				//定义字符数组
    va_list arg;					//定义可变参数列表数据类型的变量arg
    va_start(arg, format);			//从format开始，接收参数列表到arg变量
    vsprintf(String, format, arg);	//使用vsprintf打印格式化字符串和参数列表到字符数组中
    va_end(arg);					//结束变量arg
    My_USART_SendString(String);		//串口发送字符数组（字符串）
}

void USART1_IRQHandler(void)
{
    uint8_t ucTemp;

    if (USART_GetITStatus(USART_INSTANCE, USART_IT_RXNE) != RESET)
    {
        ucTemp = USART_ReceiveData(USART_INSTANCE);
        My_USART_SendByte(ucTemp); // 数据流前缀

        while (USART_GetFlagStatus(USART_INSTANCE, USART_FLAG_TXE) == RESET);

        USART_SendData(WIFI_USART, ucTemp);

        USART_ClearITPendingBit(USART_INSTANCE, USART_IT_RXNE);
    }
}

