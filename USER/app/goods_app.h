#ifndef _GOODS_APP_H_
#define _GOODS_APP_H_

#include "system_core.h"

#define None		0
#define RED 	1
#define GREEN 	2
#define BLUE	3

/**********************************************
货物管理应用
*********************************************/

static uint8_t Attitude_Flag = 0;	//0:完成 1:运行中 2等待
static uint8_t Attitude = 0;	//0:默认 1:寻找二维码 2:寻找上物块 3:寻找下物块 4:取货预备
static uint8_t Target_Blob = None;	//色块
static uint8_t Target_Pos = 0;
static uint8_t Target_Warehouse = 0;
static uint8_t Target_Attitude = 0;
static uint8_t Attitude_Line = 0;	//0:GetFloor 1:GetWarehouse 2:PutFloor 3:PutWarehouse 4:AttitudeSet
static uint8_t Attitude_State = 0;
static uint8_t Warehouse[3] = {None,None,None};

void goods_app_Task(void);
uint8_t Attitude_Set(uint8_t Attitude);
uint8_t GetBlob_Floor(uint8_t Pos,uint8_t Blob);
uint8_t GetBlob_Warehouse(uint8_t Blob);
uint8_t PutBlob_Floor(uint8_t Pos);
uint8_t PutBlob_Warehouse(void);
uint8_t Read_AttitudeFlag(void);

void PutBlob_FloorRun(void);
void Attitude_SetRun(void);
void GetBlob_FloorRun(void);

#endif
