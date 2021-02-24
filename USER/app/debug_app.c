#include "debug_app.h"
#include "street_motor.h"

void debug_app_Task(void)
{
//	if(ReturnState)
//	{
//		ReturnSpeed();
//		ReturnPosition();
//		ReturnYaw();
//		Vofa_Send();
//	}
//	MechanicalArm_Debug();
//	uint8_t temp;
//	if(ReturnState)
//	{
//		for(temp=0;temp<5;temp++)
//			Vofa_Input((float)*(street_width[temp]),temp);
//		Vofa_Send();
//	}
	MechanicalArm_AngleDebug();
}

void MechanicalArm_AngleDebug(void)
{
//	*street_width[0] = AngleToWidth(90.0);
//	*street_width[1] = AngleToWidth(45.0);
//	*street_width[2] = AngleToWidth(45.0);
//	*street_width[3] = AngleToWidth(45.0);
}

void MechanicalArm_Debug(void)
{
	static uint8_t StreetNum = 0;
	static uint8_t Inc_Dir = 0;	//0:无增长  1:增长  2:递减
	uint8_t *cmd;
	cmd = Read_Usart_Sbuffer(1);
	if(*cmd!=0)
	{
		if(*(cmd+1) != 0xff)
		{
			StreetNum = *(cmd+1) / 3;
			Inc_Dir = *(cmd+1)%3;
		}else
		{
			uint8_t temp;
			printf("==============\r\n");
			for(temp=0;temp<5;temp++)
				printf("%d\r\n",*street_width[temp]);
		}
		Usart_Sbuffer_Push(1,1);
	}
	if(Inc_Dir == 1)
	{
		*street_width[StreetNum] += 1;
	}else if(Inc_Dir == 2)
	{
		*street_width[StreetNum] -= 1;
	}
}

void ReturnYaw(void)
{
	int Yaw;
	Yaw = Gyroscope_ReadYaw();
	Vofa_Input((float)Yaw,6);
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
