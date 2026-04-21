#include "spi.h"

void SPI1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SPI_InitTypeDef SPI_InitStruct;

    // 时钟使能（简化，避免重复）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | SPI_RCC, ENABLE);

    // SCK + MOSI 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = SPI_SCK_PIN | SPI_MOSI_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_SCK_PORT, &GPIO_InitStruct);

    // MISO 上拉输入
    GPIO_InitStruct.GPIO_Pin = SPI_MISO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(SPI_MISO_PORT, &GPIO_InitStruct);

    // SPI 初始化
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init(SPI_INSTANCE, &SPI_InitStruct);

    SPI_Cmd(SPI_INSTANCE, ENABLE);
}

uint8_t SPI1_ReadWriteByte(uint8_t data)
{
    while (SPI_I2S_GetFlagStatus(SPI_INSTANCE, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI_INSTANCE, data);

    while (SPI_I2S_GetFlagStatus(SPI_INSTANCE, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI_INSTANCE);
}

