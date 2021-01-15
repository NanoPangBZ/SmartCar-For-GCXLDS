#ifndef _INFRA_RED_H_
#define _INFRA_RED_H_

#include "system_beat.h"

//GPIOB
#define L1		GPIO_Pin_11
#define L2		GPIO_Pin_10
#define L3		GPIO_Pin_1
#define L4		GPIO_Pin_0
//GPIOA
#define L5		GPIO_Pin_7

static uint16_t*InfraRed_IDR[5] = {(uint16_t*)&GPIOB->IDR,
						   (uint16_t*)&GPIOB->IDR,
						   (uint16_t*)&GPIOB->IDR,
						   (uint16_t*)&GPIOB->IDR,
						   (uint16_t*)&GPIOA->IDR};
static uint16_t InfraRed_Pin[5] = {L1,L2,L3,L4,L5};

void InfraRedGPIO_Init(void);
uint8_t*InfraRed_Decode(void);

#endif
