#include "test_app.h"
#include <math.h>

#define val	3.14/180

void test_app_task(void)
{
	//TestPart1();
//	TestPart2();
	TestPart2_1();
}

void TestPart2_1(void)
{
	static uint8_t flag = 0;
	static int angle[2][5] = {{90,45,-90,45,0},{0,45,-90,45,0}};
	static uint8_t inc[5] = {1,1,1,1,1};
	if(Read_MechanicalArmState() == 0)
	{
		if(flag)
		{
			MechanicalArm_IncAngleSet(angle[flag],inc);
			flag = 0;
		}else
		{
			MechanicalArm_IncAngleSet(angle[flag],inc);
			flag = 1;
		}
	}
}

void TestPart2(void)
{
	static uint8_t flag = 0;
	static uint16_t Width[2][5] = {{2550,2025,450,2025,800},{1500,2025,450,2025,800}}; 
	static uint8_t Inc[5] = {1,1,1,1,1};
	if(Read_MechanicalArmState() == 0)
	{
		if(flag)
		{
			flag = 0;
			MechanicalArm_IncSet(Width[0],Inc);
		}else
		{
			flag = 1;
			MechanicalArm_IncSet(Width[1],Inc);
		}
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
