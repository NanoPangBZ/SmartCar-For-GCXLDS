#ifndef	_MOTOR_DRIVER_H_
#define	_MOTOR_DRIVER_H_

#include "system_core.h"

//电机抽象定义
#define  MA	1
#define  MB	2
#define  MC	3
#define  MD	4
//电机方向控制引脚
#define MAD1	GPIO_Pin_9
#define MAD2	GPIO_Pin_8
#define MBD1	GPIO_Pin_10
#define MBD2	GPIO_Pin_11
#define MCD1	GPIO_Pin_13
#define MCD2	GPIO_Pin_12
#define MDD1	GPIO_Pin_15
#define MDD2	GPIO_Pin_14
//霍尔引脚
#define HallA1_Pin	GPIO_Pin_5
#define HallB1_Pin	GPIO_Pin_4
#define HallC1_Pin	GPIO_Pin_0
#define HallD1_Pin	GPIO_Pin_2
#define HallA2_Pin	GPIO_Pin_7
#define HallB2_Pin	GPIO_Pin_6
#define HallC2_Pin	GPIO_Pin_1
#define HallD2_Pin	GPIO_Pin_3

static uint16_t over_time = 0;					//溢出时间
static uint16_t last_time[4] = { 0 ,0 ,0 ,0};			//上上次上升沿时间
static uint16_t that_time[4] = { 0 ,0 ,0 ,0};			//上一次上升沿时间
static uint16_t last_over_time[4] = { 0 ,0 ,0 ,0};		//上上次上升沿溢出时间
static uint16_t that_over_time[4] = { 0 ,0 ,0 ,0};		//上一次上升沿溢出时间
static uint8_t last_dir[4] = {0,0,0,0};				//上上次上升沿霍尔方向
static uint16_t that_dir[4] = {0,0,0,0};				//上一次上升沿霍尔方向
static long int distance[4];						//霍尔计数

void PWM_Out(int*PWM);		//占空比输出  PWM -7200~7200

int* Read_Speed(void);		//读取速度
long int*Read_Distance(void);	//读取霍尔计数
void Disitance_clear(void);		//霍尔计数清0


#endif
