#include "oled.h"

void OLED_Init(void)
{
	OLED_SendByte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_SendByte(0x00,OLED_CMD);//---set low column address
	OLED_SendByte(0x10,OLED_CMD);//---set high column address
	OLED_SendByte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_SendByte(0x81,OLED_CMD);//--set contrast control register
	OLED_SendByte(0xCF,OLED_CMD);// Set SEG Output Current Brightness
	OLED_SendByte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0×óÓÒ·´ÖÃ 0xa1Õý³£
	OLED_SendByte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0ÉÏÏÂ·´ÖÃ 0xc8Õý³£
	OLED_SendByte(0xA6,OLED_CMD);//--set normal display
	OLED_SendByte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_SendByte(0x3f,OLED_CMD);//--1/64 duty
	OLED_SendByte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_SendByte(0x00,OLED_CMD);//-not offset
	OLED_SendByte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_SendByte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_SendByte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_SendByte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_SendByte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_SendByte(0x12,OLED_CMD);
	OLED_SendByte(0xDB,OLED_CMD);//--set vcomh
	OLED_SendByte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_SendByte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_SendByte(0x02,OLED_CMD);//
	OLED_SendByte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_SendByte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_SendByte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_SendByte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_SendByte(0xAF,OLED_CMD);
	OLED_Clear();
}

void OLED_Refresh(void)
{
	uint8_t page,col;
	for(page=0;page<8;page++)
	{
		OLED_SendByte(0xb0+page,OLED_CMD);		//page设置
		OLED_SendByte(0x00,OLED_CMD);			//列地址低四位设置
		OLED_SendByte(0x10,OLED_CMD);			//列地址高四位设置
		for(col=0;col<128;col++)
			OLED_SendByte(0x00,OLED_DATA);
	}
}

void OLED_Clear(void)
{
	uint8_t page , col;
	for(page=0;page<8;page++)
		for(col=0;col<128;col++)
			OLED_Sbuffer[col][page] = 0x00;
	OLED_Refresh();
}

void OLED_DrawPoint(uint8_t x,uint8_t y)
{
	uint8_t page ,line;
	page = y / 8;
	line = y % 8;
	OLED_Sbuffer[x][page] |= (0x01<<line);
}

void OLED_ClearPoint(uint8_t x,uint8_t y)
{
	uint8_t page ,line;
	page = y / 8;
	line = y % 8;
	OLED_Sbuffer[x][page] = ~OLED_Sbuffer[x][page];
	OLED_Sbuffer[x][page] |= (0x01<<line);
	OLED_Sbuffer[x][page] = ~OLED_Sbuffer[x][page];
}

void OLED_DisPlay_On(void)
{
	OLED_SendByte(0x8D,OLED_CMD);
	OLED_SendByte(0x14,OLED_CMD);
	OLED_SendByte(0xAF,OLED_CMD);
}

void OLED_DisPlay_Off(void)
{
	OLED_SendByte(0x8D,OLED_CMD);
	OLED_SendByte(0x10,OLED_CMD);
	OLED_SendByte(0xAF,OLED_CMD);
}

void OLED_SendByte(uint8_t dat,uint8_t Mode)
{
	IIC_Start();
	IIC_SendByte(0x78);
	IIC_WaitACK();
	if(Mode)
		IIC_SendByte(0x40);
	else
		IIC_SendByte(0x00);
	IIC_WaitACK();
	IIC_SendByte(dat);
	IIC_WaitACK();
	IIC_Stop();
}
