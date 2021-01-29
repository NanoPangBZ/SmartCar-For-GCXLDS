#include "main_app.h"
#include "position.h"

void main_app_Task(void)
{
	if(RunState==0)
	{
		WaitStart();
		return;
	}
	
}

//寻找二维码
void Find_Ecode(void)
{
	long int*temp;
	long int Nposition[2];
	temp = Read_Position();
	Nposition[0] = *temp;
	Nposition[1] = *(temp+1);
	TargetPosition[0] = PositionList[Ecode][0];
}

//等待发车命令
void WaitStart(void)
{
	if(0)
		RunState = 1;
}

