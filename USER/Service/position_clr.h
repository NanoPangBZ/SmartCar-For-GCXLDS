#ifndef _POSITION_CLR_H_
#define _POSITION_CLR_H_

#include "system_core.h"

#define	SpeedKp	1.15
#define	SpeedTi 	0.82
#define	SpeedTd	0.015

#define	K_output	48			//PID输出放大倍数

#define X 0
#define Y 1

typedef struct
{
	float pointSet;
	float Err;
	float Err1;
	float Err2;
}PID_TypeDef;

static PID_TypeDef	PID_Struct[4];			//速度PID结构体
static int PWM[4] = {0,0,0,0};					//当前占空比

static long int position[2] = {0 , 0};			//当前坐标
static int Err_Yaw = 0;						//当前航向角

/*********************外部控制接口*****************************/
long int*Read_Position(void);									//坐标读取
uint8_t Read_PositionState(void);								//获取运动控制状态
void PositionClr_Service(void);									//实现接口
void PositionCmd_Move(uint8_t Dir,int Speed,uint8_t YawEn);		//直接位移
void PositionCmd_TargetMove(long int x,long int y,uint8_t PMode);	//指定位置位移,
void PositionCmd_ClrCng(uint8_t num,uint16_t vale);				//控制参量配置
/***********************内部函数*****************************/
float Inc_PID(float Input , PID_TypeDef*  PID);		//增量式PID运算
void Speed_Set(int*PointSet);					//PID目标值设定
void Position_Update(void);					//真实坐标更新
void Speed_Config(void);						//合成速度
void Inc_PID_Realiz(void);						//Inc_PID实现

#endif



