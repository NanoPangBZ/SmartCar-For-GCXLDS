#include "position_clr.h"

void PositionClr_Service(void)
{
	Position_Update();
	if(Position_Mode)
	{
		
	}else
	{
		
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
	Position_State= 1;
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
	Position_State = 4;
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


