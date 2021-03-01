#include "openmv_service.h"

void openmv_service(void)
{
	openmv_Updata();
	openmv_Decode();
}

void openmv_Decode(void)
{
	
}

void openmv_Updata(void)
{
	uint8_t*Cmd;
	uint8_t temp;
	Cmd = Read_Usart();
	if(*Cmd!=0)
	{
		for(temp=0;temp<*Cmd;temp++)
		{
			OpenMV_Sbuffer[OpenMV_Sbuffer[0]+1] = *(Cmd+temp+1);
			OpenMV_Sbuffer[0]++;
		}
		Read_End();
	}
}

