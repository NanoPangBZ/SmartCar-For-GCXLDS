#ifndef _MechanicalArm_Service_H_
#define _MechanicalArm_Service_H_

#include "system_core.h"

//机械臂的CCR寄存器地址
static uint16_t* street_width[6] = {(uint16_t*)&TIM3->CCR1 , (uint16_t*)&TIM3->CCR2,
							(uint16_t*)&TIM3->CCR3 , (uint16_t*)&TIM3->CCR4,
							(uint16_t*)&TIM2->CCR1 , (uint16_t*)&TIM2->CCR2 };
							
static uint8_t ArmLen[3] = {150,90,90};						//机械臂长度
static uint16_t ArmLen2[3] = {22500,8100,8100};				//长度平方,方便余弦定理的计算

static uint16_t Reset_Width[5] ={2535,925,400,2490,500};		//复位脉宽
static uint16_t Target_Width[5] = {2535,925,400,2490,500};		

void MechanicalArm_Service(void);							//机械臂控制服务
void MechanicalArm_Reset(uint8_t mode);					//机械臂复位
uint8_t Read_MechanicalArmState(void);						//机械臂状态获取

void MechanicalArm_WidthToAngle(void);					//角度转脉宽
void MechanicalArm_AngleSet(int*angle);					//角度设置
void MechanicalArm_WidthSet(uint16_t*Width);				//设置脉宽

#endif

