#include "usart.h"

static uint8_t	Usart1_Tx_Sbuffer[48];
static uint8_t	Usart2_Tx_Sbuffer[48];
static uint8_t	Usart3_Tx_Sbuffer[48];

void Usart_Config(void)
{
	USART_InitTypeDef		USART_InitStruct;
	GPIO_InitTypeDef			GPIO_InitStruct;
	NVIC_InitTypeDef			NVIC_InitStruct;
	
	//GPIO ±÷”
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//Tx≥ı ºªØ
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_2;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	//Rx≥ı ºªØ
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//¥Æø⁄≈‰÷√
	USART_InitStruct.USART_BaudRate = USART_BOUND;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx ;
	USART_InitStruct.USART_Parity = USART_Parity_No ;
	USART_InitStruct.USART_StopBits = USART_StopBits_1 ;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b ;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	USART_Init(USART1,&USART_InitStruct);
	USART_Init(USART2,&USART_InitStruct);
	USART_Init(USART3,&USART_InitStruct);
	
	//¥Æø⁄÷–∂œ≈‰÷√
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1 ;
	
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_Init(&NVIC_InitStruct);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART1,ENABLE);
	USART_Cmd(USART2,ENABLE);
	USART_Cmd(USART3,ENABLE);
}

void Usart_DMA_Config(void)
{
	DMA_InitTypeDef	DMA_InitStruct;
	NVIC_InitTypeDef	NVIC_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStruct.DMA_BufferSize = 0;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	//Usart1_DMA÷–∂œ≈‰÷√
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	//Usart2_DMA÷–∂œ≈‰÷√
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel7_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	//Usart3_DMA÷–∂œ≈‰÷√
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	//Usart1_Tx_DMA≈‰÷√
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)Usart1_Tx_Sbuffer;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_DeInit(DMA1_Channel4);
	DMA_ClearFlag(DMA1_FLAG_GL4);
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
	DMA_Init(DMA1_Channel4,&DMA_InitStruct);
	//Usart2_Tx_DMA≈‰÷√
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)Usart2_Tx_Sbuffer;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_DeInit(DMA1_Channel7);
	DMA_ClearFlag(DMA1_FLAG_GL7);
	DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,ENABLE);
	DMA_Init(DMA1_Channel7,&DMA_InitStruct);
	//Usart3_Tx_DMA≈‰÷√
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)Usart3_Tx_Sbuffer;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_DeInit(DMA1_Channel2);
	DMA_ClearFlag(DMA1_FLAG_GL2);
	DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE);
	DMA_Init(DMA1_Channel2,&DMA_InitStruct);
	//Usart_Tx_DMA«Î«Û πƒ‹
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
	USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
}

uint8_t Usart1_Send(uint8_t*data,uint8_t len)
{
	uint8_t	n;
	if(Usart_Tx_Flag[0] == 0)
	{
		Usart_Tx_Flag[0] = 1;
		for(n=0;n<len;n++)
		{
			Usart1_Tx_Sbuffer[n] = *data;
			data++;
		}
		DMA_SetCurrDataCounter(DMA1_Channel4,len);
		DMA_Cmd(DMA1_Channel4,ENABLE);
		return 0;
	}
	return 1;
}

uint8_t Usart2_Send(uint8_t*data,uint8_t len)
{
	uint8_t	n;
	if(Usart_Tx_Flag[1] == 0)
	{
		Usart_Tx_Flag[1] = 1;
		for(n=0;n<len;n++)
		{
			Usart2_Tx_Sbuffer[n] = *data;
			data++;
		}
		DMA_SetCurrDataCounter(DMA1_Channel7,len);
		DMA_Cmd(DMA1_Channel7,ENABLE);
		return 0;
	}
	return 1;
}

uint8_t Usart3_Send(uint8_t*data,uint8_t len)
{
	uint8_t	n;
	if(Usart_Tx_Flag[2] == 0)
	{
		Usart_Tx_Flag[2] = 1;
		for(n=0;n<len;n++)
		{
			Usart3_Tx_Sbuffer[n] = *data;
			data++;
		}
		DMA_SetCurrDataCounter(DMA1_Channel2,len);
		DMA_Cmd(DMA1_Channel2,ENABLE);
		return 0;
	}
	return 1;
}

uint8_t Usart_Sbuffer_Push(uint8_t USARTx,uint8_t len)
{
	uint8_t temp;
	if(len <= Usart_Sbuffer[USARTx-1][0] )
	{
		for(temp=0;temp<len;temp++)
			if(temp+1+len<63)
				Usart_Sbuffer[USARTx-1][temp+1] = Usart_Sbuffer[USARTx-1][temp + 1 + len];
		Usart_Sbuffer[USARTx-1][0] -= len;
		return 0;
	}
	return 1;
}

uint8_t* Read_Usart_Sbuffer(uint8_t USARTx)
{
	return Usart_Sbuffer[USARTx - 1];
}

void Usart_Sbuffer_Clear(uint8_t USARTx)
{
	Usart_Sbuffer[USARTx-1][0] = 0;
}

void Usart_TxFlag_Clear(uint8_t USARTx)
{
	Usart_Tx_Flag[USARTx-1] = 0;
}

void USART1_IRQHandler(void)
{
	uint8_t temp;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		temp = Usart_Sbuffer[0][0]++;
		if(temp != 63)
			Usart_Sbuffer[0][temp + 1]  = USART_ReceiveData(USART1);
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}

void USART2_IRQHandler(void)
{
	uint8_t temp;
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{
		temp = Usart_Sbuffer[1][0]++;
		if(temp != 63)
			Usart_Sbuffer[1][temp + 1]  = USART_ReceiveData(USART2);
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}

void USART3_IRQHandler(void)
{
	uint8_t temp;
	if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)
	{
		temp = Usart_Sbuffer[2][0]++;
		Usart_Sbuffer[2][temp +1] = USART_ReceiveData(USART3);
		if(Usart_Sbuffer[2][0] == 11)
		{
			Usart_Sbuffer[2][0] = 0;
			Gyroscope_YawUpdata(&Usart_Sbuffer[2][1]);
		}
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	}
}

void DMA1_Channel4_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC4) != RESET)
	{
		DMA_ClearFlag(DMA1_FLAG_TC4);
		DMA_Cmd(DMA1_Channel4,DISABLE);
		Usart_TxFlag_Clear(1);
	}
}

void DMA1_Channel7_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC7) != RESET)
	{
		DMA_ClearFlag(DMA1_FLAG_TC7);
		DMA_Cmd(DMA1_Channel7,DISABLE);
		Usart_TxFlag_Clear(2);
	}
}

void DMA1_Channel2_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC2) != RESET)
	{
		DMA_ClearFlag(DMA1_FLAG_TC2);
		DMA_Cmd(DMA1_Channel2,DISABLE);
		Usart_TxFlag_Clear(3);
	}
}

int fputc (int c, FILE *fp)
{
	USART_SendData(USART1,c);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	return c;
}
