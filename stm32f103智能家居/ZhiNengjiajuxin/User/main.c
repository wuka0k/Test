#include "stm32f10x.h"
#include "bsp_ili9341_lcd.h"
#include "bsp_spi_flash.h"
#include "bsp_SysTick.h"
#include "bsp_dht11.h"
#include "FENG.h"
#include "exti.h"
#include "key.h"
#include "bsp_led.h"
#include "stm32f10x_it.h"
#include "adc.h"
#include "bsp_breathing.h"
#include "bsp_i2c_ee.h"
#include "uart.h"

extern __IO uint16_t ADC_ConvertedValue;
float ADC_ConvertedValueLocal;
uint8_t write_buf[EEPROM_SIZE];
uint8_t read_buf[EEPROM_SIZE];
uint8_t testCNT;
char T[100]="0";
char RH[100]="0";
char TMAX[100]="30";
char V[100]="0";
uint32_t temperature=25;
uint32_t tmax=30;


static void LCD_Test(void);	
void Temp(void);
void Eye(void);
void Eyebrows(void);


int main(void)
{
	//LCD ��ʼ��
	ILI9341_Init ();  
	/* ����SysTick Ϊ1us�ж�һ�� */
	SysTick_Init();
	//����ͨ��
	USART_Config();
	/*��ʼ��DHT11������*/
	DHT11_Init ();
	//������
	FENG_GPIO_Config();
	//����
	KEY_GPIO_Config();
	//�����ж�
	EXTI_Key_Config();
	//led
	LED_GPIO_Config();
	//ACD
	ADCx_Init();
	//������
	TIMx_Breathing_Init();
 
	
	//����0��3��5��6 ģʽ�ʺϴ���������ʾ���֣�
	//���Ƽ�ʹ������ģʽ��ʾ����	����ģʽ��ʾ���ֻ��о���Ч��			
	//���� 6 ģʽΪ�󲿷�Һ�����̵�Ĭ����ʾ����  
	ILI9341_GramScan ( 6 );
	
	//��ȡ����
	read_tem();
	
	//��������
	Eye();
	LCD_SetFont(&Font8x16);
	LCD_SetColors(RED,BLACK);
	ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */
	while ( 1 )
	{
		Temp();
		LCD_Test();
	}
}



/*���ڲ��Ը���Һ���ĺ���*/
void LCD_Test(void)
{
	LCD_SetFont(&Font8x16);
	LCD_SetColors(BLUE,BLACK);
	ILI9341_DisplayStringEx(20,1*16,16,16,(uint8_t*)"ʪ�ȣ�",0);
	ILI9341_DisplayStringEx(20,2*16,32,32,(uint8_t*)RH,0);
	
	if(temperature>=tmax)
	{
		FENG(ON);
		LCD_SetTextColor(RED);
	}
	else
	{
		FENG(OFF);
	}
	ILI9341_DisplayStringEx(20,5*16,16,16,(uint8_t*)"�¶ȣ�",0);
	ILI9341_DisplayStringEx(20,6*16,32,32,(uint8_t*)T,0);
	LCD_SetTextColor(RED);
	ILI9341_DisplayStringEx(20,8*16,16,16,(uint8_t*)TMAX,0);
	
	//��ѹ
	ADC_ConvertedValueLocal=(float)ADC_ConvertedValue/4096*3.3;
	if(ADC_ConvertedValueLocal>2)
	{
		LCD_SetTextColor(WHITE);
		sprintf(V,"Now AD value %f V",\
		ADC_ConvertedValueLocal);
		
		ILI9341_DisplayStringEx(20,10*16,16,16,(uint8_t*)V,0);
		ILI9341_DisplayStringEx(20,12*16,24,24,(uint8_t*)" ����",0);
	}
	else
	{
		LCD_SetTextColor(BLUE);
		sprintf(V,"Now AD value %f V",\
		ADC_ConvertedValueLocal);
		
		ILI9341_DisplayStringEx(20,10*16,16,16,(uint8_t*)V,0);
		ILI9341_DisplayStringEx(20,12*16,24,24,(uint8_t*)" ��ҹ",0);
	}

	
	//��Ŀ��������
	LCD_SetTextColor(GREEN);
	ILI9341_DisplayStringEx(20,14*16,16,16,(uint8_t*)"ARM�����ܼҾӼ��ϵͳ",0);
	
  /* ��ֱ�� */
	LCD_SetTextColor(RED);
  ILI9341_DrawLine(1,1,239,1);  
	ILI9341_DrawLine(1,305+11,239,305+11);
	//��
	ILI9341_DrawLine(1,1,1,305+11);
	//��
	ILI9341_DrawLine(239,1,239,305+11);
	
	LCD_SetTextColor(YELLOW);
  ILI9341_DrawLine(6,6,234,6);  
	ILI9341_DrawLine(6,305+6,234,305+6);
	//��
	ILI9341_DrawLine(6,6,6,305+6);
	//��
	ILI9341_DrawLine(234,6,234,305+6);
	
	LCD_SetTextColor(BLUE);
  ILI9341_DrawLine(11,11,229,11);  
	ILI9341_DrawLine(11,305+1,229,305+1); 
	//��
	ILI9341_DrawLine(11,11,11,305+1);
	//��
	ILI9341_DrawLine(229,11,229,305+1);
	
}


