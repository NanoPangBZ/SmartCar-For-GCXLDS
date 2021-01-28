#ifndef	_SYSTEM_CORE_H_
#define _SYSTEM_CORE_H_

#include "stm32f10x.h"
#include <stdio.h>
#include "usart.h"
#include "iic.h"
#include "motor_init.h"
#include "motor_driver.h"
#include "street_motor.h"
#include "MechanicalArm_Clr.h"
#include "position_service.h"
#include "gyroscope.h"
#include "oled.h"
#include "DataScope_DP.h"
#include "main_app.h"
#include "debug_app.h"

//任务控制块
typedef struct
{
	uint8_t Enable;
	uint8_t RunType;		//0:在死循环whil(1)中执行   1:在系统中断时执行
	uint8_t TaskType;		//0:Driver   1.Service   2.App   3.System
	//uint32_t RunTime;	//测试任务时序
	void (*Task_Addr)(void);
}TCB;

/***************系统时间***************/
static uint32_t SysTime = 0;
static uint32_t SysSubTime = 0;
/***************系统状态***************/
static uint8_t SystemState = 0;		//0:初始化  1:待机  2:运行  3:串口调试
static uint8_t TaskNum = 0;			//任务总量
static TCB TaskList[32];			//任务总表
static void(*SysBeatTask[16])(void);		//系统心跳任务列表
static void(*ContinueTask[16])(void);		//连续任务
/*********系统初始化&系统任务*****************/
void PCB_System_Init(void);
void SysSecBeat_Config(uint16_t A,uint16_t Pre);
void System_Task(void);
void FeedBack_Task(void);
void System_Task(void);		//主要是系统状态更新,任务使能管理
void TaskList_Config(uint8_t Enable,uint8_t RunType,uint8_t TaskType,void (*Task)(void));
void TaskList_Load(void);
/************系统对外接口*****************/
uint32_t Read_SysTime(void);
uint32_t Read_SysSubTime(void);
uint8_t Read_SystemState(void);
uint8_t SystemState_Set(uint8_t state);
/****************中断*****************/
void SysTick_Handler(void);
void TIM7_IRQHandler(void);

#endif

