#include "feng.h"

void FENG_GPIO_Config(void)
{
	/*定义一个 GPIO_InitTypeDef 类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启 LED 相关的 GPIO 外设时钟*/
	RCC_APB2PeriphClockCmd( FENG_GPIO_CLK, ENABLE);
	/*选择要控制的 GPIO 引脚*/
	GPIO_InitStructure.GPIO_Pin = FENG_GPIO_PIN;

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/*设置引脚速率为 50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		/*调用库函数，初始化 GPIO*/
	GPIO_Init(FENG_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(FENG_GPIO_PORT, FENG_GPIO_PIN);
}
