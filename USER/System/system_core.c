#include "system_core.h"

/*********系统初始化&系统任务*****************/
void PCB_System_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//驱动初始化
	SysSecBeat_Config(10,72);		//系统初始化辅助心跳
	Usart_Config();
	Usart_DMA_Config();
	StreetMotor_Init();
	Motor_Init();
	Gyroscope_Init();
	IIC_Init();
	OLED_Init();
	//将任务函数的指针载入任务列表
	TaskList_Config(1,1,1,PositionClr_Service);
	TaskList_Config(1,1,1,MechanicalArm_Service);
	TaskList_Config(1,0,1,FeedBack_Task);
	TaskList_Config(1,0,1,System_Task);
	//系统进入待机
	SystemState_Set(1);
	Move_Set(Y,-300);
	SysTick_Config(5*72000);			//系统主心跳
	while(1)
	{
		uint8_t temp;
		for(temp = 0;TaskList[temp].Task_Addr!=NULL;temp++)
		{
			if(TaskList[temp].Enable!=0 && TaskList[temp].RunType ==0)
				TaskList[temp].Task_Addr();
		}
	}
}

void TaskList_Config(uint8_t Enable,uint8_t RunType,uint8_t TaskType,void (*Task)(void))
{
	TaskList[TaskNum].Enable = Enable;
	TaskList[TaskNum].RunType = RunType;
	TaskList[TaskNum].TaskType = TaskType;
	TaskList[TaskNum].Task_Addr = Task;
	TaskNum++;
}

void TaskList_Load(void)
{
	
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

void FeedBack_Task(void)
{
	static uint8_t ShowStrFlag = 0;
	if(ShowStrFlag!=1)
	{
		OLED_ShowString("SysState:",0,0,1);
		OLED_ShowString("SysTime:",1,0,1);
		ShowStrFlag = 1;
	}
	OLED_ShowNum(SystemState,0,64,1);
	OLED_ShowNum((uint16_t)(SysTime/200),1,57,1);
}

void System_Task(void)
{	
}

/************系统对外接口*****************/
uint8_t SystemState_Set(uint8_t state)
{
	if(state<5)
		SystemState = state;
	return SystemState;
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
	uint8_t temp;
	SysTime++;
	for(temp=0;TaskList[temp].Task_Addr!=NULL;temp++)
	{
		if(TaskList[temp].Enable!=0 && TaskList[temp].RunType ==1)
			TaskList[temp].Task_Addr();
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

