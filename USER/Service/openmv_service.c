#include "openmv_service.h"

void openmv_service(void)
{
	OpenMV_Updata();
}

void OpenMV_Init(void)
{
	uint8_t *Cmd;
	Cmd = Read_Usart_Sbuffer(2);
	while(*Cmd == 0);
	while(*(Cmd+1) != 'A')
		Usart_Sbuffer_Clear(2);
	Usart_Sbuffer_Clear(2);
	uint8_t temp;
	temp = OpenMV_Tstate + 0x30;
	Usart2_Send(&temp,1);
}

void OpenMV_Set(uint8_t State)
{
	OpenMV_Tstate = State;
}

void OpenMV_Updata(void)
{
	uint8_t*Cmd;
	uint8_t temp;
	uint8_t Blob;
	uint8_t cx;
	uint8_t w;
	Cmd = Read_Usart_Sbuffer(2);
	if(*Cmd!=0)
	{
		if(*(Cmd+1) != 0xee )
			//确认OpenMV数据头
		{
			Usart_Sbuffer_Clear(2);
		}
		else if(*(Cmd + *Cmd) == 0xde)		//确认OpenMV数据是否结尾
		{
			OpenMV_State = *(Cmd + 2);
			//OpenMV目标状态转ASSIC
			temp = OpenMV_Tstate + 0x30;
			//确认目标状态与实际状态
			if(OpenMV_State!=OpenMV_Tstate)
				Usart2_Send(&temp,1);
			//数据处理
			switch(OpenMV_State)
			{
				case 1:
					//二维码读取和OLED展示
					OLED_ShowString("TC:",6,0,2);
					for(temp=3;*(Cmd+temp)!=0xde;temp++)
					{
						QrCode[temp - 3] = *(Cmd+temp) ;
						OLED_ShowChar(QrCode[temp - 3],6,(temp-3)*8+27,2);
					}
					//数字ASSCI转16进制(简化任务码)
					for(temp=0;temp<7;temp++)
						QrCode[temp] -= 0x30;
					break;
				case 2:
					Blob = *(Cmd+3) + 1;
					cx = *(Cmd+4);
					w = *(Cmd+5);
					if(cx>8 && cx<24)
					{
						LookData[0] = Blob;
						LookData[1] = cx;
						LookData[2] = w;
					}
					break;
				case 3:
					for(temp=0;temp<25;temp++)
						LineFind[temp] = *(Cmd+3+temp);
					break;
			}
			Usart_Sbuffer_Clear(2);
		}else
		{
			Usart_Sbuffer_Clear(2);
		}
	}
}

uint8_t*Read_LineData(void)
{
	uint8_t x,y;
	uint8_t temp;
	//横线位置判别 从左往右统计是否右3个格子不为0
	for(x=0;x<5;x++)
	{
		temp = 0;
		for(y=0;y<5;y++)
			if(LineFind[x*5+y]!=0)
				temp++;
		if(temp>3)
			break;
	}
	if(temp<4)
		LookPos[1] = 0;
	else
		LookPos[1] = x+1;
	//横线位置判别 从左往右统计是否右3个格子不为0
	for(x=0;x<5;x++)
	{
		temp = 0;
		for(y=0;y<5;y++)
			if(LineFind[5*y+x]!=0)
				temp++;
		if(temp>3)
			break;
	}
	if(temp<4)
		LookPos[0] = 0;
	else
		LookPos[0] = x+1;
	OLED_ShowNum(LookPos[0],0,0,1);
	OLED_ShowNum(LookPos[1],0,7,1);
	return LookPos;
}

uint8_t*Read_LookData(void)
{
	return LookData;
}

uint8_t*Read_Recording(void)
{
	return Recording;
}

uint8_t*Read_QrCode(void)
{
	return QrCode;
}

