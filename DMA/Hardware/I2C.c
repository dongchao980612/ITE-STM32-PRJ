#include "stm32f10x.h"
#include "i2c.h"





void My_I2C_W_SCL(uint8_t  status)
{
	GPIO_WriteBit(I2C_SCL_PORT, I2C_SCL_PIN, (BitAction)status);

}


void My_I2C_W_SDA(uint8_t  status)
{
	GPIO_WriteBit(I2C_SDA_PORT, I2C_SDA_PIN, (BitAction)status);

}


/*引脚初始化*/
void My_I2C_Init(void)
{
    RCC_APB2PeriphClockCmd(I2C_SCL_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(I2C_SDA_CLK, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN;
    GPIO_Init(I2C_SCL_PORT, &GPIO_InitStructure);

    My_I2C_W_SCL(1);
    My_I2C_W_SDA(1);

}

/**
  * @brief  I2C开始
  */
void My_I2C_Start(void)
{
    My_I2C_W_SDA(1);
    My_I2C_W_SCL(1);
    My_I2C_W_SDA(0);
    My_I2C_W_SCL(0);
}

/**
  * @brief  I2C停止
  */
void My_I2C_Stop(void)
{
    My_I2C_W_SDA(0);
    My_I2C_W_SCL(1);
    My_I2C_W_SDA(1);
}

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的一个字节
  */
void My_I2C_SendByte(uint8_t Byte)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        My_I2C_W_SDA(Byte & (0x80 >> i));
        My_I2C_W_SCL(1);
        My_I2C_W_SCL(0);
    }

    My_I2C_W_SCL(1); //额外的一个时钟，不处理应答信号
    My_I2C_W_SCL(0);
}