void Temp(void)
{
	DHT11_Data_TypeDef DHT11_Data;
	/*����DHT11_Read_TempAndHumidity��ȡ��ʪ�ȣ����ɹ����������Ϣ*/
	if( DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS)
	{
		sprintf(RH,"  %d.%d ��RH",\
		DHT11_Data.humi_int,DHT11_Data.humi_deci);
		sprintf(T,"  %d.%d ��",\
		DHT11_Data.temp_int,DHT11_Data.temp_deci);		
		temperature=DHT11_Data.temp_int;
	}
		sprintf(TMAX,"�¶� < %d ��",\
		tmax);
}


//�۾�
void Eye(void)
{
	LCD_SetColors(YELLOW,BLACK);
  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */
	ILI9341_Clear(0,16*9,LCD_X_LENGTH,LCD_Y_LENGTH-16*9);	/* ��������ʾȫ�� */

	//��ӭʹ��
	ILI9341_DisplayStringEx(30,2*16,48,48,(uint8_t*)"��ӭʹ��",0);

	
	//��
	LCD_SetTextColor(RED);
  ILI9341_DrawCircle(60,200,50,0);
	ILI9341_DrawCircle(180,200,50,0);
	LCD_SetTextColor(GREEN);
  ILI9341_DrawCircle(60,200,20,1);                                                        
	ILI9341_DrawCircle(180,200,20,1); 
	Eyebrows();
	
	Delay_ms(1000);
	ILI9341_Clear(0,16*9,LCD_X_LENGTH,LCD_Y_LENGTH-16*9);	/* ��������ʾȫ�� */	
	
	//��
	LCD_SetTextColor(RED);
  ILI9341_DrawCircle(60,200,50,0);
	ILI9341_DrawCircle(180,200,50,0);
	LCD_SetTextColor(GREEN);
  ILI9341_DrawCircle(60-25,200,20,1);                                                        
	ILI9341_DrawCircle(180-25,200,20,1); 
	Eyebrows();
	
	Delay_ms(1000);
	ILI9341_Clear(0,16*9,LCD_X_LENGTH,LCD_Y_LENGTH-16*9);	/* ��������ʾȫ�� */	
	
	//��
	LCD_SetTextColor(RED);
  ILI9341_DrawCircle(60,200,50,0);
	ILI9341_DrawCircle(180,200,50,0);
	LCD_SetTextColor(GREEN);
  ILI9341_DrawCircle(60,200-25,20,1);                                                        
	ILI9341_DrawCircle(180,200-25,20,1); 
	Eyebrows();
		
	Delay_ms(1000);
	ILI9341_Clear(0,16*9,LCD_X_LENGTH,LCD_Y_LENGTH-16*9);	/* ��������ʾȫ�� */	
	
	//��
	LCD_SetTextColor(RED);
  ILI9341_DrawCircle(60,200,50,0);
	ILI9341_DrawCircle(180,200,50,0);
	LCD_SetTextColor(GREEN);
  ILI9341_DrawCircle(60+25,200,20,1);                                                        
	ILI9341_DrawCircle(180+25,200,20,1); 
	Eyebrows();
		
	Delay_ms(1000);
	ILI9341_Clear(0,16*9,LCD_X_LENGTH,LCD_Y_LENGTH-16*9);	/* ��������ʾȫ�� */	
	
	//��
	LCD_SetTextColor(RED);
  ILI9341_DrawCircle(60,200,50,0);
	ILI9341_DrawCircle(180,200,50,0);
	LCD_SetTextColor(GREEN);
  ILI9341_DrawCircle(60,200+25,20,1);                                                        
	ILI9341_DrawCircle(180,200+25,20,1); 
	Eyebrows();
		
	Delay_ms(1000);
	ILI9341_Clear(0,16*9,LCD_X_LENGTH,LCD_Y_LENGTH-16*9);	/* ��������ʾȫ�� */	
}


//üë
void Eyebrows(void)
{
	LCD_SetTextColor(YELLOW);
  ILI9341_DrawRectangle(30,120,60,30,1);
  ILI9341_DrawRectangle(150,120,60,30,1);
}
