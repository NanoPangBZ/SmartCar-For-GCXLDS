#ifndef _SYSTEM_BEAT_H_
#define _SYSTEM_BEAT_H_

#include "stm32f10x.h"
#include "usart.h"
#include "infra_red.h"
#include "clr_port.h"
#include "led.h"
#include <stdio.h>

static uint32_t System_Time = 0;
static uint32_t LastRespond_Time = 0;
static uint8_t System_State = 0;
static int SendFlag = 0;

void BSP_Driver_Init(void);
void InputSend(void);
void SystemLED(void);

#endif

