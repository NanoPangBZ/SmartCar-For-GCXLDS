#include "MechanicalArm_Service.h"
#include "street_motor.h"
#include <math.h>

void MechanicalArm_Service(void)
{
	MechanicalArm_StateCheck();
	if(MechanicalArm_State)
	{
		if(MechanicalArm_Mode)
			MechanicalArm_PositionInc();
		else
			MechanicalArm_WidthInc();
	}
}

void MechanicalArm_StateCheck(void)
{
	uint8_t temp;
	uint8_t flag = 0;
	if(MechanicalArm_State)
	{
		if(MechanicalArm_Mode)
		{
			for(temp=0;temp<2;temp++)
			{
				if(MechanicalArm_Position[temp] != MechanicalArm_TargetPosition[temp])
					flag = 1;
			}
		}else
		{
			for(temp=0;temp<5;temp++)
			{
				if(Target_Width[temp] != *street_width[temp])
					flag =1;
			}
		}
		if(flag!=1)
			MechanicalArm_State = 0;
	}
}

void MechanicalArm_WidthInc(void)
{
	uint8_t temp;
	for(temp = 0;temp<5;temp++)
	{
		if(*street_width[temp]<Target_Width[temp])
		{
			*street_width[temp] += MechanicalArm_Inc[temp];
			if(*street_width[temp] > Target_Width[temp])
				*street_width[temp] = Target_Width[temp];
		}else
		{
			*street_width[temp] -= MechanicalArm_Inc[temp];
			if(*street_width[temp] < Target_Width[temp])
				*street_width[temp] = Target_Width[temp];
		}
	}
}

uint8_t Read_MechanicalArmState(void)
{
	return MechanicalArm_State;
}

void MechanicalArm_PositionInc(void)
{
	static uint8_t cycle = 0;
	uint8_t temp;
	cycle++;
	if(cycle > 5)
	{
		for(temp = 0;temp<2;temp++)
		{
			if(MechanicalArm_Position[temp] < MechanicalArm_TargetPosition[temp])
				MechanicalArm_Position[temp] ++;
			else if(MechanicalArm_Position[temp] != MechanicalArm_TargetPosition[temp])
				MechanicalArm_Position[temp]--;
		}
		MechanicalArm_PositionSet(MechanicalArm_Position[0],MechanicalArm_Position[1]);
		cycle = 0;
	}
}

uint16_t AngleToWidth(double angle)
{
	uint16_t temp;
	temp = (uint16_t)(Width_Benchmark+(int)(angle*Width_Unit));
	return temp;
}

void MechanicalArm_PostionLineSet(int slen,int shight,int elen,int ehight)
{
	MechanicalArm_State = 1;
	MechanicalArm_Mode = 1;
	MechanicalArm_TargetPosition[0] = elen;
	MechanicalArm_TargetPosition[1] = ehight;
	MechanicalArm_PositionSet(slen,shight);
}

void MechanicalArm_PositionSet(int len,int hight)
{
	uint8_t temp;
	double*angle;
	angle = Cosin_AngleConfig(len,hight);
	MechanicalArm_Position[0] = len;
	MechanicalArm_Position[1] = hight;
	for(temp=0;temp<3;temp++)
	{
		*street_width[temp+1] = AngleToWidth(*(angle+temp));
	}
}

double*Cosin_AngleConfig(int len,int hight)
{
	static double Angle[3] = {0,0,0};
	double a1,a2;
	uint32_t l2,l;
	len -= ArmLen[2];
	hight -= 20;
	l2 = (hight*hight) + (len*len);
	l = sqrt((double)l2);
	if(len!=0)
	{
		a1 = (hight*1.0)/(len*1.0);		//计算tan值
		a1 = atan(a1)*HZJ;				//求a1角度
	}else
	{
		a1 = 90.0;
	}
	a2 = ((l2+ArmLen2[0]-ArmLen2[1])*1.0) / ( (2*l*ArmLen[0])*1.0);	//计算a2 cos值
	a2 = acos(a2)*HZJ;		//求a2角度
	Angle[0] = 90 -a1 -a1;		//计算舵机1的前倾角
	AngleCheck(&Angle[0]);
	Angle[1] = ((ArmLen2[1]+ArmLen2[0]-l2)*1.0) / ((2*ArmLen[1]*ArmLen[0])*1.0);
	Angle[1] = acos(Angle[1])*HZJ;
	Angle[1] = 180 - Angle[1];
	AngleCheck(&Angle[1]);
	Angle[2] = 90 - Angle[0] - Angle[1];
	AngleCheck(&Angle[2]);
	Angle[1] = -Angle[1];
	Angle[2] = -Angle[2];
	return Angle;
}

void AngleCheck(double*angle)
{
	if(*angle>90.0)
		*angle = 90.0;
	if(*angle<-90.0)
		*angle = -90.0;
}

void TargetWidth_Set(uint16_t width,uint8_t inc,uint8_t num)
{
	MechanicalArm_Mode = 0;
	MechanicalArm_State = 1;
	Target_Width[num] = width;
	MechanicalArm_Inc[num] = inc;
}

void ClawClr(uint8_t state,uint8_t Inc)
{
	MechanicalArm_Mode = 0;
	MechanicalArm_State = 1;
	Target_Width[4] = Claw_Width[state];
	MechanicalArm_Inc[4] = Inc;
}

void MechanicalArm_Reset(void)
{
	uint8_t temp;
	for(temp=0;temp<5;temp++)
		*street_width[temp] = Reset_Width[temp];
}
