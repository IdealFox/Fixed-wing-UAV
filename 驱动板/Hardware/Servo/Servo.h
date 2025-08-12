#ifndef __Servo_H
#define __Servo_H

void Servo_Init(u16 value1,u16 value2,u16 value3);							//PWM输出初始化

void TIM2_Interrupt_Init(u8 PreemptionPriorit,u8 SubPriority);	//TIM2定时中断初始化		10ms

#endif


