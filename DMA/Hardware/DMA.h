#ifndef __DMA_H
#define __DMA_H

// 选择DMA1_Channel7（任意空闲通道即可，M2M模式无外设绑定）
#define DMA_CLOCK					 RCC_AHBPeriph_DMA1
#define DMA_M2M_CHANNEL    DMA1_Channel7
#define DMA_M2M_FLAG_TC    DMA1_FLAG_TC7


// 测试用缓存定义
#define TEST_DATA_LEN      5  // 测试数据长度
extern uint8_t DMA_SRC_BUF[TEST_DATA_LEN]; // DMA源缓存
extern uint8_t DMA_DST_BUF[TEST_DATA_LEN]; // DMA目标缓存


// 函数声明
void DMA_M2M_Init(void);                // DMA内存到内存初始化
void DMA_M2M_Transfer(void);            // 启动DMA数据搬运


#endif

