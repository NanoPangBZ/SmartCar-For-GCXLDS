#include "feedback_service.h"

void feedback_service(void)
{
	OLED_FB_Task();
}

void OLED_FB_Task(void)
{
	static uint8_t ShowStrFlag = 0;
	uint32_t Time;
	if(ShowStrFlag!=1)
	{
		OLED_ShowString("SysTime:",0,0,1);
		ShowStrFlag = 1;
	}
	Time = Read_SysTime();
	OLED_ShowNum((uint16_t)(Time/200),0,57,1);
}

