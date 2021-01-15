#ifndef _IIC_H_
#define _IIC_H_

#include "system_core.h"

#define IIC_SDA		N4
#define IIC_SCL		N3

#define N4	GPIO_Pin_14
#define N3	GPIO_Pin_13
#define N_Port	GPIOA

#define SDA_SET()  		N_Port->BSRR=IIC_SDA
#define SDA_RESET()  	N_Port->BRR=IIC_SDA
#define SCL_SET() 		N_Port->BSRR=IIC_SCL
#define SCL_RESET() 	N_Port->BRR=IIC_SCL

void IIC_Init(void);
void IIC_SendByte(uint8_t dat);

void IIC_Start(void);
void IIC_Stop(void);
void IIC_WaitAck(void);

#endif

