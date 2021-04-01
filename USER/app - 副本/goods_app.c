#include "goods_app.h"
#include "angle_list.h"

void goods_app_Task(void)
{
	if(Goods_State)
	{
		switch(Goods_Line)
		{
			case 0:
				Attitude_Adjust();
				break;
			case 1:
				Goods_Line1();
				break;
			case 2:
				Goods_Line2();
				break;
			case 3:
				Goods_Line3();
				break;
			case 4:
				Goods_Line4();
				break;
			case 5:
				Goods_Line5();
				break;
			case 6:
				Goods_Line6();
				break;
		}
	}
}

void Goods_Line1(void)
{
	static uint8_t flag = 0;
	uint8_t temp;
	if(flag == 0)
	{
		for(temp=0;temp<4;temp++)
			TargetWidth_Set(AngleToWidth(GetBlob_Ready[0][temp]),Attitude_Inc[0][temp],temp);
		flag++;
	}else if(flag == 1)
	{
		if(Read_MechanicalArmState() == 0)
		{
			flag++;
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(GetBlob_Adjust[0][temp]),Attitude_Inc[0][temp],temp);
		}
	}else if(flag == 2)
	{
		if(Read_MechanicalArmState() == 0)
		{
			flag++;
			ClawClr(2,2);
		}
	}else if(flag == 3)
	{
		if(Read_MechanicalArmState() == 0)
		{
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(GetBlob_Ready[0][temp]),Attitude_Inc[0][temp],temp);
			flag++;
		}
	}else if(flag == 4)
	{
		if(Read_MechanicalArmState() == 0)
		{
			flag = 0;
			Goods_State = 0;
		}
	}
}

void Goods_Line2(void)
{
	static uint8_t flag = 0;
	uint8_t temp;
	if(flag == 0)
	{
		for(temp=0;temp<4;temp++)
			TargetWidth_Set(AngleToWidth(GetBlob_Ready[1][temp]),GetBlob_Ready[1][temp],temp);
		flag++;
	}else if(flag == 1)
	{
		if(Read_MechanicalArmState() == 0)
		{
			flag++;
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(GetBlob_Adjust[1][temp]),GetBlob_Adjust[1][temp],temp);
		}
	}else if(flag == 2)
	{
		if(Read_MechanicalArmState() == 0)
		{
			flag++;
			ClawClr(2,2);
		}
	}else if(flag == 3)
	{
		if(Read_MechanicalArmState() == 0)
		{
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(GetBlob_Ready[1][temp]),GetBlob_Ready[1][temp],temp);
			flag++;
		}
	}else if(flag == 4)
	{
		if(Read_MechanicalArmState() == 0)
		{
			flag = 0;
			Goods_State = 0;
		}
	}
}

void Goods_Line3(void)
{
	static uint8_t flag = 0;
	uint8_t temp;
	if(flag == 0)
	{
		for(temp=0;temp<4;temp++)
			TargetWidth_Set(AngleToWidth(GetBlob_Ready[2][temp]),GetBlob_Ready[2][temp],temp);
		flag++;
	}else if(flag == 1)
	{
		if(Read_MechanicalArmState() == 0)
		{
			flag++;
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(GetBlob_Adjust[1][temp]),GetBlob_Adjust[1][temp],temp);
		}
	}else if(flag == 2)
	{
		if(Read_MechanicalArmState() == 0)
		{
			flag++;
			ClawClr(2,2);
		}
	}else if(flag == 3)
	{
		if(Read_MechanicalArmState() == 0)
		{
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(GetBlob_Ready[1][temp]),GetBlob_Ready[1][temp],temp);
			flag++;
		}
	}else if(flag == 4)
	{
		if(Read_MechanicalArmState() == 0)
		{
			flag = 0;
			Goods_State = 0;
		}
	}
}
	
void Goods_Line4(void)
{
	static uint8_t flag = 0;
	uint8_t temp;
	if(flag == 0)
	{
		for(temp=0;temp<4;temp++)
			TargetWidth_Set(AngleToWidth(PutBlob_Ready[0][temp]),PutBlob_Readytnc[0][temp],temp);
		flag++;
	}else if(flag == 1)
	{
		if(Read_MechanicalArmState() == 0)
		{
			flag++;
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(PutBlob_Adjust[0][temp]),PutBlob_Adjustnc[0][temp],temp);
		}
	}else if(flag == 2)
	{
		if(Read_MechanicalArmState() == 0)
		{
			flag++;
			ClawClr(0,2);
		}
	}else if(flag == 3)
	{
		if(Read_MechanicalArmState() == 0)
		{
			for(temp=0;temp<4;temp++)
				TargetWidth_Set(AngleToWidth(PutBlob_GoBack[0][temp]),PutBlob_GoBackInc[0][temp],temp);
			flag++;
		}
	}else if(flag == 4)
	{
		if(Read_MechanicalArmState() == 0)
		{
			flag = 0;
			Goods_State = 0;
		}
	}
}

void Goods_Line5(void)
{}

void Goods_Line6(void)
{}
	
void Attitude_Adjust(void)
{
	static uint8_t flag = 0;
	uint8_t temp;
	if(flag==0)
	{
		for(temp=0;temp<4;temp++)
			TargetWidth_Set(AngleToWidth(Attitude_Angle[Target_Attitude][temp]),Attitude_Inc[Target_Attitude][temp],temp);
		flag = 1;
	}else
	{
		if(Read_MechanicalArmState()==0)
		{
			flag = 0;
			Goods_State = 0;
		}
	}
}


uint8_t Read_GoodsAppState(void)
{
	return Goods_State;
}

void Goods_Cmd(uint8_t Line)
{
	Goods_State  = 1;
	Goods_Line = Line;
}

void Attitude_Set(uint8_t attitude)
{
	Goods_State = 1;
	Goods_Line = 0;
	Target_Attitude = attitude;
}
