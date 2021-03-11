#include "main_app.h"

void main_app_Task(void)
{
	if(main_flag == 0)
	{
		main_state++;
		stateCmd_flag = 0;
		main_flag = 1;
	}
	if(main_state == 1)
		GetQrCode();
	else if(main_state == 2)
		Blobs_Recording();
	OLED_ShowNum(main_state,6,0,1);
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
		if(Read_PositionTaskEn() == 0 && Read_AttitudeFlag() == 0 && *addr != 0xff)
		{
			main_flag = 0;
			for(temp=0;temp<3;temp++)
			{
				OLED_ShowNum(*(addr+temp),1,temp*7,1);
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

