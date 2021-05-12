#include "exti.h"


void EXTI_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启按键 GPIO 口的时钟*/
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK|KEY2_INT_GPIO_CLK,ENABLE);

	/*--------------------------KEY1 配置---------------------*/
	/* 选择按键用到的 GPIO */
	GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
	/* 配置为浮空输入 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);
	
	
	/* 选择按键用到的 GPIO */
	GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
	/* 配置为浮空输入 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);
}

static void EXTI_NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* 配置 NVIC 为优先级组 1 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* 配置中断源：按键 1 */
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
	//2
//	NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
	
	/* 配置抢占优先级：1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* 配置子优先级：1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* 使能中断通道 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	
	
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
		/* 配置抢占优先级：1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* 配置子优先级：1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	/* 使能中断通道 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI_Key_Config()
{
	//1
	EXTI_InitTypeDef EXTI_InitStruct;
	
	EXTI_GPIO_Config();
	EXTI_NVIC_Config();
	
	/*开启按键 GPIO 口的时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	/* 选择 EXTI 的信号源 */
	GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE,KEY1_INT_EXTI_PINSOURCE);
	/* 选择按键用到的 GPIO */
	EXTI_InitStruct.EXTI_Line=KEY1_INT_EXTI_LINE;
	/* EXTI 为中断模式 */
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	/* 上升沿中断 */
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	/* 使能中断 */
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	//2
	/* 选择 EXTI 的信号源 */
	GPIO_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE,KEY2_INT_EXTI_PINSOURCE);
	/* 选择按键用到的 GPIO */
	EXTI_InitStruct.EXTI_Line=KEY2_INT_EXTI_LINE;
	/* EXTI 为中断模式 */
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	/* EXTI 为中断模式 */
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	/* 使能中断 */
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	
	
}

