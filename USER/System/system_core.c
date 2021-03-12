#include "system_core.h"

/*********系统初始化&系统任务*****************/
void PCB_System_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//驱动初始化
	SysSecBeat_Config(10,72);		//系统初始化辅助心跳
	StreetMotor_Init();
	MechanicalArm_Reset();
	IIC_Init();
	OLED_Init();
	
	OLED_ShowString("SystemInit",0,0,2);
	
	Usart_Config();
	Usart_DMA_Config();
	Motor_Init();
	OpenMV_Init();
	OLED_ShowString("OpenMV ready",2,0,2);
	
	Gyroscope_Init();
	OLED_Clear();
	
	//将任务函数的指针载入任务列表
	TaskList_Config(1,1,1,PositionClr_Service);
	TaskList_Config(1,1,1,MechanicalArm_Service);
//	TaskList_Config(1,1,1,feedback_service);
	TaskList_Config(1,1,1,openmv_service);
//	TaskList_Config(1,1,2,debug_app_Task);
//	TaskList_Config(1,1,2,test_app_task);
	TaskList_Config(1,1,2,goods_app_Task);
	TaskList_Config(1,1,2,position_app_Task);
	TaskList_Config(1,1,2,main_app_Task);
	
	SystemState_Set(1);
	SysTick_Config(6*72000);			//系统主心跳
	
	while(1)
	{
		uint8_t temp;
		for(temp=0;ContinueTaskList[temp].Task_Addr!=NULL;temp++)
		{
			if(ContinueTaskList[temp].Enable)
				ContinueTaskList[temp].Task_Addr();
		}
	}
}

void TaskList_Config(uint8_t Enable,uint8_t RunType,uint8_t TaskType,void (*Task)(void))
{
	TCB temp;
	temp.Enable = Enable;
	temp.RunType = RunType;
	temp.TaskType = TaskType;
	temp.Task_Addr = Task;
	//根据RunType分配致相应任务列表
	if(RunType)
	{
		temp.TaskNumID = BeatTaskNum;
		BeatTaskList[BeatTaskNum++] = temp;
	}
	else
	{
		temp.TaskNumID = ContinueTaskNum;
		ContinueTaskList[ContinueTaskNum++] = temp;
	}
	
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

void SystemBeat_Task(void)
{
}

void SystemConti_Task(void)
{	
}

/************系统对外接口*****************/
uint8_t SystemState_Set(uint8_t state)
{
	if(state<5)
		SystemState = state;
	return SystemState;
}

void Task_Cmd(void(*Task)(void),uint8_t Enable)
{
	TCB*temp;
	temp = TCB_AddrGet(Task);
	if(temp!=NULL)
		temp->Enable = Enable;
}

TCB*TCB_AddrGet(void(*Task)(void))
{
	uint8_t temp;
	for(temp=0;temp<BeatTaskNum+1;temp++)
	{
		if(Task == BeatTaskList[temp].Task_Addr)
			return &BeatTaskList[temp];
	}
	for(temp=0;temp<ContinueTaskNum+1;temp++)
	{
		if(Task == ContinueTaskList[temp].Task_Addr)
			return &ContinueTaskList[temp];
	}
	return NULL;
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
	for(temp=0;BeatTaskList[temp].Task_Addr!=NULL;temp++)
	{
		if(BeatTaskList[temp].Enable)
			BeatTaskList[temp].Task_Addr();
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

