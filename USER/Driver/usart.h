#ifndef	_USART_H_
#define	_USART_H_

#include "system_core.h"

#define	USART_BOUND		115200

static uint8_t Usart_Tx_Flag[3] = { 0, 0, 0};			//DMA在忙标志位
static uint8_t Usart_Sbuffer[3][64] = {{0},{0},{0}};		//Usart接收缓存  每行第一位表示接收到的数据长度

/*****************外部接口***********************/
uint8_t Usart1_Send(uint8_t*data,uint8_t len);				//利用DMA向Usartx发送数据
uint8_t Usart2_Send(uint8_t*data,uint8_t len);
uint8_t Usart3_Send(uint8_t*data,uint8_t len);
void Usart_TxFlag_Clear(uint8_t USARTx);				//DMA在忙标志清除
void Usart_Sbuffer_Clear(uint8_t USARTx);				//串口接收缓冲区清除
uint8_t* Read_Usart_Sbuffer(uint8_t USARTx);			//读取串口接收缓冲区数据
uint8_t Usart_Sbuffer_Push(uint8_t USARTx,uint8_t len);	//串口缓冲区数据前移
/****************初始化**************************/
void Usart_Config(void);
void Usart_DMA_Config(void);
/****************中断****************************/
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);

#endif

