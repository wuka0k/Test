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
	//LCD 初始化
	ILI9341_Init ();  
	/* 配置SysTick 为1us中断一次 */
	SysTick_Init();
	//串口通信
	USART_Config();
	/*初始化DHT11的引脚*/
	DHT11_Init ();
	//蜂鸣器
	FENG_GPIO_Config();
	//按键
	KEY_GPIO_Config();
	//按键中断
	EXTI_Key_Config();
	//led
	LED_GPIO_Config();
	//ACD
	ADCx_Init();
	//呼吸灯
	TIMx_Breathing_Init();
 
	
	//其中0、3、5、6 模式适合从左至右显示文字，
	//不推荐使用其它模式显示文字	其它模式显示文字会有镜像效果			
	//其中 6 模式为大部分液晶例程的默认显示方向  
	ILI9341_GramScan ( 6 );
	
	//读取数据
	read_tem();
	
	//进场动画
	Eye();
	LCD_SetFont(&Font8x16);
	LCD_SetColors(RED,BLACK);
	ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* 清屏，显示全黑 */
	while ( 1 )
	{
		Temp();
		LCD_Test();
	}
}



/*用于测试各种液晶的函数*/
void LCD_Test(void)
{
	LCD_SetFont(&Font8x16);
	LCD_SetColors(BLUE,BLACK);
	ILI9341_DisplayStringEx(20,1*16,16,16,(uint8_t*)"湿度：",0);
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
	ILI9341_DisplayStringEx(20,5*16,16,16,(uint8_t*)"温度：",0);
	ILI9341_DisplayStringEx(20,6*16,32,32,(uint8_t*)T,0);
	LCD_SetTextColor(RED);
	ILI9341_DisplayStringEx(20,8*16,16,16,(uint8_t*)TMAX,0);
	
	//电压
	ADC_ConvertedValueLocal=(float)ADC_ConvertedValue/4096*3.3;
	if(ADC_ConvertedValueLocal>2)
	{
		LCD_SetTextColor(WHITE);
		sprintf(V,"Now AD value %f V",\
		ADC_ConvertedValueLocal);
		
		ILI9341_DisplayStringEx(20,10*16,16,16,(uint8_t*)V,0);
		ILI9341_DisplayStringEx(20,12*16,24,24,(uint8_t*)" 白天",0);
	}
	else
	{
		LCD_SetTextColor(BLUE);
		sprintf(V,"Now AD value %f V",\
		ADC_ConvertedValueLocal);
		
		ILI9341_DisplayStringEx(20,10*16,16,16,(uint8_t*)V,0);
		ILI9341_DisplayStringEx(20,12*16,24,24,(uint8_t*)" 黑夜",0);
	}

	
	//项目名称姓名
	LCD_SetTextColor(GREEN);
	ILI9341_DisplayStringEx(20,14*16,16,16,(uint8_t*)"ARM的智能家居监测系统",0);
	
  /* 画直线 */
	LCD_SetTextColor(RED);
  ILI9341_DrawLine(1,1,239,1);  
	ILI9341_DrawLine(1,305+11,239,305+11);
	//左
	ILI9341_DrawLine(1,1,1,305+11);
	//右
	ILI9341_DrawLine(239,1,239,305+11);
	
	LCD_SetTextColor(YELLOW);
  ILI9341_DrawLine(6,6,234,6);  
	ILI9341_DrawLine(6,305+6,234,305+6);
	//左
	ILI9341_DrawLine(6,6,6,305+6);
	//右
	ILI9341_DrawLine(234,6,234,305+6);
	
	LCD_SetTextColor(BLUE);
  ILI9341_DrawLine(11,11,229,11);  
	ILI9341_DrawLine(11,305+1,229,305+1); 
	//左
	ILI9341_DrawLine(11,11,11,305+1);
	//右
	ILI9341_DrawLine(229,11,229,305+1);
	
}


