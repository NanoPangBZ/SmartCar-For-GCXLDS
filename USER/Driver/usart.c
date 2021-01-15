#include "usart.h"

void Usart_Config(void)
{
	USART_InitTypeDef   Usart_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	Usart_InitStruct.USART_BaudRate = BaudRate;
	Usart_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	Usart_InitStruct.USART_Parity = USART_Parity_No ;
	Usart_InitStruct.USART_StopBits = USART_StopBits_1;
	Usart_InitStruct.USART_WordLength = USART_WordLength_8b;
	Usart_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1,&Usart_InitStruct);
	USART_Init(USART2,&Usart_InitStruct);
	
	NVIC_InitTypeDef		NVIC_InitStruct;

	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;

	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_Init(&NVIC_InitStruct);
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_Init(&NVIC_InitStruct);

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

	USART_Cmd(USART1,ENABLE);
	USART_Cmd(USART2,ENABLE);
}

void UsartGPIO_Config(void)
{
	GPIO_InitTypeDef	GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = Usart_Tx_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Usart_Port,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = Usart_Rx_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(Usart_Port,&GPIO_InitStruct);
}

void Usart_DMA_Config(void)
{
	DMA_InitTypeDef		DMA_InitStruct;
	NVIC_InitTypeDef		NVIC_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//DMA串口通用配置
	DMA_InitStruct.DMA_BufferSize = 0;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	//USART1_DMA 通道以及中断配置
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)Usart1_Tx_Sbuffer;
	DMA_DeInit(DMA1_Channel4);
	DMA_ClearFlag(DMA1_FLAG_GL4);
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
	DMA_Init(DMA1_Channel4,&DMA_InitStruct);
	//USART2_DMA 通道以及中断配置
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(USART2->DR);
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)Usart2_Tx_Sbuffer;
	DMA_DeInit(DMA1_Channel7);
	DMA_ClearFlag(DMA1_FLAG_GL7);
	DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,ENABLE);
	DMA_Init(DMA1_Channel7,&DMA_InitStruct);
	//DMA中断优先级
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	//DMA中断优先级
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_Init(&NVIC_InitStruct);
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel7_IRQn;
	NVIC_Init(&NVIC_InitStruct);
	//串口MDA使能
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
}

uint8_t*Read_Usart(uint8_t USARTx)
{
	if(USARTx < 2)
		return Usart_Rx_Sbuffer[USARTx-1];
	return NULL;
}

uint8_t Usart1_Send(uint8_t*dat,uint8_t len)
{
	uint8_t temp;
	if(DMA_Flag[0] != 1)
	{
		for(temp=0;temp<len;temp++)
			Usart1_Tx_Sbuffer[temp] = *(dat+temp);
		DMA_SetCurrDataCounter(DMA1_Channel4,len);
		DMA_Cmd(DMA1_Channel4,ENABLE);
		DMA_Flag[0] = 1;
		return 0;
	}
	return 1;
}

uint8_t Usart2_Send(uint8_t*dat,uint8_t len)
{
	uint8_t temp;
	if(DMA_Flag[1] != 1)
	{
		for(temp=0;temp<len;temp++)
			Usart2_Tx_Sbuffer[temp] = *(dat+temp);
		DMA_SetCurrDataCounter(DMA1_Channel7,len);
		DMA_Cmd(DMA1_Channel7,ENABLE);
		DMA_Flag[1] = 1;
		return 0;
	}
	return 1;
}

uint8_t Usart_Rx_Sbuffer_Push(uint8_t USARTx,uint8_t len)
{
	uint8_t temp;
	if(len <= Usart_Rx_Sbuffer[USARTx-1][0] )
	{
		for(temp=0;temp<len;temp++)
			if(temp+1+len<63)
				Usart_Rx_Sbuffer[USARTx-1][temp+1] = Usart_Rx_Sbuffer[USARTx-1][temp + 1 + len];
		Usart_Rx_Sbuffer[USARTx-1][0] -= len;
		return 0;
	}
	return 1;
}

void Usart_Rx_Sbuffer_Clear(uint8_t USARTx)
{
	Usart_Rx_Sbuffer[USARTx][0] = 0;
}

int fputc (int c, FILE *fp)
{
	USART_SendData(USART1,c);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	return c;
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		Usart_Rx_Sbuffer[0][0]++;
		if(Usart_Rx_Sbuffer[0][0]<63)
			Usart_Rx_Sbuffer[0][Usart_Rx_Sbuffer[0][0]] = USART_ReceiveData(USART1);
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{
		Usart_Rx_Sbuffer[1][0]++;
		if(Usart_Rx_Sbuffer[1][0]<63)
			Usart_Rx_Sbuffer[1][Usart_Rx_Sbuffer[1][0]] = USART_ReceiveData(USART2);
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}

void DMA1_Channel4_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC4) == SET)
	{
		DMA_Cmd(DMA1_Channel4,DISABLE);
		DMA_ClearITPendingBit(DMA1_IT_TC4);
		DMA_Flag[0] = 0;
	}
}

void DMA1_Channel7_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC7) == SET)
	{
		DMA_Cmd(DMA1_Channel7,DISABLE);
		DMA_ClearITPendingBit(DMA1_IT_TC7);
		DMA_Flag[1] = 0;
	}
}
