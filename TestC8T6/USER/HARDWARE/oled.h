#ifndef _OLED_H_
#define _OLED_H_

#include "system_core.h"

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_Init(void);
void OLED_Clear(void);
void OLED_PosSet(uint8_t page,uint8_t col);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);

void OLED_ShowChar(uint8_t chr,uint8_t page,uint8_t col,uint8_t size);

void OLED_SendByte(uint8_t dat,uint8_t Mode);	//Mode: OLED_CMD or OLED_DATA

#endif

