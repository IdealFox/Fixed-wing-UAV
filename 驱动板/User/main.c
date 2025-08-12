#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Servo.h"
#include "NRF24L01.h"
#include "Control.h"
#include "SPI.h"
#include "Interrupt.h"

void Servo_Control_Init(void);

int main(void)
{
	
	LED_Init();							//指示灯初始化
	LED1_State(0); 					//开启运行指示灯
	SPI1_Init();						//硬件SPI1初始化

	while(NRF24L01_Init())	//NRF24L01初始化
	{	LED2_State(0);}
	LED2_State(1);
	
	
	
	Servo_Init(800,1500,1500);
	Interrupt_Init();				//中断初始化
	
	Receive_Data.Servo[0]=800;
	Receive_Data.Servo[1]=1500;
	Receive_Data.Servo[2]=1500;
	
	while(1)
	{
		Control();
	}
		
}



