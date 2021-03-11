#include "test_app.h"
#include <math.h>

#define val	3.14/180

void test_app_task(void)
{
	static uint8_t flag = 0;
	static uint8_t state = 0;
	if(flag == 0)
	{
		flag = 1;
		if(state == 0)
			Attitude_Set(2);
		else if(state == 1)
			GetBlob_Floor(0,RED);
	}
	if(Read_AttitudeFlag() == 0)
	{
		flag = 0;
		state++;
	}
//	TestPart1();
//	TestPart2();
//	static uint8_t flag = 0;
//	if(Read_MechanicalArmState() == 0)
//	{
//		if(flag)
//		{
//			MechanicalArm_PostionLineSet(200,100,225,50);
//			flag = 0;
//		}else
//		{
//			flag =1;
//			MechanicalArm_PostionLineSet(225,50,225,100);
//		}
//	}
}

void TestPart2(void)
{
	uint8_t*Cmd;
	Cmd = Read_Usart_Sbuffer(1);
	if(*Cmd >1)
	{
		if(*(Cmd+1)>0)
			Attitude_Set(*(Cmd+2));
		else
			GetBlob_Floor(*(Cmd+2),RED);
		Usart_Sbuffer_Push(1,2);
	}
}

void TestPart1(void)
{
	//圆周运动
	static int Angle = 0;
	static uint16_t IncTime = 0;
	int Xspeed,Yspeed;
	if(IncTime==10)
	{
		Angle++;
		Xspeed = (int)(sin((double)(Angle*val))*150);
		Yspeed = (int)(cos((double)(Angle*val))*150);
		VectorMove_Set(Xspeed,Yspeed);
		IncTime =0;
	}
	IncTime++;
}
