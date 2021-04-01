#ifndef _GOODS_APP_H_
#define _GOODS_APP_H_

#include "system_core.h"

#define None		0
#define RED 	1
#define GREEN 	2
#define BLUE	3

static uint8_t Goods_State = 0;	//0:无任务 1:运行中
static uint8_t Goods_Line = 0;	//0:姿态调整 1:夹原料区上物块 2:夹原料区下物块 3:夹半成品 4:放半成品 5:放上成品 6:放下成品
static uint8_t Goods_Attitude = 0;	//0:默认 1:寻找二维码 2:寻找原料区上物块 3:寻找原料区下物块
								//4:寻找半成品区物块 5:正面线寻 6:左面线训 7:右面线训 8:其他

static uint8_t Target_Attitude = 0;	//0:默认
void goods_app_Task(void);

void Attitude_Adjust(void);
void Goods_Line1(void);
void Goods_Line2(void);
void Goods_Line3(void);
void Goods_Line4(void);
void Goods_Line5(void);
void Goods_Line6(void);

uint8_t Read_GoodsAppState(void);
void Attitude_Set(uint8_t attitude);
void Goods_Cmd(uint8_t Line);

#endif
