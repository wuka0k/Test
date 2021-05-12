#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

//ADC编号选择
//可以是 ADC1/2，如果使用ADC3,中断相关的要改成ADC3的
#define ADC_APBxClock_FUN				RCC_APB2PeriphClockCmd
#define ADCx										ADC2
#define ADC_CLK									RCC_APB2Periph_ADC2


//ADC通道宏定义
#define ADC_CHANNEL							ADC_Channel_11

//ADC中断相关宏定义
#define ADC_IRQ									ADC1_2_IRQn
#define ADC_IRQHandler					ADC1_2_IRQHandler



void ADCx_Init(void);

#endif
