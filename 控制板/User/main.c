#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Interrupt.h"
#include "OLED.h"
#include "ADC.h"
#include "Key.h"
#include "NRF24L01.h"
#include "Control.h"
#include "SPI.h"
#include "Timer.h"
#include "BEEP.h"
#include "USART.h"
#include "LED.h"
#include "lcd.h"
 
u8 EN_AA_State;					//接收应答状态字节		0：接收到应答		1：未接收到应答			2:出现异常

int main (void)
{
	LED_Init();						//LED初始化
	RunLED_State(0);			//开启运行指示灯
	Key_Init();						//按键初始化
	BEEP_Init();					//蜂鸣器初始化
	USART1_Init();				//串口初始化
	TIM3_Init();					//TIM3初始化		20ms溢出
	ADC1_Init();					//ADC1初始化
	ADC1_Start();					//ADC1开始转换
	
	SPI1_Init();					//SPI1初始化
	NRF24L01_Init();			//NRF24L01初始化 
//	LCD_Init();						//LCD初始化
//	LCD_Clear();
	
	Interrupt_Init();			//中断初始化
//	LCD_ShowString(10,10,"OK",RED,WHITE,10,0);
	while(1) 
	{
		Compute_AD_Final_Value();												//指数加权移动平均滤波器算法
		Control();																			//控制计算
		while(NRF24L01_State==5){Delay_us(1);}					//等待数据发送完成
		if(NRF24L01_State==6){EN_AA_State=0;}						//数据接收正常
		else if(NRF24L01_State==7){EN_AA_State=1;}			//数据接收异常
		else if(NRF24L01_State==8){EN_AA_State=2;}			//其他异常
		USART1_SendPacket(0XAB,0XCD,(u8*)&Send_Data.Servo[0],6);			//串口发送数据
		NRF24L01_Send_Data((u8*)&Send_Data.Servo[0]);		//NRF24L01发送数据
		Send_Data.verify++;															//校验位自增
	}
}




