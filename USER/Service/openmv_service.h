#ifndef _OPENMV_SERVICE_H_
#define _OPENMV_SERVICE_H_

#include "system_core.h"

static uint8_t OpenMV_State = 0;
static uint8_t OpenMV_Tstate = 1;
static uint8_t QrCode[7] = {0,0,0,0,0,0,0};
static uint8_t LookData[3] = {0,0,0};
static uint8_t RecordingNum = 0;		//截取到的物块个数
static uint8_t Recording[3] = {0,0,0};	//原料区物块摆放顺序
	
void openmv_service(void);

void OpenMV_Set(uint8_t State);
void OpenMV_Init(void);
void OpenMV_Updata(void);
uint8_t*Read_Recording(void);
uint8_t*Read_LookData(void);
uint8_t*Read_QrCode(void);

#endif
