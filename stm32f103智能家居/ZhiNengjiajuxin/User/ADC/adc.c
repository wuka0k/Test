#include "adc.h"

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//打开ADC IO端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//配置ADC IO引脚模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	//必须为模拟输入
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	
	//初始化ADC IO
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

static void ADCx_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
	
	//ADC转换的工作模式
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;
	//ADC转换的扫描模式
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;
	//ADC连续转换模式
	ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;
	//ADC外部触发转换
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	//ADC数据对齐方式
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	//ADC转换通道数
	ADC_InitStruct.ADC_NbrOfChannel=1;
	
	ADC_Init(ADC2,&ADC_InitStruct);
	
	//匹置ADC时钟PCLK2的8分频,即 9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	//配置ADC通道转换顺序为1，第一个转换，采样时间为55.5个时钟周期
	ADC_RegularChannelConfig(ADC2,ADC_CHANNEL,1,ADC_SampleTime_55Cycles5);
	
	//中断使能函数
	//ADC转换结束产生中断，在中断服务程序中读取转化值
	ADC_ITConfig(ADC2,ADC_IT_EOC,ENABLE);
	//开启ADC,并开始转换
	ADC_Cmd(ADC2,ENABLE);
	
	//建议在上电时执行一次ADC校准
	//初始化ADC 校准寄存器
	ADC_ResetCalibration(ADCx);
	//等待校准寄存器初始化完成
	while(ADC_GetResetCalibrationStatus(ADCx));
	
	//ADC开始校准
	ADC_StartCalibration(ADCx);
	//等待校准完成
	while(ADC_GetCalibrationStatus(ADCx));
	
	
	//由于没有采用外部触发，所以使用软件触发ADC转换
	ADC_SoftwareStartConvCmd(ADCx,ENABLE);
}
 
static void ADC_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	// 优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
 
  // 配置中断优先级
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
