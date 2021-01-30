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
	if(Read_PositionState()==5)
	{
		TargetMove_Set(PositionList[Ecode][0],PositionList[Ecode][1],0);
	}
}

//等待发车命令
void WaitStart(void)
{
	if(0)
		RunState = 1;
}

