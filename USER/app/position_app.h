#ifndef _POSITION_APP_H_
#define _POSITION_APP_H_

#include "system_core.h"

static uint8_t PositionTask_En = 0;	//0:完成 1:运行

static uint8_t PositionTask_State = 0;

void position_app_Task(void);
void FindQrcode_Move(void);
void FindBlobs_Move(void);
void GetBlob_Move(void);

uint8_t Read_PositionTaskEn(void);
void PositionTask_StateSet(uint8_t state);

#endif
