#ifndef _DEBUG_APP_H_
#define _DEBUG_APP_H_

#include "system_core.h"

static uint8_t ReturnState = 1;	//0:不返回   1:返回速度和位置

void debug_app_Task(void);
void ReturnPosition(void);
void ReturnSpeed(void);

#endif
