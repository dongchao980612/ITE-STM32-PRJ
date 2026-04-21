#ifndef __RC522_H
#define __RC522_H

#include "stm32f10x.h"

// ==================== Òý½Å¶¨Òå ====================
#define RC522_CS_PORT        GPIOA
#define RC522_CS_PIN         GPIO_Pin_4
#define RC522_CS_RCC         RCC_APB2Periph_GPIOA

#define RC522_RST_PORT       GPIOB
#define RC522_RST_PIN        GPIO_Pin_0
#define RC522_RST_RCC        RCC_APB2Periph_GPIOB

// ==================== ²Ù×÷ºê ====================
#define RC522_CS_HIGH()      GPIO_SetBits(RC522_CS_PORT, RC522_CS_PIN)
#define RC522_CS_LOW()       GPIO_ResetBits(RC522_CS_PORT, RC522_CS_PIN)

#define RC522_RST_HIGH()     GPIO_SetBits(RC522_RST_PORT, RC522_RST_PIN)
#define RC522_RST_LOW()      GPIO_ResetBits(RC522_RST_PORT, RC522_RST_PIN)

// ==================== ÃüÁî ====================
#define PCD_RESETPHASE       0x0F
#define PCD_TRANSCEIVE       0x0C
#define PCD_AUTHENT          0x0E
#define PCD_IDLE             0x00

// ==================== ×´Ì¬ ====================
#define MI_OK                0x26
#define MI_ERR               0xBB
#define MI_NOTAGERR          0xCC


#define CommandReg       0x01
#define ComIEnReg        0x02
#define ComIrqReg        0x04
#define ErrorReg         0x06
#define FIFODataReg      0x09
#define FIFOLevelReg     0x0A
#define BitFramingReg    0x0D
#define TxControlReg     0x14
#define ControlReg       0x0C


// ==================== º¯Êý ====================
void RC522_Init(void);
void RC522_WriteReg(uint8_t addr, uint8_t data);
uint8_t RC522_ReadReg(uint8_t addr);

void RC522_AntennaOn(void);

void SetBitMask(uint8_t reg, uint8_t mask);
void ClearBitMask(uint8_t reg, uint8_t mask);

uint8_t RC522_Com(uint8_t cmd, uint8_t *in, uint8_t in_len, uint8_t *out, uint32_t *out_len);
uint8_t RC522_Request(uint8_t req_code, uint8_t *tag_type);
uint8_t RC522_Anticoll(uint8_t *snr);
void RC522_Halt(void);

#endif