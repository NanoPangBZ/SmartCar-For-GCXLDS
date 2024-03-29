#ifndef _ANGLE_LIST_H_
#define _ANGLE_LIST_H_

#include "stm32f10x.h"

double Attitude_Angle[6][4] = {{0.0,-45.0,-90.0,-90.0},{-90.0,70.0,-90.0,82.0},{-90.0,-70.0,-90.0,-70.0},{0.0,70.0,-90.0,70.0},{0.0,-45.0,-90.0,90.0},{0.0,-40.0,-90.0,-90.0}};
uint8_t Attitude_Inc[6][4] = {{2,2,2,3},{3,4,4,6},{4,7,7,7},{2,2,2,3},{2,2,2,3},{2,2,2,3}};
	
double GetBlob_Ready[3][4] = {{-90.0,-25.0,-90.0,15.0},{0.0,70.0,-90.0,90.0}};
uint8_t GetBlob_ReadyInc[3][4] = {{2,9,6,6},{2,2,2,3}};

double GetBlob_Adjust[3][4] = {{-90.0,18.0,-90.0,28.0},{0.0,90.0,-70.0,70.0}};
uint8_t GetBlob_AdjustInc[3][4] = {{2,7,6,6},{2,2,2,3}};

double PutBlob_Ready[3][4] = {{0.0,0.0,-70.0,-50.0},{0.0,60.0,-90.0,72.0},{0.0,60.0,-90.0,72.0}};
uint8_t PutBlob_Readytnc[3][4] = {{7,4,4,4},{2,2,2,3}};
	
double PutBlob_Adjust[3][4] = {{0.0,80.0,-80.0,75.0},{0.0,60.0,-90.0,72.0},{0.0,60.0,-90.0,72.0}};
uint8_t PutBlob_Adjustnc[3][4] = {{7,4,4,8},{2,2,2,3}};

double PutBlob_GoBack[3][4] = {{0.0,60.0,-90.0,72.0}};
uint8_t PutBlob_GoBackInc[3][4] = {7,4,4,4};

#endif
