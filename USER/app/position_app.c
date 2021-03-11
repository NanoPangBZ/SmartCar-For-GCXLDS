#include "position_app.h"

void position_app_Task(void)
{
	if(PositionTask_En != 0)
	{
		switch(PositionTask_State)
		{
			case 1:
				FindQrcode_Move();
				break;
			case 2:
				FindBlobs_Move();
				break;
		}
	}
}

void PositionTask_StateSet(uint8_t state)
{
	if(PositionTask_En!=1)
	{
		PositionTask_State = state;
		PositionTask_En = 1;
	}
}

void FindBlobs_Move(void)
{
	static uint8_t flag = 0;
	if(Read_PositionState() == 5)
	{
		flag++;
		if(flag == 1)
		{
			TargetMove_Set(5000,0,1);
		}else if(flag == 2)
		{
			PositionTask_En = 0;
		}
	}
}

void FindQrcode_Move(void)
{
	static uint8_t flag = 0;
	if(Read_PositionState() == 5)
	{
		flag++;
		if(flag == 1)
		{
			TargetMove_Set(0,-1000,1);
		}else if(flag == 2)
		{
			TargetMove_Set(1800,0,1);
		}else if(flag == 3)
		{
			PositionTask_En = 0;
		}
	}
}

uint8_t Read_PositionTaskEn(void)
{
	return PositionTask_En;
}
