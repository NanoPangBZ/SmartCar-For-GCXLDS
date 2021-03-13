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
			case 3:
				GetBlob_Move();
				break;
		}
	}
}

void PositionTask_StateSet(uint8_t state)
{
		PositionTask_State = state;
		PositionTask_En = 1;
}

void GetBlob_Move(void)
{
	static uint8_t flag = 1;
	static uint8_t Blob;
	static uint8_t Pos;
	uint8_t*TempAddr1,*TempAddr2;
	uint8_t temp;
		if(flag==1)
		{
			//本环节addr1作为任务码地址 addr2物块排列地址
			TempAddr1 = Read_QrCode();
			TempAddr2 = Read_Recording();
			//根据任务码确定目标物块,并在任务码数组中将他置位
			for(temp=0;temp<7;temp++)
			{
				if(*(TempAddr1+temp) != 0 &&  temp!=3)	//屏蔽了任务码中的'+'字符
				{
					Blob = *(TempAddr1+temp);
					*(TempAddr1+temp) = 0;		//将取读到的任务码清0
				}
			}
			//根据物块排列表确定位置
			for(temp=0;temp<3;temp++)
			{
				if(Blob == *(TempAddr2+temp))
					Pos = temp;
			}
			//向目标位置对齐 addr1重新指向LoodData
			TempAddr1 = Read_LookData();
			switch(Pos)
			{
				case 0:
					VectorMove_Set(-150,0);
					break;
				case 1:
					if(*(TempAddr1+1)<14)
						VectorMove_Set(120,0);
					else if(*(TempAddr1+1)>18)
						VectorMove_Set(-120,0);
					else
						flag++;
					break;
				case 2:
					VectorMove_Set(150,0);
					break;
			}
			flag++;
		}else if(flag == 2)
		{
			//等待到达目标物块前方
			TempAddr1 = Read_LookData();
			if(*TempAddr1== Blob && *(TempAddr1+1)>14 && *(TempAddr1+1)<18)
			{
				PositionService_Stop();
				flag = 3;
			}
		}else if(flag == 3)
		{
			//远进调整 addr1指向LookData.w
			TempAddr1 = Read_LookData() + 2;
			if(*TempAddr1 > 70 )
			{
				VectorMove_Set(-3,-80);
				flag = 4;
			}else if(*TempAddr1 < 58)
			{
				VectorMove_Set(10,80);
				flag =4;
			}else
			{
				flag = 5;
			}
		}else if(flag == 4)
		{
			//等待远近调整完成 附带对齐修正
			TempAddr1 = Read_LookData()+2;
			if(*TempAddr1<70 && *TempAddr1>58)
			{
				PositionService_Stop();
				OLED_ShowNum(*TempAddr1,2,0,1);
				flag = 5;
			}
		}else if(flag == 5)
		{
			PositionTask_En = 0;
		}
		OLED_ShowNum(flag,5,0,1);
		
}

void FindBlobs_Move(void)
{
	static uint8_t flag = 0;
	if(Read_PositionState() == 5)
	{
		flag++;
		if(flag == 1)
		{
			TargetMove_Set(1200,0,1);
		}else if(flag == 2)
		{
			VectorMove_Set(150,0);
		}else if(flag == 3)
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
