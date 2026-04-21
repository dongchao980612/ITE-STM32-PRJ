#include "rc522.h"
#include "spi.h"
#include "delay.h"

// 统一 CS 控制（必须统一！）
#define RC522_CS_Enable()    RC522_CS_LOW()
#define RC522_CS_Disable()   RC522_CS_HIGH()

void RC522_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // 1. 先开时钟
    RCC_APB2PeriphClockCmd(RC522_CS_RCC | RC522_RST_RCC, ENABLE);

    // 2. CS 推挽输出
    GPIO_InitStruct.GPIO_Pin = RC522_CS_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RC522_CS_PORT, &GPIO_InitStruct);

    // 3. RST 推挽输出
    GPIO_InitStruct.GPIO_Pin = RC522_RST_PIN;
    GPIO_Init(RC522_RST_PORT, &GPIO_InitStruct);

    // 4. 默认状态
    RC522_CS_HIGH();
    RC522_RST_HIGH();

    // ==================== 正确硬件复位 ====================
    RC522_RST_LOW();     // 拉低复位
    Delay_ms(10);       // 保持
    RC522_RST_HIGH();   // 拉高复位
    Delay_ms(10);       // 等待稳定

    // 5. 初始化 SPI
    SPI1_Init();

    // ==================== RC522 标准初始化 ====================
    RC522_WriteReg(0x01, PCD_RESETPHASE);  // 软复位
    Delay_ms(1);

    RC522_WriteReg(0x2A, 0x8D);
    RC522_WriteReg(0x2B, 0x3E);
    RC522_WriteReg(0x2D, 0x1E);
    RC522_WriteReg(0x2C, 0x00);
    RC522_WriteReg(0x15, 0x40);
    RC522_WriteReg(0x11, 0x3D);
		RC522_WriteReg(0x0D, 0x00);
		RC522_WriteReg(0x14, 0x03);
		RC522_WriteReg(0x0C, 0x00);


    RC522_AntennaOn();
}

// ==================== 写寄存器 ====================
void RC522_WriteReg(uint8_t addr, uint8_t data)
{
    RC522_CS_Enable();
    SPI1_ReadWriteByte((addr << 1) & 0x7E);
    SPI1_ReadWriteByte(data);
    RC522_CS_Disable();
}

// ==================== 读寄存器 ====================
uint8_t RC522_ReadReg(uint8_t addr)
{
    uint8_t data;
    RC522_CS_Enable();
    SPI1_ReadWriteByte(((addr << 1) & 0x7E) | 0x80);
    data = SPI1_ReadWriteByte(0xFF);
    RC522_CS_Disable();
    return data;
}

// ==================== 开天线 ====================
void RC522_AntennaOn(void)
{
//    uint8_t temp = RC522_ReadReg(0x14);
//    if ((temp & 0x03) == 0)
//    {
//        RC522_WriteReg(0x14, temp | 0x03);
//    }
	   RC522_WriteReg(0x14, 0x03);
}

// ==================== 空函数 ====================
uint8_t RC522_Com(uint8_t cmd, uint8_t *inData, uint8_t inLen, uint8_t *outData, uint32_t *outLen)
{
    uint8_t status = MI_ERR;
    uint8_t irqEn = 0x00;
    uint8_t waitFor = 0x00;
    uint8_t lastBits, n;
    uint32_t i;

    if (cmd == PCD_AUTHENT)
    {
        irqEn = 0x12;
        waitFor = 0x10;
    }
    else if (cmd == PCD_TRANSCEIVE)
    {
        irqEn = 0x77;
        waitFor = 0x30;
    }

    SetBitMask(ComIEnReg, irqEn | 0x80);
    ClearBitMask(ComIrqReg, 0x80);
    RC522_WriteReg(CommandReg, PCD_IDLE);
    SetBitMask(FIFOLevelReg, 0x80);

    for (i = 0; i < inLen; i++)
    {
        RC522_WriteReg(FIFODataReg, inData[i]);
    }

    RC522_WriteReg(CommandReg, cmd);
    SetBitMask(BitFramingReg, 0x80);

    i = 20000;
    do
    {
        n = RC522_ReadReg(ComIrqReg);
    } while ((i--) && !(n & 0x01) && !(n & waitFor));

    ClearBitMask(BitFramingReg, 0x80);

    if (i != 0)
    {
        if (!(RC522_ReadReg(ErrorReg) & 0x1B))
        {
            status = MI_OK;
            if (n & irqEn & 0x01)
            {
                status = MI_NOTAGERR;
            }

            if (cmd == PCD_TRANSCEIVE)
            {
                n = RC522_ReadReg(FIFOLevelReg);
                lastBits = RC522_ReadReg(ControlReg) & 0x07;

                if (lastBits)
                    *outLen = (n - 1) * 8 + lastBits;
                else
                    *outLen = n * 8;

                if (n == 0)
                    n = 1;
                if (n > 64)
                    n = 64;

                for (i = 0; i < n; i++)
                {
                    outData[i] = RC522_ReadReg(FIFODataReg);
                }
            }
        }
    }

    RC522_WriteReg(CommandReg, PCD_IDLE);
    return status;
}

// ==================== 寻卡 ====================
uint8_t RC522_Request(uint8_t req_code, uint8_t *tag_type)
{
    uint8_t status;
    uint32_t len;
    uint8_t buf[8];

    buf[0] = req_code;
    RC522_WriteReg(0x0D, 0x07);

    status = RC522_Com(PCD_TRANSCEIVE, buf, 1, buf, &len);
    if ((status == MI_OK) && (len == 0x10))
    {
        tag_type[0] = buf[0];
        tag_type[1] = buf[1];
    }
    else
    {
        status = MI_ERR;
    }
    return status;
}

// ==================== 防冲突（读UID） ====================
uint8_t RC522_Anticoll(uint8_t *snr)
{
    uint8_t status;
    uint32_t len;
    uint8_t buf[8];

    buf[0] = 0x93;
    buf[1] = 0x20;

    RC522_WriteReg(0x0D, 0x00);

    status = RC522_Com(PCD_TRANSCEIVE, buf, 2, buf, &len);
    if (status == MI_OK)
    {
        snr[0] = buf[0];
        snr[1] = buf[1];
        snr[2] = buf[2];
        snr[3] = buf[3];
    }
    return status;
}

// ==================== 休眠 ====================
void RC522_Halt(void)
{
    uint8_t buf[8];
    uint32_t len;

    buf[0] = 0x50;
    buf[1] = 0x00;
    RC522_Com(PCD_TRANSCEIVE, buf, 2, buf, &len);
}

// 置位：将寄存器的某些位设为 1
void SetBitMask(uint8_t reg, uint8_t mask)
{
    uint8_t tmp = RC522_ReadReg(reg);
    RC522_WriteReg(reg, tmp | mask);
}

// 清零：将寄存器的某些位清 0
void ClearBitMask(uint8_t reg, uint8_t mask)
{
    uint8_t tmp = RC522_ReadReg(reg);
    RC522_WriteReg(reg, tmp & (~mask));
}