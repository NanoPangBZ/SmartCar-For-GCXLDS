#ifndef _TASK_CLR_H_
#define _TASK_CLR_H_

#include "system_core.h"

//任务控制块
typedef struct
{
	uint8_t Enable;	//任务使能
	uint8_t TaskID;	//任务序号
	//uint16_t RunTime; //任务时序测试
	uint8_t TaskType;	//任务类型
	void (*Task_Addr)(void);	//任务函数指针
}TCB;



void SystemCycle_Run(void);	//系统执行周期
void Task_Run(void);			//执行任务清单
void TaskList_Clr(void);		//任务控制
void TaskList_Config(void);		//任务清单建立

#endif


