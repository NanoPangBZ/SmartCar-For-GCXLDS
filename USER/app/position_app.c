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
	static uint8_t flag = 0;
	static uint8_t Blob = 0;
	uint8_t temp;
	uint8_t*TaskAddr,*ListAddr;
	if(flag==0)
	{
		TaskAddr = Read_Recording();
		ListAddr = Read_QrCode();
		//取任务码中未完成的物块
		for(temp=0;temp<3;temp++)
			if(*(TaskAddr+temp) != 0)
			{
				Blob = *(TaskAddr+temp);
				*(TaskAddr+temp) = 0;
				break;
			}
		OLED_ShowNum(Blob,2,0,1);
		//确定物块再Recording[]中的位置
		for(temp = 0;temp<3;temp++)
		{
			if(*(ListAddr+temp) == Blob)
			{
				switch(temp)
				{
					case 0:
						VectorMove_Set(-150,0);
						flag = 1;
						break;
					case 1:
						flag = 2;
						break;
					case 2:
						VectorMove_Set(150,0);
						flag = 1;
						break;
				}
				break;
			}
		}
	}else if(flag == 1)        //x对齐
	{
		TaskAddr = Read_LookData();
		if(*TaskAddr == Blob)
		{
			PositionService_Stop();
			OLED_ShowNum(*(TaskAddr+2),3,0,2);
			if(*(TaskAddr+2) > 41)
			{
				VectorMove_Set(0,-100);
				flag++;
			}else if(*(TaskAddr+2) < 39)
			{
				VectorMove_Set(0,100);
				flag++;
			}else
			{
				flag += 2;
			}
		}
	}else if(flag == 2)	//远近调整
	{
		TaskAddr = Read_LookData();
		if(*(TaskAddr+2) < 46 && *(TaskAddr+2) > 34)
		{
			PositionService_Stop();
			flag++;
		}
	}else if(flag == 3)
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
