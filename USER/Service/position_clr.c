#include "position_clr.h"

void PositionClr_Service(void)
{
	Position_Update();				//位置,航向角更新
	if(Position_Mode)
	{
		PositionState_Updata();		//自动控制下的进度更新
		if(Position_State == 1 || Position_State == 3)
			PositionSpeed_Config(Position_State/2);
	}
	YawSpeed_Config();			//旋转速度配置
	Speed_Syn();					//合成位移和旋转的速度
	Speed_Set(Target_Speed);		//将合成的速度载入PID结构体
	Inc_PID_Realiz();				//PID实现;
}

void PositionSpeed_Config(uint8_t Dir)
{
	int Abs_Speed = Target_Speed[0];
	int Un_Speed;
	//取上一次速度绝对值
	if(Abs_Speed < 0)
		Abs_Speed = -Abs_Speed;
	//根据距离配置速度
	if(Err_Position[Dir] > Speed_Base || Err_Position[Dir] < -Speed_Base)
		Un_Speed = Speed_Base;
	else
		Un_Speed = Err_Position[Dir];
	if(Un_Speed<0)
		Un_Speed = -Un_Speed;
	//变速过程
	Abs_Speed+=Speed_Cha;
	if(Abs_Speed > Un_Speed)
		Abs_Speed = Un_Speed;
	//配置轮子速度
	if(Err_Position[Dir] <0)
		Abs_Speed = -Abs_Speed;
	if(Dir)
	{
		Position_Speed[3] = Position_Speed[0] = Abs_Speed;
		Position_Speed[1] = Position_Speed[2] = -Abs_Speed;
	}else
	{
		Position_Speed[1] = Position_Speed[2] = Position_Speed[3] = Position_Speed[0] = Abs_Speed;
	}
}

void Speed_Syn(void)
{
	uint8_t temp;
	int AbsTemp;
	for(temp=0;temp<4;temp++)
	{
		Target_Speed[temp]  = AbsTemp = Position_Speed[temp] + Yaw_Speed[temp];
		if(AbsTemp<0)
			AbsTemp = -AbsTemp;
		if(AbsTemp > Speed_Max)
		{
			if(Target_Speed[temp]>0)
				Target_Speed[temp] = Speed_Max;
			else
				Target_Speed[temp] = -Speed_Max;
		}
		if(AbsTemp < Speed_Min && AbsTemp!=0)
		{
			if(Target_Speed[temp]>0)
				Target_Speed[temp] = Speed_Min;
			else
				Target_Speed[temp] = -Speed_Min;
		}
	}
}

void YawSpeed_Config(void)
{
	int temp = Err_Yaw;
	if(Position_State == 1 || Position_State == 3)
	{
		Yaw_Speed[0] = temp;
		Yaw_Speed[1] = -temp;
		Yaw_Speed[2] = temp;
		Yaw_Speed[3] = -temp;
	}else
	{
		if(Err_Yaw/10!=0)
		{
			Yaw_Speed[0] = temp;
			Yaw_Speed[1] = -temp;
			Yaw_Speed[2] = temp;
			Yaw_Speed[3] = -temp;
		}else
		{
			Position_Stop();
		}
	}
}

void PositionState_Updata(void)
{
	switch(Position_State)
	{
		case 0:
			if(Err_Yaw/10==0)
				PositionState_Inc();
			break;
		case 1:
			if(Err_Position[X]/10==0)
				PositionState_Inc();
			break;
		case 2:
			if(Err_Yaw/10==0)
				PositionState_Inc();
			break;
		case 3:
			if(Err_Position[Y]/10==0)
				PositionState_Inc();
			break;
		case 4:
			if(Err_Yaw/10==0)
				PositionState_Inc();
			break;
	}
}

void PositionState_Inc(void)
{
	Position_Stop();
	Position_State++;
}

void PositionService_Stop(void)
{
	Position_Stop();
	Position_State = 5;
	Position_Mode = 0;
}

void Position_Stop(void)
{
	uint8_t temp;
	for(temp=0;temp<4;temp++)
	{
		Target_Speed[temp] = 0;
		Yaw_Speed[temp] = 0;
		Position_Speed[temp]=0;
	}
}

void TargetMove_Set(long int x,long int y, uint8_t PosMode)
{
	Target_Position[0] = x;
	Target_Position[1] = y;
	if(PosMode)
	{
		Target_Position[0] += position[0];
		Target_Position[1] += position[1];
	}
	Position_State= 0;
	Position_Mode = 1;
}

void Move_Set(uint8_t Dir,int Speed)
{
	if(Dir)
	{
		Position_Speed[0] = Position_Speed[3] = Speed;
		Position_Speed[1] = Position_Speed[2] = -Speed;
	}else
	{
		Position_Speed[0] = Speed;
		Position_Speed[1] = Speed;
		Position_Speed[2] = Speed;
		Position_Speed[3] = Speed;
	}
	Position_State = 6;
	Position_Mode = 0;
}

uint8_t Read_PositionState(void)
{
	return Position_State;
}

long int*Read_Position(void)
{
	return position;
}

float Inc_PID(float Input , PID_TypeDef* PID)
{
		float Inc;
		PID->Err2 = PID->Err1;
		PID->Err1 = PID->Err;
		PID->Err = PID->pointSet - Input;
		Inc = SpeedKp*(PID->Err - PID->Err1) + SpeedTi*PID->Err + SpeedTd*(PID->Err - 2*PID->Err1 + PID->Err2);
		return Inc;
}

void Inc_PID_Realiz(void)
{
		uint8_t n;
		int*Speed;
		Speed = Read_Speed();
		for(n=0;n<4;n++)
		{
			if(PID_Struct[n].pointSet != 0)
			{
				PWM[n] += (int)Inc_PID((float)*(Speed+n),&PID_Struct[n]);
				if(PWM[n] >7000)
					PWM[n] = 7000;
				if(PWM[n] < -7000)
					PWM[n] = -7000;
			}else
			{
				PWM[n] = 0;
			}
		}
		PWM_Out(PWM);
}

void Speed_Set(int*PointSet)
{
		uint8_t n;
		for(n=0;n<4;n++)
			PID_Struct[n].pointSet = *(PointSet + n);
}

void Position_Update(void)
{
	long int*distance;
	Err_Yaw = Gyroscope_ReadYaw();
	distance = Read_Distance();
	position[0] += (*distance + *(distance + 1)  + *(distance +2 ) + *(distance + 3)) /4;
	position[1] += (*distance - *(distance + 1 ) - *(distance + 2) + *(distance + 3))/4;
	Err_Position[0] = Target_Position[0] - position[0];
	Err_Position[1] = Target_Position[1] - position[1];
	Disitance_clear();
}


