#include "exti.h"


void EXTI_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*�������� GPIO �ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK|KEY2_INT_GPIO_CLK,ENABLE);

	/*--------------------------KEY1 ����---------------------*/
	/* ѡ�񰴼��õ��� GPIO */
	GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
	/* ����Ϊ�������� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);
	
	
	/* ѡ�񰴼��õ��� GPIO */
	GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
	/* ����Ϊ�������� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);
}

static void EXTI_NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* ���� NVIC Ϊ���ȼ��� 1 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* �����ж�Դ������ 1 */
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
	//2
//	NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
	
	/* ������ռ���ȼ���1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* ���������ȼ���1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* ʹ���ж�ͨ�� */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	
	
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
		/* ������ռ���ȼ���1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* ���������ȼ���1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	/* ʹ���ж�ͨ�� */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI_Key_Config()
{
	//1
	EXTI_InitTypeDef EXTI_InitStruct;
	
	EXTI_GPIO_Config();
	EXTI_NVIC_Config();
	
	/*�������� GPIO �ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	/* ѡ�� EXTI ���ź�Դ */
	GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE,KEY1_INT_EXTI_PINSOURCE);
	/* ѡ�񰴼��õ��� GPIO */
	EXTI_InitStruct.EXTI_Line=KEY1_INT_EXTI_LINE;
	/* EXTI Ϊ�ж�ģʽ */
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	/* �������ж� */
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	/* ʹ���ж� */
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	//2
	/* ѡ�� EXTI ���ź�Դ */
	GPIO_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE,KEY2_INT_EXTI_PINSOURCE);
	/* ѡ�񰴼��õ��� GPIO */
	EXTI_InitStruct.EXTI_Line=KEY2_INT_EXTI_LINE;
	/* EXTI Ϊ�ж�ģʽ */
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	/* EXTI Ϊ�ж�ģʽ */
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	/* ʹ���ж� */
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	
	
}

