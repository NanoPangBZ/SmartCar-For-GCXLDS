#include "attitude_app.h"

void attitude_app_Task(void)
{
	if(attitude_flag)
		attitudeRun();
}


void FindQrCode_AttitudeTask(void)
{
	double angle_list[4] = {-90.0,60.0,-90.0,62.0};
	uint8_t Inc[4] = {2,2,2,3};
	uint8_t temp;
	if(attitude_state==0)
	{
		for(temp=0;temp<4;temp++)
			TargetWidth_Set(AngleToWidth(angle_list[temp]),Inc[temp],temp);
		attitude_state++;
	}else if(attitude_state == 1)
	{
		if(Read_MechanicalArmState() == 0)
		{
			attitude_state = 0;
			attitude_flag = 0;
		}
	}
}

void FindUpBlob_AttitudeTask(void)
{
	double angle_list[4] = {-90.0,-70.0,-90.0,-80.0};
	uint8_t Inc[4] = {4,7,7,7};
	uint8_t temp;
	if(attitude_state==0)
	{
		for(temp=0;temp<4;temp++)
		{
			TargetWidth_Set(AngleToWidth(angle_list[temp]),Inc[temp],temp);
		}
		attitude_state++;
	}else if(attitude_state == 1)
	{
		if(Read_MechanicalArmState() == 0)
		{
			attitude_state = 0;
			attitude_flag = 0;
		}
	}
}

void GetYL_UpBlosTask(void)
{
	double Read_Angle[4] = {-90.0,-25.0,-90.0,15.0};
	uint8_t Read_Inc[4] = {2,4,6,6};
	double Adjust_Angle[4] = {-90.0,18.0,-90.0,18.0};
	uint8_t Adjust_Inc[4] = {2,4,6,6};
	uint8_t temp;
	if(attitude_state == 0)
	{
		for(temp=0;temp<4;temp++)
			TargetWidth_Set(AngleToWidth(Read_Angle[temp]),Read_Inc[temp],temp);
		attitude_state++;
	}else if(attitude_state == 1)
	{
		if(Read_MechanicalArmState() == 0)
		{
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(Adjust_Angle[temp]),Adjust_Inc[temp],temp);
			attitude_state++;
		}
	}else if(attitude_state == 2)
	{
		if(Read_MechanicalArmState() == 0)
		{
			ClawClr(2,3);
			attitude_state++;
		}
	}else if(attitude_state == 3)
	{
		if(Read_MechanicalArmState() == 0)
		{
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(Read_Angle[temp]),Read_Inc[temp],temp);
			attitude_state++;
		}
	}else if(attitude_state == 4)
	{
		if(Read_MechanicalArmState() == 0)
		{
			attitude_flag = 0;
			attitude_state = 0;
		}
	}
}

void FindLine_NAttitudeTask(void)
{
	uint8_t temp;
	double AngleList[4] = {0.0,-30.0,-90.0,-90.0};
	uint8_t Inc[4] = {2,2,2,3};
	if(attitude_state == 0)
	{
		for(temp=0;temp<4;temp++)
			TargetWidth_Set(AngleToWidth(AngleList[temp]),Inc[temp],temp);
		attitude_state++;
	}else if(attitude_state == 1)
	{
		if(Read_MechanicalArmState() == 0)
		{
			attitude_state = 0;
			attitude_flag = 0;
		}
	}
}

void PutBC_AttitudeTask(void)
{
	double Ready_List[4] = {0.0,0.0,-70.0,-50.0};
	uint8_t Ready_Inc[4] = {7,4,4,4};
	double Adjust_List[4] = {0.0,90.0,-80.0,70.0};
	uint8_t Adjust_Inc[4] = {7,4,4,8};
	double GoBack_List[4] = {0.0,60.0,-90.0,72.0};
	uint8_t GoBack_Inc[4] = {7,4,4,4};
	uint8_t temp;
	if(attitude_state == 0)
	{
		for(temp=0;temp<4;temp++)
			TargetWidth_Set(AngleToWidth(Ready_List[temp]),Ready_Inc[temp],temp);
		attitude_state++;
	}else if(attitude_state == 1)
	{
		if(Read_MechanicalArmState() == 0)
		{
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(Adjust_List[temp]),Adjust_Inc[temp],temp);
			attitude_state++;
		}
	}else if(attitude_state == 2)
	{
		if(Read_MechanicalArmState() == 0)
		{
			ClawClr(0,2);
			attitude_state++;
		}
	}else if(attitude_state == 3)
	{
		if(Read_MechanicalArmState() == 0)
		{
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(GoBack_List[temp]),GoBack_Inc[temp],temp);
			attitude_state++;
		}
	}else if(attitude_state == 4)
	{
		if(Read_MechanicalArmState() == 0)
		{
			attitude_state = 0;
			attitude_flag = 0;
		}
	}
}

/****************对外接口**************/

void PutBlob_Attituede(uint8_t Pos)
{
	attitude_flag = 1;
	attitudeRun = PutBC_AttitudeTask;
}

void FindLine_Attitude(uint8_t Pos)
{
	attitude_flag = 1;
	if(Pos)
	{
		attitudeRun = FindLine_NAttitudeTask;
	}else
	{
		attitudeRun = FindLine_NAttitudeTask;
	}
}

void GetBlob(uint8_t Pos)
{
	attitude_flag = 1;
	if(Pos)
	{
		attitudeRun = GetYL_UpBlosTask;
	}else
	{
		attitudeRun = GetYL_UpBlosTask;
	}
}

void FindUpBlob_Attitude(void)
{
	attitude_flag = 1;
	attitudeRun = FindUpBlob_AttitudeTask;
}

void FindQrCode_Attitude(void)
{
	attitude_flag = 1;
	attitudeRun = FindQrCode_AttitudeTask;
}

uint8_t Read_AttitudeFlag(void)
{
	return attitude_flag;
}

uint8_t Read_AttitudeState(void)
{
	return attitude_state;
}

