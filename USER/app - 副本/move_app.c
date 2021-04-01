#include "move_app.h"

void move_app_Task(void)
{
	if(Move_State)
	{
		switch(Move_Line)
		{
			case 1:
				FindQrCode_Move();
				break;
			case 2:
				FindYL_Move();
				break;
			case 3:
				GetYL_Move();
				break;
			case 4:
				PutBC_Move();
				break;
			case 5:
				BCToYL();
				break;
		}
	}
}

void BCToYL(void)
{
	static uint8_t flag = 0;
	uint8_t*TempAddr;
	uint8_t temp;
	if(flag==0)
	{
		//获取下一目标物块
		TempAddr = Read_QrCode();
		for(temp=0;temp<3;temp++)
		{
			if(*(TempAddr+temp) < 20)
			{
				Blob = *(TempAddr+temp);
				*(TempAddr+temp) += 20;
				break;
			}
		}
		TargetMove_Set(300,Blob*500+2000,1);
		flag++;
	}else if(flag == 1)
	{
		if(Read_PositionState() == 5)
		{
			VectorMove_Set(-150,0);
			flag++;
		}
	}else if(flag == 2)
	{
		TempAddr = Read_LookData();
		if(*TempAddr==Blob && *(TempAddr+1) == 14)
		{
			if(*(TempAddr+2)>68)
			{
				VectorMove_Set(-3,-80);
				flag++;
			}else if(*(TempAddr+2)<62)
			{
				VectorMove_Set(10,80);
				flag++;
			}else
			{
				PositionService_Stop();
				flag = 0;
				Move_State = 0;
			}
		}
	}else if(flag == 3)
	{
		TempAddr = Read_LookData();
		if(*(TempAddr+2)<68 && *(TempAddr+2)>62)
		{
			
		}
	}
}

uint8_t Read_MoveState(void)
{
	return Move_State;
}

void PutBC_Move(void)
{
	static uint8_t flag = 0;
	uint8_t*TempAddr;
	if(flag==0)
	{
		flag++;
		//大至移动到中线
		TargetMove_Set(0,-3300,1);
	}else if(flag == 1)
	{
		//准确移动到中线
		if(Read_PositionState() == 5 && Read_GoodsAppState() ==0)
		{
			TempAddr = Read_LineData();
			if(*TempAddr >3)
				VectorMove_Set(0,100);
			else if(*TempAddr < 3)
				VectorMove_Set(0,-100);
			flag++;
		}
	}else if(flag == 2)
	{
		//前往半成品区
		TempAddr = Read_LineData();
		if(*TempAddr == 3)
		{
			VectorMove_Set(100,0);
			flag++;
		}
	}else if(flag == 3)
	{
		TempAddr = Read_LineData();
		//修正
		if(*TempAddr!=3 && *TempAddr!=0)
		{
			if(*TempAddr >3)
				VectorMove_Set(100,20);
			else if(*TempAddr < 3)
				VectorMove_Set(100,-20);
		}else if(*TempAddr==0)
		{
			PositionService_Stop();
			flag++;
		}
	}else if(flag == 4)
	{
		switch(Blob)
		{
			case RED:
				TargetMove_Set(0,650,1);
				break;
			case GREEN:
				PositionService_Stop();
				break;
			case BLUE:
				TargetMove_Set(0,-650,1);
		}
		flag++;
	}else if(flag == 5)
	{
		if(Read_PositionState()==5)
		{
			TargetMove_Set(100,0,1);
			flag++;
		}
	}else if(flag == 6)
	{
		if(Read_PositionState() == 5)
		{
			flag = 0;
			Move_State = 0;
		}
	}
}

void GetYL_Move(void)
{
	static uint8_t flag = 0;
	uint8_t temp;
	uint8_t cx;
	uint8_t*TempAddr;
	if(flag  == 0)
	{
		//取任务码地址
		TempAddr = Read_QrCode();
		for(temp=0;temp<7;temp++)
		{
			if(*(TempAddr + temp) < 20 && temp!= 3)	//屏蔽了'+'号
			{
				Blob = *(TempAddr + temp) ;
				*(TempAddr + temp) += 20;
				break;
			}
		}
		//取Recording地址 获取目标位置
		TempAddr = Read_Recording();
		for(temp=0;*(TempAddr+temp)!=Blob;temp++);
		flag++;
	}else if(flag==1)	//等待对齐
	{
		TempAddr = Read_LookData();
		cx = *(TempAddr+1);
		if(*TempAddr== Blob && cx==14)
		{
			PositionService_Stop();
			flag = 2;
		}
	}else if(flag == 2)
	{
		//远进调整 addr1指向LookData.w
			TempAddr = Read_LookData() + 2;
			if(*TempAddr > 68 )
			{
				VectorMove_Set(-3,-80);
				flag = 3;
			}else if(*TempAddr < 62)
			{
				VectorMove_Set(10,80);
				flag =3;
			}else
			{
				flag = 4;
			}
	}else if(flag == 3)
	{
		//等待远近调整完成 附带对齐修正
			TempAddr = Read_LookData()+2;
			if(*TempAddr<68 && *TempAddr>62)
			{
				PositionService_Stop();
				flag = 4;
			}
	}else if(flag==4)
	{
		Move_State = 0;
		flag = 0;
	}
}

void FindYL_Move(void)
{
	static uint8_t flag = 0;
	uint8_t*TempAddr;
	uint8_t temp;
	if(flag==0)
	{
		flag++;
		TargetMove_Set(2100,0,1);
		TempAddr = Read_QrCode();
		for(temp=0;temp<3;temp++)
		{
			if(*(TempAddr+temp)<20)
			{
				Blob = *(TempAddr+temp);
				*(TempAddr+temp) += 20;
				break;
			}
		}
	}else if(flag == 1)
	{
		if(Read_PositionState()==5)
		{
			VectorMove_Set(150,0);
			flag=2;
		}
	}else if(flag == 2)
	{
		TempAddr = Read_LookData();
		if(*TempAddr == Blob && *(TempAddr+1)==14)
		{
			if(*(TempAddr+2)<62)
			{
				VectorMove_Set(10,80);
				flag++;
			}else if(*(TempAddr+2)>68)
			{
				VectorMove_Set(-3,-80);
				flag++;
			}else
			{
				PositionService_Stop();
				Move_State = 0;
				flag = 0;
			}
		}
	}else if(flag == 3)
	{
		TempAddr = Read_LookData();
		if(*(TempAddr+2)>62 && *(TempAddr+2)<68)
		{
			PositionService_Stop();
			Move_State = 0;
			flag = 0;
		}
	}
}

void MoveCmd_Set(uint8_t Line)
{
	Move_Line = Line;
	Move_State = 1;
}

void FindQrCode_Move(void)
{
	static uint8_t flag = 0;
	if(flag == 0)
	{
		flag = 1;
		ClawClr(0,2);
		TargetMove_Set(0,-1100,1);
	}else if(flag == 1)
	{
		if(Read_PositionState() == 5)
		{
			flag = 2;
			TargetMove_Set(1800,0,1);
		}
	}else if(flag == 2)
	{
		if(Read_PositionState() == 5)
		{
			flag = 0;
			Move_State = 0;
		}
	}
}

