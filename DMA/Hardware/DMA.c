#include "stm32f10x.h"
#include "dma.h"
#include <string.h>

// DMA测试缓存（源+目标）
uint8_t DMA_SRC_BUF[TEST_DATA_LEN] = "SRC"; // 源数据
uint8_t DMA_DST_BUF[TEST_DATA_LEN] = {0}; // 目标数据（初始化为DST）
const uint8_t DMA_DST_ORIGIN[TEST_DATA_LEN] = "DST"; // 只读保存原始值

void DMA_M2M_Init()
{
    DMA_InitTypeDef DMA_InitStruct;

    // 1. 使能DMA1时钟,
    RCC_AHBPeriphClockCmd(DMA_CLOCK, ENABLE);

    // 2. 配置DMA通道（M2M模式）
    DMA_DeInit(DMA_M2M_CHANNEL);

    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)DMA_SRC_BUF; // 源内存地址（M2M模式下，Periph=源内存）
    DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)DMA_DST_BUF;     // 目标内存地址

    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;                // 外设（源内存）→内存（目标内存）
    DMA_InitStruct.DMA_BufferSize = TEST_DATA_LEN;                 // 传输长度
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;   // 源地址递增
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;           // 目标地址递增
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 8位传输
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;                     // 普通模式（单次传输）
    DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;            // 中等优先级
    DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;                      // 开启内存到内存模式（关键！）

    DMA_Init(DMA_M2M_CHANNEL, &DMA_InitStruct);
}

void DMA_M2M_Transfer(void)
{
    // 2. 启动DMA传输
    DMA_Cmd(DMA_M2M_CHANNEL, DISABLE);                    // 先关闭通道
    DMA_SetCurrDataCounter(DMA_M2M_CHANNEL, TEST_DATA_LEN); // 重置传输长度
    DMA_Cmd(DMA_M2M_CHANNEL, ENABLE);

    // 3. 等待DMA传输完成
    while (DMA_GetFlagStatus(DMA_M2M_FLAG_TC) == RESET);

    // 4. 清除完成标志
    DMA_ClearFlag(DMA_M2M_FLAG_TC);
}