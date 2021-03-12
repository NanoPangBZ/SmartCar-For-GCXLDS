#ifndef _MAIN_APP_H_
#define _MAIN_APP_H_

#include "system_core.h"

/*****************************************
主控应用
******************************************/

static uint8_t main_flag = 0;			//0:完成 1:运行
static uint8_t stateCmd_flag = 0;	//当前步骤的命令是否传达给了服务函数
static uint8_t main_state = 0;
static uint8_t Ctr_Blob = 0;
static uint8_t BlobsList[3] = {0,0,0};	//原料区物块

void main_app_Task(void);
void GetQrCode(void);
void Blobs_Recording(void);		//获取原料排放顺序
void Get_UpBlobs(void);

#endif

