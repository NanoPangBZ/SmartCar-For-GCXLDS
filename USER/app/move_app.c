#include "move_app.h"

void move_app_Task(void)
{
	if(move_flag)
		MoveRun();
}

void FindQrCode_MoveTask(void)
{
	if(move_state == 0)
	{
		TargetMove_Set(0,-1000,1);
		move_state++;
	}else if(move_state==1)
	{
		if(Read_PositionState() == 5)
		{
			TargetMove_Set(1800,0,1);
			move_state++;
		}
	}else if(move_state == 2)
	{
		if(Read_PositionState() == 5)
		{
			move_state = 0;
			move_flag = 0;
		}
	}
}

void FindBlob_MoveTask(void)
{
	uint8_t*TempAddr;
	uint8_t temp;
	if(move_state == 0)
	{
		TempAddr = Read_QrCode();
		for(temp=0;temp<7;temp++)
		{
			if(*(TempAddr+temp)<30 && temp!= 3)
			{
				Blob = *(TempAddr+temp);
				*(TempAddr+temp) += 30;
				OLED_ShowNum(Blob,1,0,1);
				break;
			}
		}
		TargetMove_Set(2400,0,1);
		move_state++;
	}else if(move_state == 1)
	{
		if(Read_PositionState() == 5)
		{
			OpenMV_Set(2);
			VectorMove_Set(150,0);
			move_state++;
		}
	}else if(move_state == 2)
	{
		TempAddr = Read_LookData();
		if(*(TempAddr) == Blob && *(TempAddr+1) == 13)
		{
			//远近调整
			if(*(TempAddr+2)>68)
			{
				VectorMove_Set(-3,-80);
				move_state++;
			}else if(*(TempAddr+2)<58)
			{
				VectorMove_Set(10,80);
				move_state++;
			}else
			{
				PositionService_Stop();
				move_state = 0;
				move_flag = 0;
			}
		}
	}else if(move_state == 3)
	{
		//等待远近调整
		TempAddr = Read_LookData();
		if(*(TempAddr +2)<68 && *(TempAddr +2)>58)
		{
			PositionService_Stop();
			move_state = 0;
			move_flag = 0;
		}
	}
}

void PutYL_MoveTask(void)
{
	uint8_t*TempAddr;
	if(move_state==0)
	{
		move_state++;
		//大致对齐中线
		TargetMove_Set(-300,-3000,1);
		OpenMV_Set(3);
	}else if(move_state==1)
	{
		if(Read_PositionState() == 5)
		{
			//调整
			TempAddr = Read_LineData();
			if(*TempAddr > 3)
			{
				VectorMove_Set(0,80);
				move_state++;
			}else if(*TempAddr < 3)
			{
				VectorMove_Set(0,-80);
				move_state++;
			}else
			{
				move_state+=2;
			}
		}
	}else if(move_state == 2)
	{
		TempAddr = Read_LineData();
		if(*TempAddr == 3)
		{
			PositionService_Stop();
			move_state++;
		}
	}else if(move_state == 3)
	{
		VectorMove_Set(100,0);
		move_state++;
	}else if(move_state == 4)
	{
		//注意修正
		TempAddr = Read_LineData();
		if(*TempAddr>3)
		{
			VectorMove_Set(100,20);
		}else if(*TempAddr<3 && *TempAddr!=0)
		{
			VectorMove_Set(100,-20);
		}else if(*TempAddr==3)
		{
			VectorMove_Set(100,0);
		}else if(*TempAddr==0)
		{
			PositionService_Stop();
			switch(Blob)
			{
				case 1:
					TargetMove_Set(0,550,1);
					break;
				case 2:
					break;
				case 3:
					TargetMove_Set(0,-550,1);
					break;
			}
			move_state++;
		}
	}else if(move_state == 5)
	{
		if(Read_PositionState() == 5)
		{
			TargetMove_Set(100,0,1);
			move_state++;
		}
	}else if(move_state == 6)
	{
		if(Read_PositionState() == 5)
		{
			PositionService_Stop();
			move_state = 0;
			move_flag = 0;
		}
	}
}

void BCToYL_MoveTask(void)
{
	uint8_t*TempAddr;
	uint8_t temp;
	if(move_state == 0)
	{
		TargetMove_Set(100,Blob*500 + 2000,1);
		move_state++;
	}else if(move_state == 1)
	{
		if(Read_PositionState() == 5)
		{
			TargetMove_Set(300,0,1);
			OpenMV_Set(2);
			move_state++;
		}
	}else if(move_state == 2)
	{
		if(Read_PositionState() == 5)
		{
			TempAddr = Read_QrCode();
			for(temp = 0;temp<3;temp++)
			{
				if(*(TempAddr+temp) < 30)
				{
					Blob = *(TempAddr+temp);
					*(TempAddr+temp) += 30;
					break;
				}
			}
			VectorMove_Set(-150,0);
			move_state++;
		}
	}else if(move_state == 3)
	{
		TempAddr = Read_LookData();
		if(*(TempAddr) == Blob && *(TempAddr+1) == 13)
		{
			//远近调整
			if(*(TempAddr+2)>68)
			{
				VectorMove_Set(-3,-80);
				move_state++;
			}else if(*(TempAddr+2)<58)
			{
				VectorMove_Set(10,80);
				move_state++;
			}else
			{
				PositionService_Stop();
				move_state = 0;
				move_flag = 0;
			}
		}
	}else if(move_state == 4)
	{
		//等待远近调整
		TempAddr = Read_LookData();
		if(*(TempAddr +2)<68 && *(TempAddr +2)>58)
		{
			PositionService_Stop();
			move_state = 0;
			move_flag = 0;
		}
	}
}

/*****************对外接口***************/
void BCToYL_Move(void)
{
	MoveRun = BCToYL_MoveTask;
	move_state = 0;
	move_flag = 1;
}

void PutYL_Move(void)
{
	MoveRun = PutYL_MoveTask;
	move_state = 0;
	move_flag = 1;
}

void FindQrCode_Move(void)
{
	MoveRun = FindQrCode_MoveTask;
	move_flag = 1;
}

void FindBlob_Move(void)
{
	MoveRun = FindBlob_MoveTask;
	move_flag = 1;
}

uint8_t Read_MoveFlag(void)
{
	return move_flag;
}

uint8_t Read_MoveState(void)
{
	return move_state;
}
