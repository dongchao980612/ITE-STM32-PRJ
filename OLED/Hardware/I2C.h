#ifndef __I2C_H
#define __I2C_H

// I2C SCL引脚配置
#define I2C_SCL_CLK    RCC_APB2Periph_GPIOB  // SCL引脚时钟
#define I2C_SCL_PIN    GPIO_Pin_8            // SCL引脚号
#define I2C_SCL_PORT   GPIOB                 // SCL引脚端口

// I2C SDA引脚配置
#define I2C_SDA_CLK    RCC_APB2Periph_GPIOB  // SDA引脚时钟
#define I2C_SDA_PIN    GPIO_Pin_9            // SDA引脚号
#define I2C_SDA_PORT   GPIOB                 // SDA引脚端口



void My_I2C_W_SCL(uint8_t  action);
void My_I2C_W_SDA(uint8_t  action);


void My_I2C_Init(void);

void My_I2C_Start(void);
void My_I2C_Stop(void);

void My_I2C_SendByte(uint8_t Byte);

#endif
