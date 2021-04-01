#include "main_app.h"

void main_app_Task(void)
{
	if(main_app_flag == 0)
	{
		main_app_flag = 1;
		main_app_state++;
		OLED_ShowNum(main_app_state,5,0,1);
	}else
	{
		switch(main_app_state)
		{
			case 1:
				Find_QrCode();
				break;
			case 2:
				Find_Blobs();
				break;
			case 3:
				Get_YLBlobs();
				break;
			case 4:
				Put_BCBlobs();
				break;
		}
	}
}

void Put_BCBlobs(void)
{
	static uint8_t state = 0;
	uint8_t*TempAddr;
	uint8_t temp;
	if(state == 0)
	{
		state = 1;
		MoveCmd_Set(4);	//去半成品区
		Attitude_Set(5);
		OpenMV_Set(3);
	}else if(state == 1)
	{
		if(Read_MoveState()==0 && Read_GoodsAppState()==0)
		{
			Goods_Cmd(4);
			OpenMV_Set(2);
			state++;
		}
	}else if(state == 2)
	{
		if(Read_MoveState()==0 && Read_GoodsAppState()==0)
		{
			TempAddr = Read_QrCode();
			for(temp=0;temp<3;temp++)
			{
				if(*(TempAddr+temp)<20)
					break;
			}
			if(temp!=3)
			{
				state++;
				MoveCmd_Set(5);	//返回原料区
				OpenMV_Set(2);
				Attitude_Set(2);
			}else
			{
				state = 0;
				main_app_flag = 0;
			}
		}
	}
//	}else if(state == 3)
//	{
//		if(Read_MoveState()==0 && Read_GoodsAppState()==0)
//		{
//			Goods_Cmd(1);
//			state++;
//		}
//	}else if(state == 4)
//	{
//		if(Read_MoveState()==0 && Read_GoodsAppState()==0)
//			state=0;
//	}
}

void Get_YLBlobs(void)
{
	static uint8_t state = 0;
	if(state == 0)
	{
		state = 1;
		MoveCmd_Set(3);
		Attitude_Set(2);
	}else if(state == 1)
	{
		if(Read_MoveState()==0 && Read_GoodsAppState()==0)
		{
			Goods_Cmd(1);
			state++;
		}
	}else if(state == 2)
	{
		if(Read_GoodsAppState() == 0)
		{
			state = 0;
			main_app_flag = 0;
		}
	}
}

void Find_Blobs(void)
{
	static uint8_t state = 0;
	uint8_t temp;
	OpenMV_Set(2);
	if(state == 0)
	{
		state++;
		MoveCmd_Set(2);
		Attitude_Set(2);
	}else if(state == 1)
	{
		if(Read_GoodsAppState()==0 && Read_MoveState()==0 )
		{
			Goods_Cmd(1);
			state++;
		}
	}else if(state == 2)
	{
		if(Read_GoodsAppState() == 0)
		{
			state = 0;
			main_app_flag = 1;
			main_app_state = 4;
		}
	}
}

void Find_QrCode(void)
{
	static uint8_t state = 0;
	if(state == 0)
	{
		state++;
		MoveCmd_Set(1);
		Attitude_Set(1);
		OpenMV_Set(1);
	}else if(state == 1)
	{
		if(Read_MoveState()==0 && Read_GoodsAppState()==0 && *(Read_QrCode()+6) != 0)
		{
			state = 0;
			main_app_flag = 0;
		}
	}
}

