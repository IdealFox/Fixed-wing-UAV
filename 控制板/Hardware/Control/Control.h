#ifndef __Control_H
#define __Control_H

struct NRF24L01_Send_Data			//NRF24L01待发区结构体
{
	u16 Servo[3];								//控制参数
	u32 verify; 								//校验位
	u8 Air_Data[32];						//空字节，占位置用
};

extern struct NRF24L01_Send_Data Send_Data;

void Control(void);						//根据NRF24L01接收数据执行控制
void Control_RESET(void);			//控制参数复位


#endif


