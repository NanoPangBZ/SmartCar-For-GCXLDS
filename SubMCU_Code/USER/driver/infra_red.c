#include "infra_red.h"

uint8_t*InfraRed_Decode(void)
{
	static uint8_t Input[5];
	uint8_t temp;
	for(temp=0;temp<5;temp++)
	{
		if((*InfraRed_IDR[temp] & InfraRed_Pin[temp]) != 0)
			Input[temp] = 1;
		else
			Input[temp] = 0;
	}
	return Input;
}

void InfraRedGPIO_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	
	GPIO_InitStruct.GPIO_Pin = L5;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = L1 | L2 | L3 | L4;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

