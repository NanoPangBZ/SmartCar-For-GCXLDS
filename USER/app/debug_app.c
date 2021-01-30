#include "debug_app.h"
#include "cmd_list.h"

void debug_app_Task(void)
{
	if(ReturnState)
	{
		ReturnSpeed();
		ReturnPosition();
		Usart1_Send(DataScope_OutPut_Buffer,DataScope_Data_Generate(6));
	}
}

void Usart_Help(void)
{
	static uint32_t last_time = 0;
	
}

void ReturnPosition(void)
{
	long int*Position;
	Position = Read_Position();
	DataScope_Get_Channel_Data((float)(*Position)/10,5);
	DataScope_Get_Channel_Data((float)(*(Position+1))/10,6);
}

void ReturnSpeed(void)
{
	int*Speed;
	uint8_t temp;
	Speed = Read_Speed();
	for(temp=0;temp<4;temp++)
		DataScope_Get_Channel_Data((float)*(Speed+temp),temp+1);
}
