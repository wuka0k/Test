#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

//ADC���ѡ��
//������ ADC1/2�����ʹ��ADC3,�ж���ص�Ҫ�ĳ�ADC3��
#define ADC_APBxClock_FUN				RCC_APB2PeriphClockCmd
#define ADCx										ADC2
#define ADC_CLK									RCC_APB2Periph_ADC2


//ADCͨ���궨��
#define ADC_CHANNEL							ADC_Channel_11

//ADC�ж���غ궨��
#define ADC_IRQ									ADC1_2_IRQn
#define ADC_IRQHandler					ADC1_2_IRQHandler



void ADCx_Init(void);

#endif
