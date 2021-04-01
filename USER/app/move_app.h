#ifndef _MOVE_APP_H_
#define _MOVE_APP_H_

#include "system_core.h"

static uint8_t move_flag = 0;
static uint8_t move_state  =0;

static uint8_t Blob = 0;	//目标物块

static void(*MoveRun)(void);

void move_app_Task(void);

void FindQrCode_MoveTask(void);
void FindBlob_MoveTask(void);
void PutYL_MoveTask(void);
void BCToYL_MoveTask(void);

uint8_t Read_MoveFlag(void);
uint8_t Read_MoveState(void);
void FindQrCode_Move(void);
void FindBlob_Move(void);
void PutYL_Move(void);
void BCToYL_Move(void);

#endif

