/*
通过NRF24L01接收数据处理电机控制
数据包长度：32字节

数据包格式
位					执行操作							取值范围
0~1					无刷电机控制					500~2500
2~3					舵机1控制							500~2500
4~5					舵机2控制							500~2500

6~9					校验字节
*/

#include "stm32f10x.h"                  // Device header
#include "Control.h"
#include "Servo.h"
#include "Delay.h"

struct NRF24L01_Receive_Data Receive_Data;

/** @brief	执行控制
  **/
void Control(void)
{
	TIM_SetCompare1(TIM2,Receive_Data.Servo[0]);		
	TIM_SetCompare2(TIM2,Receive_Data.Servo[1]);
	TIM_SetCompare3(TIM2,Receive_Data.Servo[2]);
}

/** @brief	控制参数初始化
  **/
void	Control_RESET(void)
{
	Receive_Data.Servo[0]=800;
}

















