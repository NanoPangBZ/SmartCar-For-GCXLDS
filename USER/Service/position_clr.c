#include "position_clr.h"

void PositionClr_Port(void)
{
	PositionState_Updata();
	
}

void PositionState_Updata(void)
{
	Real_Position_Update();
	Err_position[X] = Target_position[X] - Real_position[X] ;
	Err_position[Y] = Target_position[Y] - Real_position[Y];
	Err_Yaw = Gyroscope_ReadYaw();
	switch(Position_State)
	{
		case 0:
			if(Err_position[X]/10 == 0)
			{
				StopRun();
				Position_State++;
			}
			break;
		case 1:
			if(Err_Yaw/10 == 0)
			{
				StopRun();
				Position_State ++;
			}
			break;
		case 2:
			if(Err_position[X]/10 == 0)
			{
				StopRun();
				Position_State++;
			}
			break;
		case 3:
			if(Err_Yaw/10 == 0)
			{
				StopRun();
				Position_State ++;
			}
			break;
		case 4:break;
		default:break;
	}
}

void Position_Clr(uint8_t Dir)
{
	uint16_t AbsPosition_Speed;		//上一次目标速度绝对值
	uint16_t UnPosition_Speed;		//最终目标速度绝对值
	//AbsPosition_Speed绝对值赋值
	if(Position_Speed>0)
		AbsPosition_Speed = Position_Speed;
	else
		AbsPosition_Speed = -Position_Speed;
	//根据距离配置最终目标速度
	if(Err_position[Dir]>Speed_Cng[Speed_Base] || Err_position[Dir]<-Speed_Cng[Dir])
	{
		UnPosition_Speed = Speed_Cng[Speed_Base];
	}else
	{
		if(Err_position[Dir]>0)
			UnPosition_Speed = Err_position[Dir];
		else
			UnPosition_Speed = -Err_position[Dir];
	}
	//向最终速度叠加
	if(AbsPosition_Speed + Speed_Cng[Speed_Cha]> UnPosition_Speed || AbsPosition_Speed > UnPosition_Speed)
		AbsPosition_Speed = UnPosition_Speed;
	else
		AbsPosition_Speed+=Speed_Cng[Speed_Cha];
	if(Err_position[Dir]>0)
		Position_Speed = AbsPosition_Speed;
	else
		Position_Speed = -AbsPosition_Speed;
}

void Yaw_Clr(void)
{
	uint16_t AbsYaw_Speed;
	uint16_t UnYaw_Speed;
	if(Yaw_Speed>0)
		AbsYaw_Speed = Yaw_Speed;
	else
		AbsYaw_Speed = -UnYaw_Speed;
	if(Err_Yaw>0)
		UnYaw_Speed = Err_Yaw;
	else
		UnYaw_Speed = -Err_Yaw;
	if(AbsYaw_Speed + Speed_Cng[Speed_Cha] > UnYaw_Speed || AbsYaw_Speed > UnYaw_Speed)
		AbsYaw_Speed = UnYaw_Speed;
	else
		AbsYaw_Speed+=Speed_Cng[Speed_Cha];
	if(Err_Yaw>0)
		Yaw_Speed = UnYaw_Speed;
	else
		Yaw_Speed = -UnYaw_Speed;
}

void Yaw_StaticClr(void)
{
	
}

void PositionMode_Set(uint8_t Mode)
{
	
}

void Real_Position_Set(long int x,long int y)
{
	StopRun();
	Real_position[X] = x;
	Real_position[Y] = y;
	Position_State = 0;
}

void PositionClr_Stop(void)
{
	uint8_t temp;
	StopRun();
	for(temp=0;temp<4;temp++)
		Target_position[temp] = Real_position[temp];
	Position_State = 3;
}

void Target_Position_Set(long int x,long int y,uint8_t Mode)
{
	Target_position[X] = x;
	Target_position[Y] = y;
	PositionMode_Set(Mode);
	Position_State = 0;
}

void Target_RelPosition_Set(long int x,long int y,uint8_t Mode)
{
	Target_position[0] += x;
	Target_position[1] += y;
	PositionMode_Set(Mode);
	Position_State = 0;
}

uint8_t Read_Position_State(void)
{
	return Position_State;
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
		static int PWM[4];
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

void Inc_PID_Set(int*PointSet)
{
		uint8_t n;
		for(n=0;n<4;n++)
			PID_Struct[n].pointSet = *(PointSet + n);
		Inc_PID_Realiz();
}

void StopRun(void)
{
	Position_Speed = 0;
	Yaw_Speed = 0;
	Target_Speed[0] = Target_Speed[1] = Target_Speed[2] = Target_Speed[3] = 0;
	Inc_PID_Set(Target_Speed);
}

void Real_Position_Update(void)
{
	long int*distance;
	distance = Read_Distance();
	Real_position[0] += (*distance + *(distance + 1)  + *(distance +2 ) + *(distance + 3)) /4;
	Real_position[1] += (*distance - *(distance + 1 ) - *(distance + 2) + *(distance + 3))/4;
	Disitance_clear();
}


