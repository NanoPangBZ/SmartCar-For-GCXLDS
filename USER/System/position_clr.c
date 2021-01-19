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
		uint8_t n;
		for(n=0;n<4;n++)
			PID_Struct[n].pointSet = *(PointSet + n);
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

void PositionClr_Port(void)
{
	PositionState_Updata();
	//根据模式配置基准速度
	if(Position_Mode)
	{
		Speed_Cng[Speed_Base] = 300;
		Speed_Cng[Speed_Max] = 360;
		Speed_Cng[Speed_Min] = 80;
		Speed_Cng[Speed_Cha] = 2;
	}else
	{
		Speed_Cng[Speed_Base] = 80;
		Speed_Cng[Speed_Max] = 100;
		Speed_Cng[Speed_Min] = 50;
		Speed_Cng[Speed_Cha] = 2;
	}
	//制动
	switch(Position_State)
	{
		case 0:
			Position_Clr(X);
			break;
		default:break;
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
				Position_State ++;
			}
			break;
		case 2:
			if(Err_position[X]/10 == 0)
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
				Position_State ++;
			}
			break;
		case 4:break;
		default:break;
	}
}

void Position_Clr(uint8_t Dir)
{
	uint16_t AbsPosition_Speed;
	uint16_t Yaw_CorSpeed;
	if(Position_Speed<0)
		AbsPosition_Speed = Position_Speed;
	else
		AbsPosition_Speed = -Position_Speed;
	//渐进式加速过程
	AbsPosition_Speed += Speed_Cng[Speed_Cha];
	if(AbsPosition_Speed > Speed_Cng[Speed_Base])
		AbsPosition_Speed = Speed_Cng[Speed_Base];
	if(Err_position[Dir] > 0)
		Position_Speed = AbsPosition_Speed;
	else
		Position_Speed = -AbsPosition_Speed;
	//动态航向角修正
	
}

void Yaw_StaticClr(void)
{
	
}

void Position_Reset(long int x,long int y)
{
	Real_position[X] = x;
	Real_position[Y] = y;
}

void Target_RelPosition_Set(long int x,long int y,uint8_t Mode)
{
	Target_position[0] += x;
	Target_position[1] += y;
	Position_Mode = Mode;
}

void PositionClr_Stop(void)
{
	uint8_t temp;
	StopRun();
	for(temp=0;temp<4;temp++)
		Target_position[temp] = Real_position[temp];
	PositionState_Reset();
}

void StopRun(void)
{
	Target_Speed[0] = Target_Speed[1] = Target_Speed[2] = Target_Speed[3] = 0;
	Inc_PID_Set(Target_Speed);
}

void PositionState_Reset(void)
{
	Position_State = 0;
	Position_Mode = QckMode;
}

uint8_t Read_Position_State(void)
{
	return Position_State;
}

void Target_Position_Set(long int x,long int y,uint8_t Mode)
{
	Target_position[X] = x;
	Target_position[Y] = y;
	Position_Mode = QckMode;
}

void Real_Position_Update(void)
{
	long int*distance;
	distance = Read_Distance();
	Real_position[0] += (*distance + *(distance + 1)  + *(distance +2 ) + *(distance + 3)) /4;
	Real_position[1] += (*distance - *(distance + 1 ) - *(distance + 2) + *(distance + 3))/4;
	Disitance_clear();
}


