#include "stm32f4xx_conf.h"

void _delay_init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);

    uint32_t timer_clock_freq;

    if (RCC_Clocks.PCLK1_Frequency == RCC_Clocks.SYSCLK_Frequency) {
        timer_clock_freq = RCC_Clocks.PCLK1_Frequency;
    } else {
        timer_clock_freq = RCC_Clocks.PCLK1_Frequency * 2;
    }

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
    TIM_TimeBaseInitStruct.TIM_Prescaler = timer_clock_freq/1000 - 1;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);
    TIM_Cmd(TIM6, ENABLE);
}

void _delay_stop(void) {
    TIM_Cmd(TIM6, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, DISABLE);
}

void delay_ms(uint16_t ms) {
    _delay_init();

    TIM6->CNT = 0;
    while(TIM6->CNT <= ms);

    _delay_stop();
}
