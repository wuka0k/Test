#include "adc.h"

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//��ADC IO�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//����ADC IO����ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	//����Ϊģ������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	
	//��ʼ��ADC IO
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

static void ADCx_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
	
	//ADCת���Ĺ���ģʽ
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;
	//ADCת����ɨ��ģʽ
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;
	//ADC����ת��ģʽ
	ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;
	//ADC�ⲿ����ת��
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	//ADC���ݶ��뷽ʽ
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	//ADCת��ͨ����
	ADC_InitStruct.ADC_NbrOfChannel=1;
	
	ADC_Init(ADC2,&ADC_InitStruct);
	
	//ƥ��ADCʱ��PCLK2��8��Ƶ,�� 9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	//����ADCͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ55.5��ʱ������
	ADC_RegularChannelConfig(ADC2,ADC_CHANNEL,1,ADC_SampleTime_55Cycles5);
	
	//�ж�ʹ�ܺ���
	//ADCת�����������жϣ����жϷ�������ж�ȡת��ֵ
	ADC_ITConfig(ADC2,ADC_IT_EOC,ENABLE);
	//����ADC,����ʼת��
	ADC_Cmd(ADC2,ENABLE);
	
	//�������ϵ�ʱִ��һ��ADCУ׼
	//��ʼ��ADC У׼�Ĵ���
	ADC_ResetCalibration(ADCx);
	//�ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADCx));
	
	//ADC��ʼУ׼
	ADC_StartCalibration(ADCx);
	//�ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADCx));
	
	
	//����û�в����ⲿ����������ʹ���������ADCת��
	ADC_SoftwareStartConvCmd(ADCx,ENABLE);
}
 
static void ADC_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	// ���ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
 
  // �����ж����ȼ�
  NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}



void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
	ADC_NVIC_Config();
}
