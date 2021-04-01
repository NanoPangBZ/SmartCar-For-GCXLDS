#ifndef _ATTITUDE_APP_H_
#define _ATTITUDE_APP_H_

#include "system_core.h"

static uint8_t attitude_flag = 0;
static uint8_t attitude_state = 0;

static void(*attitudeRun)(void);

void attitude_app_Task(void);

void FindQrCode_AttitudeTask(void);
void GetYL_UpBlosTask(void);
void FindLine_NAttitudeTask(void);
void PutBC_AttitudeTask(void);

void PutBlob_Attituede(uint8_t Pos);
void FindQrCode_Attitude(void);
void GetBlob(uint8_t Pos);
void FindLine_Attitude(uint8_t Pos);
uint8_t Read_AttitudeFlag(void);
uint8_t Read_AttitudeState(void);
void FindUpBlob_Attitude(void);

#endif
