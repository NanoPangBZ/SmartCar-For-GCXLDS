#ifndef _OPENMV_SERVICE_H_
#define _OPENMV_SERVICE_H_

#include "system_core.h"

#define Read_Usart()  Read_Usart_Sbuffer(1)
#define Read_End()	Usart_Sbuffer_Clear(1)

typedef struct
{
	uint8_t OpenMV_State;
	uint8_t OpenMV_fps;
}OpenMV_Data;

static unsigned char OpenMV_Sbuffer[128];	//OpenMV信息接收缓存区 [0]为接收到的字节数

void openmv_service(void);

void openmv_Decode(void);
void openmv_Updata(void);

#endif
