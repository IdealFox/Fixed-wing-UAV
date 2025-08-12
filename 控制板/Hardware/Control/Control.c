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
#include "ADC.h"
#include "Key.h"
#include "LED.h"

struct NRF24L01_Send_Data Send_Data;

/** @brief	将AD值转换为PWM控制参数
  * @param	AD_value			AD值
  * @retval	PWM脉冲宽度		单位1us
  **/
u16 PWM_Set_M_value(u16 AD_value)
{
	u16 Data;
	if(AD_value<=400)
	{	return 800;}
	
	AD_value-=400;
	Data=1400*((float)AD_value/3400)+800;
	return Data;
}

/** @brief	将AD值转换为PWM控制参数
  * @param	AD_value1			AD值1			左右摇杆AD
	* @param	AD_value2			AD值2			上下摇杆AD
	* @param	Servo_value1	舵机1脉冲宽度地址
	* @param	Servo_value2	舵机2脉冲宽度地址
  **/
void PWM_Set_S_value(u16 AD_value1,u16 AD_value2,u16 *Servo_value1,u16 *Servo_value2)
{
	u16 Servo1=0;
	u16 Servo2=0;
	AD_value2-=300;

	//上下摇杆参数赋值
	Servo1=2000*((float)AD_value2/3500);				//PWM=ADC/ADC_Max
	Servo2=2000*((float)AD_value2/3500);
	
	//左右摇杆参数赋值
	if(AD_value1>=2150)
	{
		AD_value1-=2150;
		Servo1-=2000*((float)AD_value1/1750);
		Servo2+=2000*((float)AD_value1/1750);
	}
	else if(AD_value1<=2050)
	{
		AD_value1-=300;
		Servo1+=2000*(1-(float)AD_value1/1750);
		Servo2-=2000*(1-(float)AD_value1/1750);
	}

//	//左右摇杆参数赋值
//	if(AD_value1>=2200)
//	{
//		AD_value1-=2200;
//		Servo1=2000*((float)AD_value1/1700);
//		Servo2=2000-2000*((float)AD_value1/1700);
//	}
//	else if(AD_value1<=2000)
//	{
//		AD_value1-=300;
//		Servo1=2000*(1-(float)AD_value1/1700);
//		Servo2=2000*(1-(float)AD_value1/1700);
//	}
//	
//	Servo1+=2000*((float)AD_value2/3500);
//	Servo2+=2000*((float)AD_value2/3500);
	
	//参数防溢出
	if(Servo1>20000)Servo1=0;
	if(Servo1>2000)Servo1=2000;
	if(Servo2>20000)Servo2=0;
	if(Servo2>2000)Servo2=2000;		
	
	Servo1=2500-Servo1;
	Servo2+=500;
	
	*Servo_value1=Servo1;
	*Servo_value2=Servo2;
}
/** @brief	执行控制
  **/
void Control(void)
{  
	static u8 Motor_State=0;				//电机控制字节	0：停止		1：运行
	if(TEST_Motor_Control()==1)
	{	Motor_State=0;
		EALED_State(0);
	}
	if(TEST_Motor_Control()==0&&AD_Final_Value[1]<=400)
	{	Motor_State=1;
		EALED_State(1);
	}
	
	if(Motor_State==1)
	Send_Data.Servo[0]=PWM_Set_M_value(AD_Final_Value[1]);
	else if(Motor_State==0)
	Send_Data.Servo[0]=800;
	PWM_Set_S_value(AD_Final_Value[2],AD_Final_Value[3],&Send_Data.Servo[1],&Send_Data.Servo[2]);
}



















