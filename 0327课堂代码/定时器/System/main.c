#include "stm32f10x.h"

// TIM2 初始化：1秒中断一次
void TIM2_Init(void)
{
    // ========== 第1步：开 TIM2 时钟 ==========
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // ========== 第2步：配置使用内部时钟 ==========
    TIM_InternalClockConfig(TIM2);

    // ========== 第3步：配置时基单元（核心） ==========
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

    // 这个分频和定时无关，随便填
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    // 向上计数模式
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    // ARR自动重装载值 = 9999
    TIM_TimeBaseInitStruct.TIM_Period = 9999;
    // PSC预分频器 = 7199
    TIM_TimeBaseInitStruct.TIM_Prescaler = 7199;
    // 基本定时器不用这个
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    // ========== 第4步：开启更新中断，清标志 ==========
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // ========== 第5步：NVIC中断优先级配置 ==========
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;

    NVIC_Init(&NVIC_InitStruct);

    // ========== 第6步：启动定时器 ==========
    TIM_Cmd(TIM2, ENABLE);
}

// ========== TIM2 中断服务函数（必须写！） ==========
void TIM2_IRQHandler(void)
{
    // 判断是否是更新中断
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        // ==============================
        // 这里写你要执行的代码 1秒触发一次
        // ==============================

        // 清除中断标志位
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}