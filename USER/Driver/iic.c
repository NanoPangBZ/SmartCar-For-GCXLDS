#include "iic.h"

void IIC_Init(void)
{
	GPIO_InitTypeDef		GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = IIC_SCL | IIC_SCL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	SDA_SET();
	SCL_SET();
}

void IIC_SendByte(uint8_t dat)
{
	uint8_t temp;
	for(temp=0;temp<8;temp++)
	{
		if( (dat&0x80) != 0)
			SDA_SET();
		else
			SDA_RESET();
		SCL_SET();
		SCL_RESET();
		dat<<=1;
	}
}

void IIC_WaitAck(void)
{
	SCL_SET();
	SCL_RESET();
}

void IIC_Stop(void)
{
	SDA_SET();
	SCL_SET();
}

void IIC_Start(void)
{
	SDA_SET();
	SCL_SET();
	
	SDA_RESET();
	SCL_RESET();
}

