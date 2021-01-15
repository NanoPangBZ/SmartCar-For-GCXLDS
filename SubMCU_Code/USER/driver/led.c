#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = LED_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	GPIO_SetBits(GPIOC,LED_Pin);
}

void LED_Clr(uint8_t S)
{
	if(S)
		GPIOC->BSRR = LED_Pin;
	else
		GPIOC->BRR = LED_Pin;
}

void LED_Re(void)
{
	if((GPIOC->ODR&LED_Pin) != 0)
		LED_Clr(0);
	else
		LED_Clr(1);
}

