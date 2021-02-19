#ifndef _MechanicalArm_Service_H_
#define _MechanicalArm_Service_H_

#include "system_core.h"

#define Pi acos(-1)
#define Width_Unit 	11.667	//角度转脉宽单位

#define Width_Benchmark		1500	//脉宽基准

/***********************************
舵机1 1500中位  2550正位  450反位
舵机2 1500中位  2550前极限  450后极限
舵机3  1500中位  2550后极限  450前极限
舵机4  1500中位  2550后极限  450前极限
************************************/

static uint8_t MechanicalArm_State = 0;						//0:完成  1:进行中
static uint8_t MechanicalArm_Mode = 0;						//0:Inc控制 1:余弦定理控制
static uint8_t ArmLen[3] = {150,90,90};						//机械臂长度
static uint16_t ArmLen2[3] = {22500,8100,8100};				//长度平方,方便余弦定理的计算

static uint16_t Reset_Width[5] ={2550,2025,450,2025,800};				//复位脉宽
static uint16_t StateEnd_Width[5] = {2550,2025,450,2025,800};			//状态最终脉宽
static uint16_t Target_Width[5] = {2550,2025,450,2025,800};			//当前周期目标脉宽

static uint8_t Width_IncReset[5] = {5,5,5,5,5};
static uint8_t Width_Inc[5] = {5,5,5,5,5};

/*******************对外接口*************************/
void MechanicalArm_Service(void);							//机械臂控制服务
void MechanicalArm_Reset(uint8_t mode);					//机械臂复位
uint8_t Read_MechanicalArmState(void);						//机械臂状态获取
void MechanicalArm_IncSet(uint16_t*Width,uint8_t*Inc);		//机械臂任务设置(Inc)
void MechanicalArm_IncAngleSet(int*angle,uint8_t*Inc);		//机械臂任务设置(Inc,角度制)
void MechanicalArm_LineSet(int*obj,int Speed);				//机械臂任务设置(Line)

void MechanicalArm_StateUpdata(void);						//运行状态更新
void MechanicalArm_WidthSet(uint16_t*Width);				//设置脉宽
uint16_t AngleToWidth(double Angle);						//角度转脉宽
void MechanicalArm_WidthInc(void);							//脉宽递增(模式0控制函数)
void MechanicalArm_LineClr(void);							//机械臂线性控制(模式1控制函数)

#endif

