#include "MechanicalArm_Service.h"
#include "street_motor.h"
#include <math.h>

void MechanicalArm_Service(void)
{
	MechanicalArm_StateUpdata();
	if(MechanicalArm_State)
	{
		if(MechanicalArm_Mode)
			printf("A");
		else
			MechanicalArm_WidthInc();
		MechanicalArm_WidthSet(Target_Width);
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
	if(temp>0)
		return (uint16_t)temp+Width_Benchmark;
	return 0xffff;
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
	uint8_t temp;
	if(mode)
	{
		MechanicalArm_WidthSet(Reset_Width);
	}else
	{
		
		for(temp=0;temp<4;temp++)
			Target_Width[temp] = Reset_Width[temp];
	}
}
