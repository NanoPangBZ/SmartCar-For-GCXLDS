#ifndef _MechanicalArm_Service_H_
#define _MechanicalArm_Service_H_

#include "system_core.h"

#define	Pi	acos(-1)					//圆周率

//机械臂的CCR寄存器地址
static uint16_t* street_width[6] = {(uint16_t*)&TIM3->CCR1 , (uint16_t*)&TIM3->CCR2,
							(uint16_t*)&TIM3->CCR3 , (uint16_t*)&TIM3->CCR4,
							(uint16_t*)&TIM2->CCR1 , (uint16_t*)&TIM2->CCR2 };
							
static uint8_t ArmLen[3] = {150,90,90};						//机械臂长度
static uint16_t ArmLen2[3] = {22500,8100,8100};				//长度平方,方便余弦定理的计算

static uint16_t Reset_Value[5] ={2535,925,400,2490,500};		//复位脉宽
static uint16_t Width_Target[5] = {2535,925,400,2490,300};		//目标脉宽
static uint8_t WidthInc[5] = {3,3,3,3,6};						//5ms脉宽增量
static uint8_t MechanicalArm_State = 1;						//0:完成  1:稳定Inc运行  2:精确轨迹运行

void MechanicalArm_Service(void);							//机械臂控制服务
void MechanicalArm_Reset(uint8_t mode);					//机械臂复位
uint8_t Read_MechanicalArmState(void);						//机械臂状态获取
void MechanicalArm_WidthSet(uint16_t*Width,uint8_t*Inc);		//设置目标脉宽
void Cash(void);										
void Put(void);

#endif

