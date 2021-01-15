#include "position_clr.h"

float Inc_PID(float Input , PID_TypeDef* PID)
{
		float Inc;
		PID->Err2 = PID->Err1;
		PID->Err1 = PID->Err;
		PID->Err = PID->pointSet - Input;
		Inc = SpeedKp*(PID->Err - PID->Err1) + SpeedTi*PID->Err + SpeedTd*(PID->Err - 2*PID->Err1 + PID->Err2);
		return Inc;
}

void Inc_PID_Set(int*PointSet)
{
//		int*Speed;
		uint8_t n;
//		Speed  = Read_Speed();
		for(n=0;n<4;n++)
		{
//			PID_Struct[n].Err = PID_Struct[n].Err1 = PID_Struct[n].Err2 = (float)(*(Speed + n) - *(PointSet + n));
			PID_Struct[n].pointSet = *(PointSet + n);
		}
		Inc_PID_Realiz();
}

void Inc_PID_Realiz(void)
{
		static int PWM[4];
		uint8_t n;
		int*Speed;
		Speed = Read_Speed();
		for(n=0;n<4;n++)
		{
			DataScope_Get_Channel_Data((float)*(Speed+n),n+1);
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
//	Usart1_Send(DataScope_OutPut_Buffer,DataScope_Data_Generate(4));
}

void Clr_Port(void)
{
	PositionState_Updata();
	switch(Position_State)
	{
		case 0:
			Position_Clr(X);
			break;
		case 1:
			Yaw_StaticClr();
			break;
		case 2:
			Position_Clr(Y);
			break;
		case 3:
			Yaw_StaticClr();
			break;
	}
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
				Position_Speed = 0;
				Position_State++;
			}
			break;
		case 1:
			if(Err_Yaw/10 == 0)
			{
				StopRun();
				Yaw_Speed = 0;
				Position_State++;
			}
			break;
		case 2:
			if(Err_position[Y]/10 == 0)
			{
				StopRun();
				Position_Speed = 0;
				Position_State++;
			}
			break;
		case 3:
			if(Err_Yaw/10 == 0)
			{
				StopRun();
				Yaw_Speed = 0;
				Position_State++;
			}
			break;
	}
}

void Position_Clr(uint8_t Dir)
{
	int UnSpeed,UnYawSpeed;
	if(Err_position[Dir] > 0xffffffff)
		UnSpeed = 0xffffffff;
	else
		UnSpeed = Err_position[Dir];
	if(UnSpeed < 0)
		UnSpeed = -UnSpeed;
	if(UnSpeed > Speed_Max)
		UnSpeed = Speed_Max;
	if(Position_Speed < UnSpeed)
	{
		Position_Speed++;
	}
	else
	{
		if(UnSpeed < Speed_Stop)
			Position_Speed = Speed_Stop;
		else
			Position_Speed=UnSpeed ;
	}
	if(Dir == X)
	{
		if(Err_position[Dir] > 0)
			Target_Speed[0] = Target_Speed[1] = Target_Speed[2] = Target_Speed[3] = Position_Speed;
		else
			Target_Speed[0] = Target_Speed[1] = Target_Speed[2] = Target_Speed[3] = -Position_Speed;
	}else
	{
		if(Err_position[Dir] > 0)
		{
			Target_Speed[0] = Target_Speed[3] = Position_Speed;
			Target_Speed[1] = Target_Speed[2] = -Position_Speed;
		}else
		{
			Target_Speed[0] = Target_Speed[3] = -Position_Speed;
			Target_Speed[1] = Target_Speed[2] = Position_Speed;
		}
	}
	UnYawSpeed = (Err_Yaw/5)*15;
	if(UnSpeed > YawSpeed_Max)
		UnSpeed = YawSpeed_Max;
	if(UnSpeed < -YawSpeed_Max)
		UnSpeed = -YawSpeed_Max;
	if(UnYawSpeed > 0)
	{
		if(Yaw_Speed < UnYawSpeed)
			Yaw_Speed++;
		else
			Yaw_Speed = UnYawSpeed;
	}else
	{
		if(Yaw_Speed > UnYawSpeed)
			Yaw_Speed--;
		else
			Yaw_Speed = UnYawSpeed;
	}
	Target_Speed[0] += Yaw_Speed;
	Target_Speed[1] -= Yaw_Speed;
	Target_Speed[2] += Yaw_Speed;
	Target_Speed[3] -= Yaw_Speed;
	Inc_PID_Set(Target_Speed);
}

void Yaw_StaticClr(void)
{
	int StaticYaw;
	StaticYaw = Gyroscope_ReadYaw();
	if(StaticYaw/10 != 0)
		StaticYaw /= 2;
	else
		StaticYaw = 0;
	if(StaticYaw != 0)
	{
		if(StaticYaw > 0)
			StaticYaw += 50;
		else
			StaticYaw -= 50;
	}
	if(StaticYaw > 320)
		StaticYaw = 320;
	if(Yaw_Speed<-320)
		StaticYaw = -320;
	Target_Speed[0] = Target_Speed[2] = StaticYaw;
	Target_Speed[1] = Target_Speed[3] = -StaticYaw;
	Inc_PID_Set(Target_Speed);
}

void StopRun(void)
{
	Target_Speed[0] = Target_Speed[1] = Target_Speed[2] = Target_Speed[3] = 0;
	Inc_PID_Set(Target_Speed);
}

void PositionState_Reset(void)
{
	Position_State = 0;
}

uint8_t Read_Position_State(void)
{
	return Position_State;
}

void Target_Position_Set(long int x,long int y)
{
	Target_position[X] = x;
	Target_position[Y] = y;
}

void Real_Position_Update(void)
{
	long int*distance;
	distance = Read_Distance();
	Real_position[0] += (*distance + *(distance + 1)  + *(distance +2 ) + *(distance + 3)) /4;
	Real_position[1] += (*distance - *(distance + 1 ) - *(distance + 2) + *(distance + 3))/4;
	Disitance_clear();
}


