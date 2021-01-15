#include "system_core.h"

/********************系统初始化***********************/
void PCB_System_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SysSecBeat_Config(50,72);		//系统初始化辅助心跳
	Usart_Config();
	Usart_DMA_Config();
	StreetMotor_Init();
	Motor_Init();
	Gyroscope_Init();
	SystemState = 2;
	SysTick_Config(5*72000);			//系统主心跳
}

void SysSecBeat_Config(uint16_t A,uint16_t Pre)
{
	TIM_TimeBaseInitTypeDef	TIM_InitStruct;
	NVIC_InitTypeDef	NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
        
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Prescaler = Pre;
	TIM_InitStruct.TIM_Period = A;
	TIM_InitStruct.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM7,&TIM_InitStruct);
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	
	NVIC_Init(&NVIC_InitStruct);
	TIM_Cmd(TIM7,ENABLE);
}

uint8_t Read_SystemState(void)
{
	return SystemState;
}

uint32_t Read_SysTime(void)
{
	return SysTime;
}

uint32_t Read_SysSubTime(void)
{
	return SysSubTime;
}

/*********************中断****************************/
void SysTick_Handler(void)
{
	SysTime++;
	switch(SystemState)
	{
		case 0:break;
		case 1:break;
		case 2:break;
		case 3:break;
		default:break;
	}
}

void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7,TIM_IT_Update) ==SET)
	{
		SysSubTime++;
		TIM_ClearITPendingBit(TIM7,TIM_IT_Update);
	}
}

