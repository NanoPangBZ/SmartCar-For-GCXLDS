#include "debug_app.h"
#include "cmd_list.h"

void debug_app_Task(void)
{
	if(ReturnState)
	{
		ReturnSpeed();
		ReturnPosition();
		ReturnYaw();
		Vofa_Send();
	}
}

void Usart_Print(uint8_t*dat)
{
	
}

void Usart_Help(void)
{
	
}

void ReturnYaw(void)
{
	int Yaw;
	Yaw = Gyroscope_ReadYaw();
	Vofa_Input((float)Yaw/10,6);
}

void ReturnPosition(void)
{
	long int*Position;
	Position = Read_Position();
	Vofa_Input((float)*Position,4);
	Vofa_Input((float)*(Position+1),5);
}

void ReturnSpeed(void)
{
	int*Speed;
	uint8_t temp;
	Speed = Read_Speed();
	for(temp = 0;temp <4;temp++)
		Vofa_Input((float)*(Speed+temp),temp);
}
