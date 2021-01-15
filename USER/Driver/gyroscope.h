#ifndef _GYROSCOPE_H_
#define _GYROSCOPE_H_

#include "system_core.h"

static uint8_t Init_Code[4] = {0xA5,0x55,0x10,0x0A};
static uint8_t Visit_Code[4] = {0xA5,0x56,0x01,0xFC};
static uint8_t Reset_Code[4] = {0xA5,0x57,0x02,0xFE};
static int Yaw = 0;
static int Yaw_Err = 0;

void Gyroscope_Init(void);								//陀螺仪初始化
uint8_t Gyroscope_Reset(void);						//陀螺仪磁场校准
uint8_t Gyroscope_RequestUpdata(void);		//陀螺仪航向角更新请求发送
int Gyroscope_ReadYaw(void);						//读取航向角
int Gyroscope_YawUpdata(uint8_t*dat);			//航向角数据接收并更新
void Wait_Gyroscope(void);							//等待陀螺仪稳定

#endif //_GYROSCOPE_H_

