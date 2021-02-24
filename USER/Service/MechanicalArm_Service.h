#ifndef _MechanicalArm_Service_H_
#define _MechanicalArm_Service_H_

#include "system_core.h"

#define HZJ 57.3	//角度转弧度
#define Width_Unit 	11.667	//角度转脉宽单位

#define Width_Benchmark		1500	//脉宽基准

static uint8_t MechanicalArm_Mode = 0;	//0:Inc  1:Line
static uint8_t MechanicalArm_State = 0;	//0:End  1:Run

/***********************************
舵机1 1500中位  2550正位  450反位
舵机2 1500中位  2550前极限  450后极限
舵机3  1500中位  2550后极限  450前极限
舵机4  1500中位  2550后极限  450前极限
************************************/
static uint8_t ArmLen[3] = {105,90,100};						//机械臂长度
static uint16_t ArmLen2[3] = {11025,8100,10000};				//长度平方,方便余弦定理的计算

static uint16_t Reset_Width[5] ={2550,2025,450,2025,800};				//复位脉宽
static uint16_t StateEnd_Width[5] = {2550,2025,450,2025,800};			//状态最终脉宽
static uint16_t Target_Width[5] = {2550,2025,450,2025,800};			//当前周期脉宽
static uint8_t MechanicalArm_Inc[5] = {1,1,1,1,1};						//周期脉宽变化最大值
static int MechanicalArm_Position[2] = {0,0};							//机械臂位置
static int MechanicalArm_Speed = 1;								//线性控制下的速度

static uint16_t Claw_Width[3] = {400,600,1250};		//机械爪三态脉宽 0:全张 1:半张 2:闭合

/*******************对外接口*************************/
void MechanicalArm_Service(void);								//机械臂控制服务
void MechanicalArm_Reset(uint8_t mode);						//机械臂复位
void ClawClr(uint8_t state,uint8_t Inc);							//机械抓控制
void MechanicalArm_PositionLineSet(int len,int hight,uint8_t speed);	//线性控制设置
void MechanicalArm_PositionIncSet(int len,int hight,uint8_t*Inc);		//曾量控制设置
void MechanicalArm_PositionSet(int len,int hight);					//跃进控制
void MechanicalArm_BaceAngleIncSet(double angle,uint8_t Inc);	//底盘增量控制设置

void MechanicalArm_WidthInc(void);							//目标脉宽增长
double*CosinAngle_Config(int len,int hight);					//余弦定理计算各个舵机角度
void MechanicalArm_WidthSet(uint16_t*Width);				//设置脉宽
uint16_t AngleToWidth(double Angle);						//角度转脉宽

#endif


/*********************************
外部->StateEnd_Width
MechanicalArm_xxxSet载入Target_Width
MechanicalArm_WidthSet再载入相关寄存器
***********************************/

