#include "main_app.h"

void main_app_Task(void)
{
	if(main_app_flag)
	{
		switch(main_state)
		{
			case 0:
				Find_QrCode();
				break;
			case 1:
				Find_Blob();
				break;
			case 2:
				PutYL_Blob();
				break;
		}
	}
}

void PutYL_Blob(void)
{
	uint8_t*TempAddr;
	uint8_t temp;
	uint8_t Endflag=0;
	if(state == 0)
	{
		PutYL_Move();
		FindLine_Attitude(0);
		state++;
	}else if(state == 1)
	{
		if(Read_AttitudeFlag() == 0 && Read_MoveFlag() == 0)
		{
			PutBlob_Attituede(0);
			state++;
		}
	}else if(state == 2)
	{
		if(Read_AttitudeFlag() == 0)
		{
			TempAddr = Read_QrCode();
			for(temp=0;temp<3;temp++)
				if(*(TempAddr+temp)<30)
				{
					Endflag = 1;
					break;
				}
			if(Endflag)
			{
				BCToYL_Move();
				FindUpBlob_Attitude();
				state++;
			}else
			{
				state = 0;
				main_state++;
			}
		}
	}else if(state == 3)
	{
		if(Read_AttitudeFlag() == 0 && Read_MoveFlag() == 0)
		{
			GetBlob(0);
			state++;
		}
	}else if(state == 4)
	{
		if(Read_AttitudeFlag()==0)
		{
			OpenMV_Set(3);
			state = 0;		
		}
	}
	OLED_ShowString("PutBlob",0,0,1);
}

void Find_QrCode(void)
{
	if(state == 0)
	{
		FindQrCode_Move();
		OpenMV_Set(1);
		FindQrCode_Attitude();
		ClawClr(0,2);
		state = 1;
	}else if(state == 1)
	{
		if(Read_MoveFlag() == 0 && *(Read_QrCode()+3) != 0)
		{
			main_state++;
			state = 0;
		}
	}
	OLED_ShowString("FindQrCode",0,0,1);
}

void Find_Blob(void)
{
	if(state == 0)
	{
		FindBlob_Move();
		FindUpBlob_Attitude();
		state++;
	}else if(state == 1)
	{
		if(Read_AttitudeFlag()==0 && Read_MoveFlag()==0)
		{
			GetBlob(0);
			state++;
		}
	}else if(state == 2)
	{
		if(Read_AttitudeFlag()==0)
		{
			state = 0;
			main_state = 2;
		}
	}
	OLED_ShowString("FindBlob",0,0,1);
}
