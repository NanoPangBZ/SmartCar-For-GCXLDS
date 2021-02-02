#ifndef	_SYSTEM_CORE_H_
#define _SYSTEM_CORE_H_

#include "stm32f10x.h"
#include <stdio.h>
#include "usart.h"
#include "iic.h"
#include "motor_init.h"
#include "motor_driver.h"
#include "street_motor.h"
#include "MechanicalArm_Service.h"
#include "position_service.h"
#include "openmv_service.h"
#include "wifi_service.h"
#include "vofa_p.h"
#include "gyroscope.h"
#include "oled.h"
#include "main_app.h"
#include "debug_app.h"

//任务控制块
typedef struct
{
	uint8_t Enable;
	uint8_t RunType;		//0:在死循环whil(1)中执行   1:在系统中断时执行
	uint8_t TaskType;		//0:Driver   1.Service   2.App   3.System
	uint8_t TaskNumID;	//由系统分配(执行顺序)
	//uint32_t RunTime;	//测试任务时序
	void (*Task_Addr)(void);
}TCB;

/***************系统时间***************/
static uint32_t SysTime = 0;
static uint32_t SysSubTime = 0;
/***************系统状态***************/
static uint8_t SystemState = 0;		//0:初始化  1:待机  2:运行  3:串口调试
/*****************任务列表*****************/
static uint8_t BeatTaskNum = 0;
static uint8_t ContinueTaskNum = 0;
static TCB BeatTaskList[32];				//心跳任务总表
static TCB ContinueTaskList[32];			//连续任务总表
/*********系统初始化*****************/
void PCB_System_Init(void);
void SysSecBeat_Config(uint16_t A,uint16_t Pre);
/***********系统相关任务**********/
void SystemBeat_Task(void);	//系统周期任务
void SystemConti_Task(void);	//系统状态切换任务
void OLED_FB_Task(void);	//通过OLED反馈系统信息
//任务列表配置
void TaskList_Config(uint8_t Enable,uint8_t RunType,uint8_t TaskType,void (*Task)(void));
/************系统对外接口*****************/
uint32_t Read_SysTime(void);
uint32_t Read_SysSubTime(void);
uint8_t Read_SystemState(void);
uint8_t SystemState_Set(uint8_t state);
TCB* TCB_AddrGet(void(*Task)(void));				//返回TCB地址,自行更改
void Task_Cmd(void(*Task)(void),uint8_t Enable);		//任务使能控制
/****************中断*****************/
void SysTick_Handler(void);
void TIM7_IRQHandler(void);

#endif

