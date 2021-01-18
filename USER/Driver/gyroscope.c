#include "gyroscope.h"

uint8_t Gyroscope_RequestUpdata(void)
{
	return Usart3_Send(Visit_Code,4);
}

uint8_t Gyroscope_Reset(void)
{
	return Usart3_Send(Reset_Code,4);
}

void Wait_Gyroscope(void)
{
	static uint8_t num = 0;
	static int last_Yaw = 0;
	static uint32_t last_time = 0;
	uint32_t SysSubTime = Read_SysSubTime();
	Gyroscope_RequestUpdata();
	//等待陀螺仪稳定
	while(num != 100)
	{
		//5ms读取间隔
		if(Read_SysSubTime() - last_time > 500)
		{
			last_time = Read_SysSubTime();
			if(last_Yaw != Yaw)
				num = 0;
			else
				num++;
			last_Yaw = Yaw;
			Gyroscope_RequestUpdata();
		}
	}
	Yaw_Err = Yaw;
}

void Gyroscope_Init(void)
{
	while(Usart3_Send(Init_Code,4));
	while(Usart3_Send(Reset_Code,4));
	while(Usart3_Send(Visit_Code,4));
	Wait_Gyroscope();
}

int Gyroscope_ReadYaw(void)
{
	return Yaw;
}

int Gyroscope_YawUpdata(uint8_t*dat)
{
	int temp;
	temp = (*(dat+8)<<8 | *(dat+9));
	if(temp > 18000)
		temp = -(0xffff - temp) ;
	temp -= Yaw_Err;
	Yaw = temp / 10;
	return Yaw;
}
