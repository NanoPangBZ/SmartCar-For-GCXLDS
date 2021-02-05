#ifndef _POSITION_SERVICE_H_
#define _POSITION_SERVICE_H_

#include "system_core.h"

#define	SpeedKp	1.15
#define	SpeedTi 	0.82
#define	SpeedTd	0.015

#define	K_output	48			//PID输出放大倍数

#define X 0
#define Y 1

#define Speed_Base  320
#define Speed_Max    380
#define Speed_Min	50
#define Speed_Cha	1

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
static long int Target_Position[2] = {0,0};		//自动模式下目标
static long int Err_Position[2] = {0,0};			//距离目标位置
static uint8_t Position_State = 5;			//自动模式的控制进度 0:Yaw 1:x 2:Yaw 3:y 4:Yaw 5:空闲
static uint8_t Position_Mode = 0;			//控制模式  0:位移模式  1:自动控制模式   3:万向模式(不支持自动控制)

static int Target_Speed[4] = {0,0,0,0};		//合成速度
static int Position_Speed[4] = {0,0,0,0};		//位移速度
static int Yaw_Speed[4] = {0,0,0,0};			//航向角修正速度

/*********************外部控制接口*****************************/
long int*Read_Position(void);									//坐标读取
uint8_t Read_PositionState(void);								//获取运动控制状态
void PositionClr_Service(void);									//实现接口
void TargetMove_Set(long int x,long int y,uint8_t PosMode);			//自动目标模式设定
void Move_Set(uint8_t Dir,int Speed);							//位移模式
void VectorMove_Set(int XSpeed,int YSpeed);					//矢量位移
void YawPoint_Reset(int ReYaw);								//基准方位重置								
void PositionService_Stop(void);				//结束当前任务
/***********************内部函数*****************************/
float Inc_PID(float Input , PID_TypeDef*  PID);		//增量式PID运算
void Inc_PID_Realiz(void);						//Inc_PID实现
void Speed_Set(int*PointSet);					//PID目标值设定
void Position_Update(void);					//坐标更新
void PositionState_Updata(void);				//自动模式下的进度更新
void PositionSpeed_Config(uint8_t Dir);			//移动速度配置
void YawSpeed_Config(void);					//通用航向角修正
void Position_Stop(void);						//电机锁死
void PositionState_Inc(void);					//进度递增
void Speed_Syn(void);						//速度合成

#endif



