#ifndef	_USART_H_
#define	_USART_H_

#include "system_core.h"
#include <stdio.h>

#define	USART_BOUND		115200

static uint8_t Usart_Tx_Flag[3] = { 0, 0, 0};			//DMA在忙标志
static uint8_t Usart_Sbuffer[3][64] = {{0},{0},{0}};		//Usart接收缓存  每行第一位表示已经接收到的数据

/*****************对外接口**********************/
uint8_t Usart1_Send(uint8_t*data,uint8_t len);				//通过DMA使USARTx向外发送数据
uint8_t Usart2_Send(uint8_t*data,uint8_t len);
uint8_t Usart3_Send(uint8_t*data,uint8_t len);
void Usart_TxFlag_Clear(uint8_t USARTx);				//DMA在忙标志位清除
void Usart_Sbuffer_Clear(uint8_t USARTx);				//Usart接收缓存清除
uint8_t* Read_Usart_Sbuffer(uint8_t USARTx);			//读取串口接收缓存
uint8_t Usart_Sbuffer_Push(uint8_t USARTx,uint8_t len);	//串口接收缓存数据段前移len个字节
/****************初始化*************************/
void Usart_Config(void);
void Usart_DMA_Config(void);
/****************中断****************************/
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);

#endif

