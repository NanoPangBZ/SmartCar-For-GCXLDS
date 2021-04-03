#include "system_core.h"

void test_app_task(void)
{
    
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
		Xspeed = (int)(sin((double)(Angle*val))*5000);
		Yspeed = (int)(cos((double)(Angle*val))*5000);
		VectorMove_Set(Xspeed,Yspeed);
		IncTime =0;
	}
	IncTime++;
}