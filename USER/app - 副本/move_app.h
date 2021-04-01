#ifndef _MOVE_APP_H_
#define _MOVE_APP_H_

#include "system_core.h"

static uint8_t Move_State = 0;	//0:完成 1:运行中
static uint8_t Move_Line = 0;	//1:FindQrCode 2:Find_Blob 3:GetYL 4:PutBC 5:YLToBC

static uint8_t Blob = 0;		//当前操作的物块

void move_app_Task(void);


void FindQrCode_Move(void);
void FindYL_Move(void);
void GetYL_Move(void);
void PutBC_Move(void);
void BCToYL(void);

uint8_t Read_MoveState(void);
void MoveCmd_Set(uint8_t Line);

#endif

