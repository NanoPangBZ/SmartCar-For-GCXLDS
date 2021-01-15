#ifndef _MechanicalArm_Clr_H_
#define _MechanicalArm_Clr_H_
//机械臂控制

#include "system_core.h"

#define	Pi	acos(-1)					//圆周率
#define	StartValue		1480		//机械臂中位脉宽
#define	WidthInc_Max	7

/*************************************
初始化
2535
925
400
2490
300
夹上层
2591
1561
374
1780
1348
放上层
1559
819
2388
786
300
*************************************/

static uint16_t* street_width[6] = {(uint16_t*)&TIM3->CCR1 , (uint16_t*)&TIM3->CCR2,
							(uint16_t*)&TIM3->CCR3 , (uint16_t*)&TIM3->CCR4,
							(uint16_t*)&TIM2->CCR1 , (uint16_t*)&TIM2->CCR2 };
							
static uint8_t ArmLen[3] = {150,90,90};						//机械臂各部分长度(从下往上)	mm
static uint16_t ArmLen2[3] = {22500,8100,8100};				//机械长平方,方便余弦定理计算
static uint16_t Reset_Value[5] ={2535,925,400,2490,300};		//机械臂归位脉宽
static uint16_t Width_Target[5] = {2535,925,400,2490,300};		//目标脉宽
static uint16_t WidthInc[5] = {3,3,3,3,6};						//5ms脉宽增量

void Angle_Realize(void);								//驱动机械臂
//uint16_t Angle_Transf(uint8_t num,int angle);				//角度转脉宽
//void Angle_Config(int Yaw,int len,int hight);		//根据目标位置设定各个舵机角度  余弦定理	mm
void MechanicalArm_Reset(uint8_t mode);				//机械臂归位	0:直接归位  1:渐渐归位
uint8_t Street_Check(void);
void Target_WidthSet(uint16_t*Width);
void Cash(void);
void Put(void);

#endif

