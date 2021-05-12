/**
  ******************************************************************************
  * @file    bsp_breathing.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32 ָ���߿����� 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://fire-stm32.taobao.com
  *
  ******************************************************************************
  */



#include "./breathinglight/bsp_breathing.h"


//����������ε�Ƶ��
__IO uint16_t period_class = 10;

/* LED���ȵȼ� PWM��,ָ������ ���˱�ʹ�ù���Ŀ¼�µ�python�ű�index_wave.py����*/
uint16_t indexWave[] = {
0,0,1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 
4, 4, 4, 4, 5, 5, 5, 5,5, 5, 6, 
7, 7,7,7, 8,8,8,8, 9,9,9,9, 10, 10, 10, 10,
11, 11, 11, 11,	13,13,13,13,
15,15,15,15, 17,17,17,17, 19,19,19,19,
22,22,22,22, 25,25,25,25, 28,28,28,28,
32,32,32,32, 36,36,36,36,41,41,41,41,
47,47,47,47, 53,53,53,53, 61,61,61,61, 
69,69,69,69,	79,79,79,79, 89,89,89,89, 
102,102,102,102,116,116,116,116,
131,131,131,131, 149,149,149,149, 
170,170,170,170,	193, 193, 193, 193, 
219,219,219,219,	250,250,250,250,
284,284,284,284, 323,323,323,323, 367,367,367,367,
417,417,417,417, 474,474,474,474, 539,539,539,539,
613, 613, 613, 613, 697, 697, 697, 697, 792,792,792,792,
901,901,901,901, 1024,1024, 1024, 1024
};

//����PWM���ж��ٸ�Ԫ��
uint16_t POINT_NUM = sizeof(indexWave)/sizeof(indexWave[0]); 


 /**
  * @brief  ����TIM�������PWMʱ�õ���I/O
  * @param  ��
  * @retval ��
  */
static void TIMx_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*  clock enable */
  RCC_APB2PeriphClockCmd(BRE_TIM_GPIO_CLK, ENABLE); 
  BRE_TIM_GPIO_APBxClock_FUN  ( BRE_TIM_GPIO_CLK, ENABLE );
		
	BRE_GPIO_REMAP_FUN();  

  /* ���ú������õ������� */
  GPIO_InitStructure.GPIO_Pin =  BRE_TIM_LED_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init( BRE_TIM_LED_PORT, &GPIO_InitStructure );
}


/**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Config_PWM(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* ����TIM3_IRQ�ж�Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = BRE_TIMx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  ����TIM�����PWM�źŵ�ģʽ�������ڡ�����
  * @param  ��
  * @retval ��
  */

static void TIMx_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;																				
	
	
	/* ����TIM3CLK ʱ�� */
	BRE_TIM_APBxClock_FUN ( BRE_TIM_CLK, ENABLE ); 
	
	/* ������ʱ������ ,���PWM��������жϷ������е�period_cntѭ����������*/	
	
	/* ����ʹ��������������Ϊ3�����Ҽ��ɴﵽ�ܺõ�Ч�� */	
	
	//Ҫ��
	//TIM_Period����PWM������ֵ��Χһ��
	//TIM_Prescaler��ԽСԽ�ã��ɼ�����˸����
	//PERIOD_CLASS���жϷ������п��Ƶ�����ѭ���Ĵ������������ɿ���������ߵ�����
	//POINT_NUM��PWM���Ԫ�أ�����PWM������ߵĲ�������

	/*************��ʵ���е�����***************/	
	/***********************************************
	#python����ű�	count.py
	#PWM����
	POINT_NUM = 110

	#���ڱ���
	PERIOD_CLASS = 10

	#��ʱ����ʱ����
	TIMER_TIM_Period = 2**10
	#��ʱ����Ƶ
	TIMER_TIM_Prescaler = 200

	#STM32ϵͳʱ��Ƶ�ʺ�����
	f_pclk = 72000000
	t_pclk = 1/f_pclk

	#��ʱ��update�¼�����
	t_timer = t_pclk*TIMER_TIM_Prescaler*TIMER_TIM_Period

	#ÿ��PWM���ʱ��
	T_Point = t_timer * PERIOD_CLASS

	#������������
	T_Up_Down_Cycle = T_Point * POINT_NUM

	print ("�������ڣ�",T_Up_Down_Cycle)
	
	#���н����
	
	�������ڣ�3.12888
	************************************************************/

  /* ������ʱ������ */		  
  TIM_TimeBaseStructure.TIM_Period = (1024-1);;       							  //����ʱ����0������ TIM_Period+1 ��Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = (200-1);	    							//����Ԥ��Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//���ϼ���ģʽ
  TIM_TimeBaseInit(BRE_TIMx, &TIM_TimeBaseStructure);

  /* PWMģʽ���� */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
  TIM_OCInitStructure.TIM_Pulse = 0;				 						  			//���ó�ʼPWM������Ϊ0	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  	  //����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ

  BRE_TIM_OCxInit ( BRE_TIMx, &TIM_OCInitStructure );	 									//ʹ��ͨ��
	

  BRE_TIM_OCxPreloadConfig ( BRE_TIMx, TIM_OCPreload_Enable );						//ʹ��Ԥװ��	

  TIM_ARRPreloadConfig(BRE_TIMx, ENABLE);			 										//ʹ��TIM���ؼĴ���ARR

  /* TIM3 enable counter */
  TIM_Cmd(BRE_TIMx, ENABLE);                   										//ʹ�ܶ�ʱ��	
	
	TIM_ITConfig(BRE_TIMx, TIM_IT_Update, ENABLE);										//ʹ��update�ж�
		
	NVIC_Config_PWM();																					//�����ж����ȼ�		
	
}

/**
  * @brief  TIM �����Ƴ�ʼ��
  *         ����PWMģʽ��GPIO
  * @param  ��
  * @retval ��
  */
void TIMx_Breathing_Init(void)
{
	TIMx_GPIO_Config();
	TIMx_Mode_Config();	
}

/*********************************************END OF FILE**********************/
