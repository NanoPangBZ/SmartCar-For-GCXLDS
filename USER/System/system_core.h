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
#include "position_clr.h"
#include "gyroscope.h"
#include "oled.h"
#include "DataScope_DP.h"
#include "debug_port.h"
#include "main_app.h"

/***************系统时间***************/
static uint32_t SysTime = 0;
static uint32_t SysSubTime = 0;
/***************系统状态***************/
static uint8_t SystemState = 0;		//0:初始化  1:待机  2:运行  3:串口调试
/*********系统初始化&系统任务*****************/
void PCB_System_Init(void);
void SysSecBeat_Config(uint16_t A,uint16_t Pre);
void System_Task(void);
void FeedBack_Task(void);
void StateUpdata_Task(void);
/************系统对外接口*****************/
uint32_t Read_SysTime(void);
uint32_t Read_SysSubTime(void);
uint8_t Read_SystemState(void);
uint8_t SystemState_Set(uint8_t state);
/****************中断*****************/
void SysTick_Handler(void);
void TIM7_IRQHandler(void);

#endif

