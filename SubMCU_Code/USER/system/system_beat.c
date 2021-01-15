#include "system_beat.h"

void BSP_Driver_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	UsartGPIO_Config();
	Usart_Config();
	Usart_DMA_Config();
	InfraRedGPIO_Init();
	LED_Init();
	SysTick_Config(2*72000);
}

void InputSend(void)
{
	uint8_t*temp;
	temp = InfraRed_Decode();
	Usart2_Send(temp,5);
	SendFlag = 1;
	LastRespond_Time = System_Time;
}

void SystemLED(void)
{
	static uint32_t time = 0;
	static uint8_t flag = 0;
	if(flag != 1)
	{
		if(time>200)
		{
			flag = 1;
			LED_Clr(0);
		}
	}
	time++;
	if(time>250)
	{
		time = 0;
		flag = 0;
		LED_Clr(1);
	}
}

//ÏµÍ³ÖÐ¶Ï
void SysTick_Handler(void)
{
	uint8_t*temp;
	System_Time++;
	if(System_Time%100 == 0)
	{
		temp = InfraRed_Decode();
		printf("%d %d %d %d %d\r\n",*temp,*(temp+1),*(temp+2),*(temp+3),*(temp+4) );
	}
	if(System_Time > 0xffffff)
		System_Time = LastRespond_Time = 0;
	if(System_Time - LastRespond_Time > 100)
		SystemLED();
	else
		LED_Clr(0);
}

