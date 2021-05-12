#include "feng.h"

void FENG_GPIO_Config(void)
{
	/*����һ�� GPIO_InitTypeDef ���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*���� LED ��ص� GPIO ����ʱ��*/
	RCC_APB2PeriphClockCmd( FENG_GPIO_CLK, ENABLE);
	/*ѡ��Ҫ���Ƶ� GPIO ����*/
	GPIO_InitStructure.GPIO_Pin = FENG_GPIO_PIN;

	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/*������������Ϊ 50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		/*���ÿ⺯������ʼ�� GPIO*/
	GPIO_Init(FENG_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(FENG_GPIO_PORT, FENG_GPIO_PIN);
}
