#include "MechanicalArm_Service.h"
#include "street_motor.h"
#include <math.h>

void MechanicalArm_Service(void)
{
	MechanicalArm_StateUpdata();
	if(MechanicalArm_State)
	{
		if(MechanicalArm_Mode)
			MechanicalArm_PositionInc();
		else
			MechanicalArm_WidthInc();
	}
}

void MechanicalArm_StateUpdata(void)
{
	if(MechanicalArm_State != 0)
	{
		uint8_t temp;
		if(MechanicalArm_Mode)
		{
			if(MechanicalArm_Position[0] == MechanicalArm_EndPosition[0] && MechanicalArm_Position[1] == MechanicalArm_EndPosition[1])
				MechanicalArm_State = 0;
		}else
		{
			for(temp=0;temp<5;temp++)
			{
				if(Target_Width[temp] != StateEnd_Width[temp])
					break;
			}
			if(temp == 4)
				MechanicalArm_State = 0;
		}
	}
}

void MechanicalArm_WidthInc(void)
{
	uint8_t temp;
	for(temp=0;temp<5;temp++)
	{
		if(Target_Width[temp]<StateEnd_Width[temp])
		{
			Target_Width[temp]+= MechanicalArm_Inc[temp];
			if(Target_Width[temp]>StateEnd_Width[temp])
				Target_Width[temp] = StateEnd_Width[temp];
		}else
		{
			Target_Width[temp]-= MechanicalArm_Inc[temp];
			if(Target_Width[temp]<StateEnd_Width[temp])
				Target_Width[temp] = StateEnd_Width[temp];
		}
	}
	MechanicalArm_WidthSet(Target_Width);
}

void MechanicalArm_PositionInc(void)
{
	uint8_t temp;
	for(temp=0;temp<2;temp++)
	{
		if(MechanicalArm_Position[temp] < MechanicalArm_EndPosition[temp])
		{
			MechanicalArm_Position[temp] += MechanicalArm_Speed;
			if(MechanicalArm_Position[temp] > MechanicalArm_EndPosition[temp])
				MechanicalArm_Position[temp] = MechanicalArm_EndPosition[temp];
		}else
		{
			MechanicalArm_Position[temp] -= MechanicalArm_EndPosition[temp];
			if(MechanicalArm_Position[temp] < MechanicalArm_EndPosition[temp])
				MechanicalArm_Position[temp] = MechanicalArm_EndPosition[temp];
		}
	}
	MechanicalArm_PositionSet(MechanicalArm_Position[0],MechanicalArm_Position[1]);
}

void MechanicalArm_PositionLineSet(int slen,int shight,int elen,int ehight,uint8_t speed)
{
	MechanicalArm_State = 1;
	MechanicalArm_Mode = 1;
	MechanicalArm_PositionSet(slen,shight);
	MechanicalArm_EndPosition[0] = elen;
	MechanicalArm_EndPosition[1] = ehight;
	MechanicalArm_Speed = speed;
}

void MechanicalArm_PositionIncSet(int len,int hight,uint8_t*Inc)
{
	double*angle;
	uint8_t temp;
	MechanicalArm_Mode = 0;
	MechanicalArm_State = 1;
	MechanicalArm_Position[0] = len;
	MechanicalArm_Position[1] = hight;
	angle = CosinAngle_Config(len,hight);
	for(temp=0;temp<3;temp++)
	{
		StateEnd_Width[temp+1] = AngleToWidth(*(angle+temp));
		MechanicalArm_Inc[temp+1] = *(Inc+temp+1);
	}
}

void MechanicalArm_PositionSet(int len,int hight)
{	
	uint8_t temp;
	double*angle;
	angle = CosinAngle_Config(len,hight);
	for(temp=0;temp<3;temp++)
		*street_width[temp+1] = StateEnd_Width[temp+1] = Target_Width[temp+1] = AngleToWidth(*(angle+temp));
}

double*CosinAngle_Config(int len,int hight)
{
	uint32_t lc,lc2;
	static double angle[3];
	double a1,a2;
	len -= ArmLen[2];
	if(len!=0)		//防止出现tan90°
	{
		a1 = hight*1.0 / len;
		a1 = atan(a1)*HZJ;
	}
	lc2 = hight*hight + len*len;
	lc = (int)sqrt(lc2);
	angle[1] = (ArmLen2[0]+ArmLen2[1]-lc2) * 1.0 / (2*ArmLen[0]*ArmLen[1]);
	angle[1]  = acos(angle[1] )*HZJ;
	angle[1] = 180 - angle[1];
	a2 = (ArmLen2[0]-ArmLen2[1]+lc2) * 1.0 / (2*ArmLen[0]*lc);
	a2 = acos(a2)*HZJ;
	angle[0] = 90 - a1 - a2;
	angle[2] = 90 -angle[1] - angle[0];
	angle[1] = -angle[1];
	angle[2] = 0;
	return angle;
}

void MechanicalArm_BaceAngleIncSet(double angle,uint8_t Inc)
{
	MechanicalArm_Mode = 0;
	MechanicalArm_State  = 1;
	StateEnd_Width[0] = AngleToWidth(angle);
	MechanicalArm_Inc[0] = Inc;
}

void ClawClr(uint8_t state,uint8_t Inc)
{
	MechanicalArm_Mode = 0;
	MechanicalArm_State = 1;
	StateEnd_Width[4] = Claw_Width[state];
	MechanicalArm_Inc[4] = Inc;
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
