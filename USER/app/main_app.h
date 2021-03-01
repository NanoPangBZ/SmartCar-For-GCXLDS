#ifndef _MAIN_APP_H_
#define _MAIN_APP_H_

#include "system_core.h"

static uint8_t RunState = 0;		//0:等待
static long int TargetPosition[2];

void main_app_Task(void);
void WaitStart(void);

#endif

