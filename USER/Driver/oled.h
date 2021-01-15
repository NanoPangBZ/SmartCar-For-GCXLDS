#ifndef _OLED_H_
#define _OLED_H_

#include "system_core.h"

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//OLED缓存
static uint8_t OLED_Sbuffer[128][8];		//[col][page]

void OLED_Init(void);
void OLED_Clear(void);
void OLED_Refresh(void);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
//只对OLED_Sbuffer进行修改
void OLED_DrawPoint(uint8_t x,uint8_t y);
void OLED_ClearPoint(uint8_t x,uint8_t y);

void OLED_SendByte(uint8_t dat,uint8_t Mode);	//Mode: OLED_CMD or OLED_DATA

#endif

