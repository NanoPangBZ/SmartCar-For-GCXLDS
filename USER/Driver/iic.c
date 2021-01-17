#include "iic.h"

void IIC_Init(void)
{
	GPIO_InitTypeDef		GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = IIC_SCL | IIC_SDA;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	IIC_SCL_SET();
	IIC_SDA_SET();
}

void IIC_SendByte(uint8_t dat)
{
	uint8_t temp;
	for(temp=0;temp<8;temp++)
	{
		if(dat&0x80)
			IIC_SDA_SET();
		else
			IIC_SDA_RESET();
		IIC_SCL_SET();
		IIC_SCL_RESET();
		dat<<=1;
	}
}

void IIC_Start(void)
{          
	IIC_SDA_SET();
	IIC_SCL_SET();
	IIC_SDA_RESET();
	IIC_SCL_RESET();
}

void IIC_Stop(void)
{
	IIC_SDA_SET();
	IIC_SCL_RESET();
	IIC_SCL_SET();
}

void IIC_WaitACK(void)
{
	IIC_SCL_SET();
	IIC_SCL_RESET();
}
