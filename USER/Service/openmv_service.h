#ifndef _OPENMV_SERVICE_H_
#define _OPENMV_SERVICE_H_

#include "system_core.h"

#define RED 	0
#define GREEN	1
#define BLUE	2
#define ALL		3

static uint8_t openmv_state = 0;
static uint8_t openmv_fps = 0;
static unsigned char OpenMV_Sbuffer[128];	//OpenMV信息接收缓存区

void openmv_service(void);
uint8_t Read_FindData(void);
int Read_BlobPosition(uint8_t TargetBlobs);
char* Read_RQcode(void);

void openmv_decode(void);

#endif
