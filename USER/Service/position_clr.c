#include "position_clr.h"

void PositionClr_Service(void)
{
	Position_Update();
	Speed_Config();
	Inc_PID_Realiz();
}

void Speed_Config(void)
{
	
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
		Inc_PID_Realiz();
}

void Position_Update(void)
{
	long int*distance;
	Err_Yaw = Gyroscope_ReadYaw();
	distance = Read_Distance();
	position[0] += (*distance + *(distance + 1)  + *(distance +2 ) + *(distance + 3)) /4;
	position[1] += (*distance - *(distance + 1 ) - *(distance + 2) + *(distance + 3))/4;
	Disitance_clear();
}


