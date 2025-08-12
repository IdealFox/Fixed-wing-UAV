#include "stm32f10x.h"                  // Device header
#include "Interrupt.h"
#include "NRF24L01.h"
#include "Control.h"
#include "LED.h"
#include "Timer.h"
#include "BEEP.h"

/** @brief	中断初始化
  **/
void Interrupt_Init(void)
{
	//中断组选择
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//NVIC中断组2
	
	//中断初始化
	NRF24L01_Interrupt_Init(2,1);											//NRF24L01中断初始化
	TIM3_Interrupt_Init(1,1);													//TIM3初始化		20ms溢出
}

/*
↓↓↓↓↓↓↓↓↓↓中断函数↓↓↓↓↓↓↓↓↓↓
													*/
/** @brief	NRF24L01外部中断函数
  **/
void EXTI1_IRQHandler(void)
{	
	EXTI_ClearITPendingBit(EXTI_Line1);								//清除中断标志位
	u8 Status,State;
	Status=NRF24L01_Read_STATUS();										//获取STATUS参数
	NRF24L01_W_Data(W_REGISTER|STATUS,Status);				//清除STATUS标志位
	
	if(Status==0XFF||Status==0X00){	State=0;}					//状态0，出现异常
	else if(Status&RX_DR){	State=1;NRF24L01_State=1;}//状态1，接收完成中断
	else if(Status&TX_DS){	State=2;}									//状态2，发送完成中断
	else if(Status&MAX_RT){	State=3;}									//状态3，最大重发中断
	
	switch(State)																			//执行各状态对应指令
	{	
		case 0:	NRF24L01_State=8;												//状态异常
						break;
		case 1:	NRF24L01_Receive_Data((u8*)&Send_Data.Servo[0]);//接收数据
						break;
		case 2: NRF24L01_Send_OK();											//发送完成操作
						break;
		case 3:	NRF24L01_Send_Error();									//发送失败操作
						break;
	}
}

extern u8 EN_AA_State;

/** @brief	TIM3外部中断函数		20ms
  **/
void TIM3_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);				//清除中断标志位
	static u8 LED_Time,BEEP_Time;

	switch(EN_AA_State)
	{
		case 0:	EN_AA_LED_State(0);LED_Time=0;					//接收应答正常，熄灭LED
						BEEP_State(1);BEEP_Time=0;							//关闭蜂鸣器
						break;
		
		case 1:	LED_Time++;LED_Time%=11;								//接收应答异常，LED闪烁
						if(LED_Time==0){EN_AA_LED_State(1);}
						else if(LED_Time==5){EN_AA_LED_State(0);}
					
						if(BEEP_Time==0){BEEP_State(0);}
						else if(BEEP_Time==5){BEEP_State(1);}
						else if(BEEP_Time==10){BEEP_State(0);}
						else if(BEEP_Time==15){BEEP_State(1);}
						BEEP_Time++;BEEP_Time%=31;
						
						break;
		case 2:	EN_AA_LED_State(1);BEEP_State(1);break;	//其他异常，LED常亮，蜂鸣器常开
	}
	
}


