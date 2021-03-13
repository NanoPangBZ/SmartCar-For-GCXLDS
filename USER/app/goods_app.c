#include "goods_app.h"
#include "angle_list.h"

void goods_app_Task(void)
{
	if(Attitude_Flag == 1)
	{
		if(Read_MechanicalArmState() != 1)
		{
			Attitude_State++;
			switch(Attitude_Line)
			{ 
				case 0:
					GetBlob_FloorRun();
					break;
				case 1:
					break;
				case 2:
					PutBlob_FloorRun();
					break;
				case 3:
					break;
				case 4:
					Attitude_SetRun();
					break;
			}
		}
	}
}

uint8_t Read_AttitudeFlag(void)
{
	return Attitude_Flag;
}

void PutBlob_FloorRun(void)
{
	uint8_t temp;
	switch(Attitude_State)
	{
		case 1:
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(*(PutBlob_Ready[Target_Pos]+temp)),*(PutBlob_Readytnc[Target_Pos]+temp),temp);
			break;
		case 2:
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(*(PutBlob_Adjust[Target_Pos]+temp)),*(PutBlob_Adjustnc[Target_Pos]+temp),temp);
			break;
		case 3:
			ClawClr(0,2);
			break;
		case 4:
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(*(PutBlob_Ready[Target_Pos]+temp)),*(PutBlob_Readytnc[Target_Pos]+temp),temp);
			break;
		case 5:
			Attitude_Flag = 0;
			break;
	}
}

uint8_t PutBlob_Floor(uint8_t Pos)
{
	if(Attitude_Flag)
		return 1;
	Attitude_Line = 2;
	Attitude_Flag = 1;
	Attitude_State=0;
	Target_Pos = Pos;
	return 0;
}

void GetBlob_FloorRun(void)
{
	uint8_t temp;
	switch(Attitude_State)
	{
		case 1:
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(*(GetBlob_Ready[Target_Pos]+temp)),*(GetBlob_ReadyInc[Target_Pos]+temp),temp);
			break;
		case 2:
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(*(GetBlob_Adjust[Target_Pos]+temp)),*(GetBlob_AdjustInc[Target_Pos]+temp),temp);
			break;
		case 3:
			ClawClr(2,2);
			break;
		case 4:
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(*(GetBlob_Ready[Target_Pos]+temp)),*(GetBlob_ReadyInc[Target_Pos]+temp),temp);
			break;
		case 5:
			Attitude_Flag = 0;
			break;
	}
}

void Attitude_SetRun(void)
{
	uint8_t temp;
	if(Attitude_State == 2)
	{
		Attitude = Target_Attitude;
		Attitude_Flag = 0;
	}else
	{
		ClawClr(0,1);
		for(temp=0;temp<4;temp++)
			TargetWidth_Set(AngleToWidth(*(Attitude_Angle[Target_Attitude]+temp)),*(Attitude_Inc[Target_Attitude]+temp),temp);
	}
}

uint8_t GetBlob_Floor(uint8_t Pos,uint8_t Blob)
{
	if(Attitude_Flag)
		return 1;
	Attitude_Line = 0;
	Attitude_Flag = 1;
	Attitude_State=0;
	Target_Pos = Pos;
	Target_Blob = Blob;
	return 0;
}

uint8_t GetBlob_Warehouse(uint8_t Blob)
{
	uint8_t temp;
	if(Attitude_Flag)
		return 1;
	Attitude_Line = 1;
	Attitude_Flag = 1;
	Attitude_State=0;
	for(temp=0;Warehouse[temp]!=Blob;temp++);
	Target_Warehouse = temp;
	return 0;
}

uint8_t PutBlob_Warehouse(void)
{
	uint8_t temp;
	if(Attitude_Flag)
		return 1;
	Attitude_Line = 4;
	Attitude_Flag = 1;
	Attitude_State=0;
	for(temp=0;Warehouse[temp]!=None;temp++);
	Target_Warehouse = temp;
	return 0;
}

uint8_t Attitude_Set(uint8_t Attitude)
{
	if(Attitude_Flag)
		return 1;
	Target_Attitude = Attitude;
	Attitude_Line = 4;
	Attitude_Flag = 1;
	Attitude_State=0;
	return 0;
}


