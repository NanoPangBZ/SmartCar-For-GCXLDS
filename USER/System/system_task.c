#include "system_task.h"

void Debug(void)
{
	uint8_t*Cmd;
	static uint8_t flag = 0;
	static uint8_t Mx = 0;
	static uint8_t temp;
	Cmd = Read_Usart_Sbuffer(1);
	if(*Cmd > 0)
	{
		if(*(Cmd+1) == 0xfa)
		{
			printf("********\r\n");
			for(temp = 0;temp < 6;temp++)
				printf("%d\r\n",*street_width[temp]);
		}else
		{
			Mx = *(Cmd + 1) /3;
			flag = *(Cmd + 1) % 3;
		}
		Usart_Sbuffer_Push(1,1);
	}
	if(flag != 0)
	{
		if(flag == 1)
			*street_width[Mx] += 2;
		else
			*street_width[Mx] -= 2;
	}
}

void Run(void)
{
	
}
