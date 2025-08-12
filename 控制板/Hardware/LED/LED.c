#include "stm32f10x.h"                  // Device header
#include "LED.h"

/** @brief	LED初始化
  **/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//初始化结构体
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_14|GPIO_Pin_15);
}

/** @brief	运行指示LED显示状态
	* @param	0，灭		1，亮
  **/
void RunLED_State(u8 state)
{
	if(state)
	{	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);}
	else
	{	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);}
}

/** @brief	油门指示LED显示状态
	* @param	1，灭		0，亮
  **/
void EALED_State(u8 state)
{
	if(state)
	{	GPIO_WriteBit(GPIOB,GPIO_Pin_15,Bit_RESET);}
	else
	{	GPIO_WriteBit(GPIOB,GPIO_Pin_15,Bit_SET);}
}

/** @brief	接收应答LED显示状态
	* @param	1，灭		0，亮
  **/
void EN_AA_LED_State(u8 state)
{
	if(state)
	{	GPIO_WriteBit(GPIOB,GPIO_Pin_14,Bit_RESET);}
	else
	{	GPIO_WriteBit(GPIOB,GPIO_Pin_14,Bit_SET);}
}







