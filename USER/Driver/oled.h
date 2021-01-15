#ifndef _OLED_H_
#define _OLED_H_

#include "system_core.h"

static uint8_t OLED_InitCmd[28] = {0xAE , 0x00 , 0x10 , 0x40 ,
                                                             0x81 , 0xCF , 0xA1 , 0xC8,
                                                             0xA6 , 0xA8 , 0x3F , 0xD3,
                                                              0x00 , 0xD5 , 0x80 , 0xD9,
                                                              0xF1 , 0xDA , 0x12 , 0xDB,
                                                               0x40 , 0x20 , 0x02 , 0x8D,
                                                               0x14 , 0xA4 , 0xA6 , 0xAF};

void OLED_Init(void);
void OLED_Clear(void);	//屏幕清除

void OLED_SendNumByte(uint8_t*dat,uint8_t len,uint8_t Mode);		//Mode=1 命令  0 数据

#endif


