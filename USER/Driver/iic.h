#ifndef _IIC_H_
#define _IIC_H_

#include "system_core.h"

#define IIC_SDA	GPIO_Pin_7
#define IIC_SCL	GPIO_Pin_5

#define IIC_SDA_SET()		GPIO_SetBits(GPIOA,IIC_SDA)
#define IIC_SDA_RESET()		GPIO_ResetBits(GPIOA,IIC_SDA)
#define IIC_SCL_SET()		GPIO_SetBits(GPIOA,IIC_SCL)
#define IIC_SCL_RESET()		GPIO_ResetBits(GPIOA,IIC_SCL)

void IIC_Init(void);
void IIC_SendByte(uint8_t dat);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_WaitACK(void);

#endif