void Temp(void)
{
	DHT11_Data_TypeDef DHT11_Data;
	/*调用DHT11_Read_TempAndHumidity读取温湿度，若成功则输出该信息*/
	if( DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS)
	{
		sprintf(RH,"  %d.%d ％RH",\
		DHT11_Data.humi_int,DHT11_Data.humi_deci);
		sprintf(T,"  %d.%d ℃",\
		DHT11_Data.temp_int,DHT11_Data.temp_deci);		
		temperature=DHT11_Data.temp_int;
	}
		sprintf(TMAX,"温度 < %d ℃",\
		tmax);
}


//眼睛
void Eye(void)
{
	LCD_SetColors(YELLOW,BLACK);
  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* 清屏，显示全黑 */
	ILI9341_Clear(0,16*9,LCD_X_LENGTH,LCD_Y_LENGTH-16*9);	/* 清屏，显示全黑 */

	//欢迎使用
	ILI9341_DisplayStringEx(30,2*16,48,48,(uint8_t*)"欢迎使用",0);

	
	//中
	LCD_SetTextColor(RED);
  ILI9341_DrawCircle(60,200,50,0);
	ILI9341_DrawCircle(180,200,50,0);
	LCD_SetTextColor(GREEN);
  ILI9341_DrawCircle(60,200,20,1);                                                        
	ILI9341_DrawCircle(180,200,20,1); 
	Eyebrows();
	
	Delay_ms(1000);
	ILI9341_Clear(0,16*9,LCD_X_LENGTH,LCD_Y_LENGTH-16*9);	/* 清屏，显示全黑 */	
	
	//左
	LCD_SetTextColor(RED);
  ILI9341_DrawCircle(60,200,50,0);
	ILI9341_DrawCircle(180,200,50,0);
	LCD_SetTextColor(GREEN);
  ILI9341_DrawCircle(60-25,200,20,1);                                                        
	ILI9341_DrawCircle(180-25,200,20,1); 
	Eyebrows();
	
	Delay_ms(1000);
	ILI9341_Clear(0,16*9,LCD_X_LENGTH,LCD_Y_LENGTH-16*9);	/* 清屏，显示全黑 */	
	
	//上
	LCD_SetTextColor(RED);
  ILI9341_DrawCircle(60,200,50,0);
	ILI9341_DrawCircle(180,200,50,0);
	LCD_SetTextColor(GREEN);
  ILI9341_DrawCircle(60,200-25,20,1);                                                        
	ILI9341_DrawCircle(180,200-25,20,1); 
	Eyebrows();
		
	Delay_ms(1000);
	ILI9341_Clear(0,16*9,LCD_X_LENGTH,LCD_Y_LENGTH-16*9);	/* 清屏，显示全黑 */	
	
	//右
	LCD_SetTextColor(RED);
  ILI9341_DrawCircle(60,200,50,0);
	ILI9341_DrawCircle(180,200,50,0);
	LCD_SetTextColor(GREEN);
  ILI9341_DrawCircle(60+25,200,20,1);                                                        
	ILI9341_DrawCircle(180+25,200,20,1); 
	Eyebrows();
		
	Delay_ms(1000);
	ILI9341_Clear(0,16*9,LCD_X_LENGTH,LCD_Y_LENGTH-16*9);	/* 清屏，显示全黑 */	
	
	//下
	LCD_SetTextColor(RED);
  ILI9341_DrawCircle(60,200,50,0);
	ILI9341_DrawCircle(180,200,50,0);
	LCD_SetTextColor(GREEN);
  ILI9341_DrawCircle(60,200+25,20,1);                                                        
	ILI9341_DrawCircle(180,200+25,20,1); 
	Eyebrows();
		
	Delay_ms(1000);
	ILI9341_Clear(0,16*9,LCD_X_LENGTH,LCD_Y_LENGTH-16*9);	/* 清屏，显示全黑 */	
}


//眉毛
void Eyebrows(void)
{
	LCD_SetTextColor(YELLOW);
  ILI9341_DrawRectangle(30,120,60,30,1);
  ILI9341_DrawRectangle(150,120,60,30,1);
}
