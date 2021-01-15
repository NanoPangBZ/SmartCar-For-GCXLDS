#ifndef _USART_H_
#define _USART_H_

#include "system_beat.h"

#define BaudRate		115200

#define Usart_Port 		GPIOA
#define Usart_Tx_Pin		GPIO_Pin_9 | GPIO_Pin_2
#define Usart_Rx_Pin		GPIO_Pin_10 | GPIO_Pin_3

//DMA发送缓存
static uint8_t	Usart1_Tx_Sbuffer[48];
static uint8_t	Usart2_Tx_Sbuffer[48];
//DMA在忙标志
static uint8_t DMA_Flag[2] = {0,0};
//Usart接收缓存
static uint8_t Usart_Rx_Sbuffer[2][64];

void Usart_Config(void);
void UsartGPIO_Config(void);
void Usart_DMA_Config(void);
uint8_t Usart1_Send(uint8_t*dat,uint8_t len);
uint8_t Usart2_Send(uint8_t*dat,uint8_t len);
uint8_t*Read_Usart(uint8_t USARTx);
uint8_t Usart_Rx_Sbuffer_Push(uint8_t USARTx,uint8_t len);
void Usart_Rx_Sbuffer_Clear(uint8_t USARTx);

#endif
