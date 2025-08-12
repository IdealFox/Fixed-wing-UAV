#include "stm32f10x.h"                  // Device header
#include "LED.h"

/** @brief	LED初始化函数
  * @param	无
  * @retval	无
  **/
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode		=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin		=GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed	=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin		=GPIO_Pin_2;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_SET);
}

/** @brief	更改LED1状态
  * @param	0，LED关闭，其他，LED开启
  **/
void LED1_State(u8 state)
{
	if(state==0)
	{	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);}
	else
	{	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);}
}

/** @brief	更改LED2状态
  * @param	0，LED关闭，其他，LED开启
  **/
void LED2_State(u8 state)
{
	if(state==0)
	{	GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);}
	else
	{	GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_SET);}
}


