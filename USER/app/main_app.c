#include "main_app.h"

void main_app_Task(void)
{
	if(main_flag == 0)
	{
		main_state++;
		stateCmd_flag = 0;
		main_flag = 1;
		OLED_ShowString("state:",0,0,1);
	}
	if(main_state == 1)
		GetQrCode();
	else if(main_state == 2)
		Blobs_Recording();
	else if(main_state == 3)
		Get_UpBlobs();
	OLED_ShowNum(main_state,0,42,1);
}

void Get_UpBlobs(void)
{
	static uint8_t temp;
	OpenMV_Set(3);
	if(stateCmd_flag == 0)
	{
		Attitude_Set(2);
		stateCmd_flag = 1;
		PositionTask_StateSet(3);
	}else if(stateCmd_flag==1)
	{
		if(Read_PositionTaskEn() == 0 && Read_AttitudeFlag() == 0)
			stateCmd_flag++;
	}else if(stateCmd_flag == 2)
	{
		if(Read_AttitudeFlag()==0)
		{
			GetBlob_Floor(0,temp);
			stateCmd_flag++;
		}
	}else if(stateCmd_flag == 3)
	{
		if(Read_AttitudeFlag()==0)
			main_flag = 0;
	}
}

void Blobs_Recording(void)
{
	uint8_t*addr;
	uint8_t temp;
	addr = Read_Recording();
	OpenMV_Set(2);
	if(stateCmd_flag == 0)
	{
		stateCmd_flag = 1;
		Attitude_Set(2);
		PositionTask_StateSet(2);
	}else
	{
		if(Read_PositionTaskEn() == 0 && Read_AttitudeFlag() == 0 && *(addr+2) != 0)
		{
			main_flag = 0;
			OLED_ShowString("Ord:",1,0,1);
			for(temp=0;temp<3;temp++)
			{
				OLED_ShowNum(*(addr+temp),1,temp*7+28,1);
				BlobsList[temp] = *(addr+temp);
			}
		}
	}
}

void GetQrCode(void)
{
	OpenMV_Set(1);
	if(stateCmd_flag == 0)
	{
		stateCmd_flag = 1;
		Attitude_Set(1);
		PositionTask_StateSet(1);
	}else
	{
		if(Read_PositionTaskEn() == 0 && Read_AttitudeFlag() == 0 && *(Read_QrCode()) != 0)
			main_flag = 0;
	}
	
}

