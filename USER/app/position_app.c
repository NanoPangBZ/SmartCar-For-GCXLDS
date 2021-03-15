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
			case 4:
				PutNBlob_Move();
				break;
			case 5:
				GoBackBCToYL();
				break;
		}
	}
}

void PositionTask_StateSet(uint8_t state)
{
		PositionTask_State = state;
		PositionTask_En = 1;
}

void PutNBlob_Move(void)
{
	static uint8_t flag = 0;
	uint8_t temp;
	uint8_t*TempAddr;
	if(flag == 0)
	{
		switch(Blob)
			{
				case RED:
					TargetMove_Set(0,-2650,1);
					break;
				case GREEN:
					TargetMove_Set(0,-3200,1);
					break;
				case BLUE:
					TargetMove_Set(0,-3750,1);
					break;
			}
		OLED_ShowNum(Blob,5,0,1);
		flag = 1;
	}else if(flag == 1)
	{
		if(Read_PositionState() == 5)
		{
			flag++;
			TempAddr = Read_Recording();
			for(temp=0;temp<3;temp++)
			{
				if(*(TempAddr+temp) == Blob)
				{
					Pos = temp;
					break;
				}
			}
			switch(Pos)
			{
				case 0:
					TargetMove_Set(2200,0,1);
					break;
				case 1:
					TargetMove_Set(1700,0,1);
					break;
				case 2:
					TargetMove_Set(1200,0,1);
					break;
			}
		}
	}else if(flag == 2)
	{
		if(Read_PositionState() == 5)
		{
			PositionTask_En = 0;
			flag = 0;
		}
	}
	OLED_ShowNum(Pos,4,0,1);
}

void GoBackBCToYL(void)
{
	static uint8_t flag = 0;
	uint8_t*TempAddr;
	uint8_t temp;
	if(flag == 0)
	{
		switch(Blob)
		{
			case RED:
				TargetMove_Set(0,2500,1);
				break;
			case GREEN:
				TargetMove_Set(0,3000,1);
				break;
			case BLUE:
				TargetMove_Set(0,3500,1);
				break;
		}
		flag++;
	}else if(flag == 1)
	{
		if(Read_PositionState() == 5)
		{
			TempAddr = Read_QrCode();
			for(temp=0;temp<3;temp++)
			{
				if(*(TempAddr+temp) < 20)
				{
					Blob = *(TempAddr+ temp);
					*(TempAddr+temp) += 20;
					break;
				}
			}
			VectorMove_Set(-130,0);
			flag++;
		}
	}else if(flag == 2)
	{
		TempAddr = Read_LookData();
		if(*TempAddr== Blob && *(TempAddr+1)>14 && *(TempAddr+1)<18)
		{
			if(*(TempAddr+2)>70)
				VectorMove_Set(0,-80);
			else if(*(TempAddr+2)<58)
				VectorMove_Set(0,80);
			else
				PositionService_Stop();
			flag++;
		}
	}else if(flag==3)
	{
		//等待远近调整完成 附带对齐修正
		TempAddr = Read_LookData()+2;
		if(*TempAddr<70 && *TempAddr>58)
		{
			PositionService_Stop();
			PositionTask_En = 0;
			flag = 0;
		}
	}
}

void GetBlob_Move(void)
{
	static uint8_t flag = 1;
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
				if(*(TempAddr1+temp) < 20 &&  temp!=3)	//屏蔽了任务码中的'+'字符
				{
					Blob = *(TempAddr1+temp);
					*(TempAddr1+temp) += 20;		//表示已经运送至原料区
					break;
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
			if(*TempAddr1== Blob && *(TempAddr1+1)>15 && *(TempAddr1+1)<17)
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
			}else if(*TempAddr1 < 59)
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
			if(*TempAddr1<70 && *TempAddr1>59)
			{
				PositionService_Stop();
				flag = 5;
			}
		}else if(flag == 5)
		{
			PositionTask_En = 0;
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
