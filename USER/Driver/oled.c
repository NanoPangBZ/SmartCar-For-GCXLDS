#include "oled.h"

void OLED_Init(void)
{
        OLED_SendNumByte(OLED_InitCmd,28,1);
}

void OLED_SendNumByte(uint8_t*dat,uint8_t len,uint8_t Mode)
{
        IIC_Start();
        IIC_SendByte(0x78);	//OLED设备地址
	IIC_WaitAck();
	if(Mode)
		IIC_SendByte(0x00);
	else
		IIC_SendByte(0x40);
	IIC_WaitAck();
	while(len!=0)
	{
		IIC_SendByte(*dat);
		dat++;
		len--;
	}
	IIC_WaitAck();
	IIC_Stop();
}

