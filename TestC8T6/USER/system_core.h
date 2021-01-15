#ifndef _SYSTEM_CORE_H_
#define _SYSTEM_CORE_H_

#include "stm32f10x.h"
#include <stdio.h>
#include "oled.h"
#include "iic.h"
#include "usart.h"

static uint32_t System_Time = 0;

void PCB_System_Init(void);

#endif

