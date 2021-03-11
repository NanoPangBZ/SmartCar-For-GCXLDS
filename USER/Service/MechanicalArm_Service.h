#ifndef _MechanicalArm_Service_H_
#define _MechanicalArm_Service_H_

#include "system_core.h"

#define Width_Unit 	11.111	//角度转脉宽单位
#define HZJ			57.32	//弧度转角度系数

#define Width_Benchmark		1500	//脉宽中位

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

static uint16_t Reset_Width[5] ={1500,1000,500,1000,800};				//复位脉宽
static uint16_t Target_Width[5] = {1500,1000,500,1000,800};			//目标脉宽
static uint8_t MechanicalArm_Inc[5] = {1,1,1,1,1};						//周期脉宽变化最大值

static int MechanicalArm_TargetPosition[2] = {0,0};
static int MechanicalArm_Position[2] = {0,0};

static uint16_t Claw_Width[3] = {400,600,1300};		//机械爪三态脉宽 0:全张 1:半张 2:闭合

/*******************对外接口*************************/
void MechanicalArm_Service(void);								//机械臂控制服务
void MechanicalArm_Reset(void);								//机械臂复位
void ClawClr(uint8_t state,uint8_t Inc);							//机械抓控制
void TargetWidth_Set(uint16_t width,uint8_t inc,uint8_t num);		//目标脉宽设置(单个)
void MechanicalArm_PositionSet(int len,int hight);					//位置设置
void MechanicalArm_PostionLineSet(int slen,int shight,int elen,int ehight);	//总线平移
uint8_t Read_MechanicalArmState(void);

void MechanicalArm_StateCheck(void);
void MechanicalArm_PositionInc(void);						//位置线性控制
void MechanicalArm_WidthInc(void);							//脉宽自增
double*Cosin_AngleConfig(int len,int hight);					//余弦定理计算
void AngleCheck(double*angle);							//角度检查
uint16_t AngleToWidth(double angle);						//角度转脉宽
void MechanicalArm_WidthInc(void);							//目标脉宽增长

#endif


/*********************************
外部->StateEnd_Width
MechanicalArm_xxxSet载入Target_Width
MechanicalArm_WidthSet再载入相关寄存器
***********************************/

