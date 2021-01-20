#include "MechanicalArm_Clr.h"

void Angle_Realize(void)
{
	uint8_t temp;
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

uint8_t Street_Check(void)
{
	uint8_t temp;
	for(temp=0;temp<5;temp++)
	{
		if(*street_width[temp] != Width_Target[temp])
			return 1;
	}
	return 0;
}

void Cash(void)
{
	Width_Target[4] = 1350;
}

void Put(void)
{
	Width_Target[4] = 500;
}

void Target_WidthSet(uint16_t*Width)
{
	uint8_t temp;
	for(temp=0;temp<4;temp++)
		Width_Target[temp] = *(Width+temp);
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
		{
			WidthInc[temp] = WidthInc_Max;
			Width_Target[temp] = Reset_Value[temp];
		}
	}
}

