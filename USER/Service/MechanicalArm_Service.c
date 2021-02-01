#include "MechanicalArm_Service.h"

void MechanicalArm_Inc(void)
{
	uint8_t temp;
	uint8_t flag  =1;
	for(temp=0;temp<5;temp++)
	{
		if(*street_width[temp] != Width_Target[temp])
		{
			flag = 0;
			break;
		}
	}
	if(flag)
		MechanicalArm_State = 0;
	for(temp=0;temp<5;temp++)
	{
		if(*street_width[temp] < Width_Target[temp])
		{
			if(*street_width[temp] + WidthInc[temp] < Width_Target[temp])
				*street_width[temp] += WidthInc[temp];
			else
				*street_width[temp] = Width_Target[temp];
		}else
		{
			if(*street_width[temp] > Width_Target[temp] + WidthInc[temp])
				*street_width[temp] -= WidthInc[temp];
			else
				*street_width[temp] = Width_Target[temp];
		}
	}
}

void MechanicalArm_Service(void)
{
	switch(MechanicalArm_State)
	{
		case 1:
			break;
		case 2:
			break;
		default:break;
	}
}

uint8_t Read_MechanicalArmState(void)
{
	return MechanicalArm_State;
}

void Cash(void)
{
	Width_Target[4] = 1350;
}

void Put(void)
{
	Width_Target[4] = 700;
}

void MechanicalArm_WidthSet(uint16_t*Width,uint8_t*Inc)
{
	uint8_t temp;
	for(temp=0;temp<4;temp++)
		Width_Target[temp] = *(Width+temp);
	if(Inc!=NULL)
	{
		for(temp = 0;temp < 4;temp++)
			Width_Target[temp] = *(Inc+temp);
	}
	MechanicalArm_State = 1;
}

void MechanicalArm_Reset(uint8_t mode)
{
	uint8_t temp;
	if(mode != 0)
	{
		for(temp = 0;temp < 5;temp++)
		{
			*street_width[temp] = Reset_Value[temp];
			Width_Target[temp] = Reset_Value[temp];
		}
	}else
	{
		for(temp = 0;temp<5;temp++)
			Width_Target[temp] = Reset_Value[temp];
	}
}

