#include "stm32f10x.h"                  // Device header
#include "Timer.h"


/** @brief	TIM3初始化，内部时钟，20ms,中断配置
  * @retval	无
  **/
void TIM3_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);										//使能TIM6
	
	TIM_InternalClockConfig(TIM3);																				//内部时钟
	
	//时基单元初始化结构体
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision			=	TIM_CKD_DIV1;					//1分频
	TIM_TimeBaseInitStruct.TIM_CounterMode				=	TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInitStruct.TIM_Period							=	200-1;								//ARR重装寄存器值
	TIM_TimeBaseInitStruct.TIM_Prescaler					=	7200-1;								//PSC预分屏器值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter	=	0;										//重复计数器关，仅高级定时器有效
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);												//初始化TIM3
	
	TIM_Cmd(TIM3,ENABLE);																									//开启TIM3
}

/** @brief	TIM3中断初始化
  * @param	Priority			抢占优先级
  * @param	SubPriority		响应优先级
  **/
void TIM3_Interrupt_Init(u8 Priority,u8 SubPriority)
{
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);														//清除中断标志位，防止开启中断后立刻进入中断
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);															//开启中断
	
	//NVIC初始化结构体
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel										=	TIM3_IRQn;				//TIM6通道
	NVIC_InitStruct.NVIC_IRQChannelCmd								=	ENABLE;						//启用中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	=	Priority;					//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority				=	SubPriority;			//响应优先级
	NVIC_Init(&NVIC_InitStruct);																					//初始化NVIC
}


/** @brief	TIM3初始化，内部时钟，200us,中断配置
  * @param	Priority			抢占优先级
	 * @param	SubPriority		响应优先级
  * @retval	无
  **/
void TIM2_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);										//使能TIM6
	
	TIM_InternalClockConfig(TIM2);																				//内部时钟
	
	//时基单元初始化结构体
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision			=	TIM_CKD_DIV1;					//1分频
	TIM_TimeBaseInitStruct.TIM_CounterMode				=	TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInitStruct.TIM_Period							=	2-1;									//ARR重装寄存器值
	TIM_TimeBaseInitStruct.TIM_Prescaler					=	7200-1;								//PSC预分屏器值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter	=	0;										//重复计数器关，仅高级定时器有效
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);												//初始化TIM2
	
	TIM_Cmd(TIM2,ENABLE);																									//开启TIM2
}

/** @brief	TIM2中断初始化
  * @param	Priority			抢占优先级
  * @param	SubPriority		响应优先级
  **/
void TIM2_Interrupt_Init(u8 Priority,u8 SubPriority)
{
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);														//清除中断标志位，防止开启中断后立刻进入中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);															//开启中断
	
	//NVIC初始化结构体
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel										=	TIM2_IRQn;				//TIM6通道
	NVIC_InitStruct.NVIC_IRQChannelCmd								=	ENABLE;						//启用中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	=	Priority;					//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority				=	SubPriority;			//响应优先级
	NVIC_Init(&NVIC_InitStruct);																					//初始化NVIC
}


