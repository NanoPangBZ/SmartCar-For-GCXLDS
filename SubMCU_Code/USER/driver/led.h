#ifndef _LED_H_
#define _LED_H_

#include "system_beat.h"

#define LED_Port		GPIOC
#define LED_Pin		GPIO_Pin_13

void LED_Init(void);
void LED_Clr(uint8_t S);
void LED_Re(void);

#endif

