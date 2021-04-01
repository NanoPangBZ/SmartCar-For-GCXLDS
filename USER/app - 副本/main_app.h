#ifndef _MAIN_APP_H_
#define _MAIN_APP_H_

#include "system_core.h"

/*****************************************
主控应用
******************************************/

static uint8_t main_app_flag = 0;
static uint8_t main_app_state = 0;

void main_app_Task(void);

void Find_QrCode(void);
void Find_Blobs(void);
void Get_YLBlobs(void);
void Put_BCBlobs(void);

#endif

