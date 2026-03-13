#include "stm32f10x.h"                  // Device header
#include "delay.h"

int main()
{

    // 步骤1：开启GPIOC时钟
    RCC->APB2ENR = 0x00000010;

    // 步骤2：配置GPIO模式
    GPIOC->CRH  =  0x00300000;  // 配置模式和速度


    while (1)
    {
        GPIOC->ODR	= 0x00002000;  // 熄灭
        Delay_ms(500);
        GPIOC->ODR	= 0x00000000;  // 点亮
        Delay_ms(500);
    }
}
