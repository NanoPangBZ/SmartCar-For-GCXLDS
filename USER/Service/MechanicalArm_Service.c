#include "MechanicalArm_Service.h"
#include "street_motor.h"
#include <math.h>

void MechanicalArm_Service(void)
{
	MechanicalArm_StateUpdata();
	if(MechanicalArm_State)
	{
		if(MechanicalArm_Mode)
			MechanicalArm_LineClr();
		else
			MechanicalArm_WidthInc();
		MechanicalArm_WidthSet(Target_Width);
	}
}

void MechanicalArm_LineClr(void)
{
	
}

void MechanicalArm_IncAngleSet(int*angle,uint8_t*Inc)
{
	uint8_t temp;
	MechanicalArm_Mode = 0;
	for(temp=0;temp<5;temp++)
	{
		StateEnd_Width[temp] = AngleToWidth((double)*(angle+temp));
		Width_Inc[temp] = *(Inc+temp);
	}
}

void MechanicalArm_IncSet(uint16_t*Width,uint8_t*Inc)
{
	uint8_t temp;
	MechanicalArm_Mode = 0;
	for(temp=0;temp<5;temp++)
	{
		StateEnd_Width[temp] = *(Width+temp);
		Width_Inc[temp] = *(Inc+temp);
	}
}

void MechanicalArm_StateUpdata(void)
{
	uint8_t temp;
	uint8_t flag = 0;
	for(temp=0;temp<5;temp++)
	{
		if(*street_width[temp] != StateEnd_Width[temp])
		{
			flag = 1;
			MechanicalArm_State = 1;
			break;
		}
	}
	if(flag!=1)
		MechanicalArm_State = 0;
}

void MechanicalArm_WidthInc(void)
{
	uint8_t temp;
	for(temp=0;temp<5;temp++)
	{
		if(Target_Width[temp]<StateEnd_Width[temp])
		{
			Target_Width[temp] += Width_Inc[temp];
			if(Target_Width[temp] > StateEnd_Width[temp])
				Target_Width[temp] = StateEnd_Width[temp];
		}else
		{
			Target_Width[temp] -= Width_Inc[temp];
			if(Target_Width[temp] < StateEnd_Width[temp])
				Target_Width[temp] = StateEnd_Width[temp];
		}
	}
}

uint16_t AngleToWidth(double Angle)
{
	double temp;
	temp = Angle*Width_Unit;
	return (uint16_t)(Width_Benchmark + temp);
}

void MechanicalArm_WidthSet(uint16_t*Width)
{
	uint8_t temp;
	for(temp = 0;temp<5;temp++)
		*street_width[temp] = *(Width+temp);
	
}

uint8_t Read_MechanicalArmState(void)
{
	return MechanicalArm_State;
}

void MechanicalArm_Reset(uint8_t mode)
{
	if(mode)
	{
		MechanicalArm_WidthSet(Reset_Width);
	}else
	{
		
		MechanicalArm_WidthSet(Reset_Width);
	}
}
