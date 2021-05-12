#ifndef __FENG_H
#define __FENG_H

#include "stm32f10x.h"


#define	ON	1
#define	OFF	0

#define FENG_GPIO_PIN	GPIO_Pin_8
#define	FENG_GPIO_PORT GPIOA
#define	FENG_GPIO_CLK	RCC_APB2Periph_GPIOA


// \ C语言里面叫续行符，后面不能有任何的东西

#define FENG(a)	if(a)	\
											GPIO_SetBits(FENG_GPIO_PORT,FENG_GPIO_PIN); \
									else	GPIO_ResetBits(FENG_GPIO_PORT,FENG_GPIO_PIN);

void FENG_GPIO_Config(void);

#endif
