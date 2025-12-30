#include "wifi.h"
#include "usart.h"

void My_WIFI_Init(void)
{
    //使能时钟
    RCC_APB2PeriphClockCmd(WIFI_GPIO_CLK, ENABLE);//使能时钟A
    RCC_APB1PeriphClockCmd(WIFI_USART_CLK, ENABLE); //使能时钟USART2

    //为初始化函数做准备
    GPIO_InitTypeDef GPIO_InitStructure;//定义结构体
    GPIO_InitStructure.GPIO_Pin = WIFI_TX_PIN;//设置PA2引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;//设置输出模式为复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;//设置输出速度为50MHZ

    //初始化函数PIN2


    GPIO_InitStructure.GPIO_Pin = WIFI_RX_PIN;//设置PA3引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;//设置输出模式为上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;//设置输出速度为50MHZ


    GPIO_Init(WIFI_GPIO_PORT, &GPIO_InitStructure); //初始化


    USART_InitTypeDef USART_InitStructure; //定义串口结构体
    USART_InitStructure.USART_BaudRate = WIFI_USART_BAUDRATE; //波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//数字帧长度
    USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位
    USART_InitStructure.USART_Parity = USART_Parity_No; //不使用校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//不使用硬件流控制
    USART_InitStructure.USART_Mode = WIFI_USART_MODE; //模式为发送+接收

    //初始化串口2
    USART_Init(WIFI_USART, &USART_InitStructure);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//使能接收中断

    NVIC_InitTypeDef NVIC_InitStructure; //定义结构体
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //根据上面的我们所选取的USART2
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//这里选择的是抢占 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //这里选择的是响应2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能指定的中断通道
    //初始化函数
    NVIC_Init(&NVIC_InitStructure);
    //使能串口2
    USART_Cmd(WIFI_USART, ENABLE);


}


void My_WIFI_SendByte(uint8_t Byte)
{
    USART_SendData(WIFI_USART, Byte);

    while(USART_GetFlagStatus(WIFI_USART, USART_FLAG_TXE) == RESET );

}
void My_WIFI_SendString(uint8_t *Array, uint16_t Length)
{

    uint16_t i;

    for (i = 0; i < Length; i ++)		//遍历数组
    {
        My_WIFI_SendByte(Array[i]);		//依次调用Serial_SendByte发送每个字节数据
    }

}


void USART2_IRQHandler(void)
{
    uint8_t data = 0;

    if (USART_GetITStatus(WIFI_USART, USART_IT_RXNE) == SET)
    {

        data = USART_ReceiveData(WIFI_USART);//ESP8266 发送给 STM32的数据
        USART_SendData(USART_INSTANCE, data);

        while (USART_GetFlagStatus(USART_INSTANCE, USART_FLAG_TXE) == RESET);

        USART_ClearITPendingBit(USART_INSTANCE, USART_IT_RXNE);
    }

}

