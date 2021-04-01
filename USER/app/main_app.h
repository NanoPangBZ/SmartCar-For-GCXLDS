#ifndef _MAIN_APP_H_
#define _MAIN_APP_H_

#include "system_core.h"

static uint8_t main_app_flag = 1;
static uint8_t main_state = 0;

static uint8_t state = 0;

void main_app_Task(void);

void PutYL_Blob(void);
void Find_QrCode(void);
void Find_Blob(void);

#endif

