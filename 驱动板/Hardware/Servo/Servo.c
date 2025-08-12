#include "stm32f10x.h"                  // Device header
#include "Servo.h"

//PWM输出定时器TIM2
/*引脚定义		无重映像
	
		CH1					PA0
		CH2					PA1
		CH3					PA2
*/

/** @brief	GPIO初始化	PA0,PA1,PA2
  * @param	无
  * @retval	无
  **/
void Servo_GPIO_Out_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);			//开启GPIOA时钟
	
	//GPIO初始化结构体
	GPIO_InitTypeDef	GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode		=GPIO_Mode_AF_PP;															//复用推挽输出，由TIM2控制
	GPIO_InitStruct.GPIO_Pin		=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;						//0,1,2端口
	GPIO_InitStruct.GPIO_Speed	=GPIO_Speed_50MHz;														//速度50MHz
	GPIO_Init(GPIOA,&GPIO_InitStruct);																				//初始化GPIOA
}

/** @brief	TIM2初始化		100Hz		10ms
  * @param	无
  * @retval	无
  **/
void TIM2_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);			//开启TIM2时钟
	
	//时基单元初始化结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision			=TIM_CKD_DIV1;					//1分频
	TIM_TimeBaseInitStruct.TIM_CounterMode				=TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInitStruct.TIM_Period							=10000;									//ARR重装寄存器，10ms计时，100Hz
	TIM_TimeBaseInitStruct.TIM_Prescaler					=72-1;									//PSC预分频器，72分频
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter	=0;											//重复计数器关
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);												//初始化TIM2
}

/** @brief	PWM输出初始化
	* @param	value1		PWM1脉冲宽度初始值		1us精度
	* @param	value2		PWM2脉冲宽度初始值		1us精度
	* @param	value3		PWM3脉冲宽度初始值		1us精度
  **/
void Servo_Init(u16 value1,u16 value2,u16 value3)
{
	Servo_GPIO_Out_Init();							//GPIO初始化
	TIM2_Init();												//TIM2初始化 
	
	//输出比较结构体初始化
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);												//结构体内所有参数赋初始值
	TIM_OCInitStruct.TIM_OCMode				=	TIM_OCMode_PWM1;				//PWM1输出模式
	TIM_OCInitStruct.TIM_OCPolarity		=	TIM_OCPolarity_High;		//输出极性为高电平
	TIM_OCInitStruct.TIM_OutputState	=	TIM_OutputState_Enable;	//输出使能
	
	
	TIM_OCInitStruct.TIM_Pulse				=	value1;			//CH通道1设置
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);						//初始化CH1通道
	
	TIM_OCInitStruct.TIM_Pulse				=	value2;			//CH通道2设置
	TIM_OC2Init(TIM2,&TIM_OCInitStruct);						//初始化CH2通道
	
	TIM_OCInitStruct.TIM_Pulse				=	value3;			//CH通道3设置	
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);						//初始化CH3通道
	
	TIM_Cmd(TIM2,ENABLE);			//开启TIM2
}

/** @brief	TIM2定时中断初始化		10ms
  * @param	PreemptionPriorit			抢占优先级
  * @param	SubPriority						响应优先级
  **/
void TIM2_Interrupt_Init(u8 PreemptionPriorit,u8 SubPriority)
{
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);														//清除中断标志位
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);															//开启中断
	
	//NVIC结构体配置
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel										= TIM2_IRQn;				//定时器中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd								= ENABLE;						//使能NVIC
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= PreemptionPriorit;//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority				= SubPriority;			//响应优先级
	NVIC_Init(&NVIC_InitStruct);
}








