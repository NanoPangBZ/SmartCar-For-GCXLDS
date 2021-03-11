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
	uint8_t flag = 0;
	uint8_t Blob;
	Cmd = Read_Usart_Sbuffer(2);
	if(*Cmd!=0)
	{
		if(*(Cmd+1) != 0xee)
			Usart_Sbuffer_Clear(2);
		else if(*(Cmd + *Cmd) == 0xde)
		{
			OpenMV_State = *(Cmd + 2);
			temp = OpenMV_Tstate + 0x30;
			if(OpenMV_State!=OpenMV_Tstate)
				Usart2_Send(&temp,1);
			switch(OpenMV_State)
			{
				case 1:
					for(temp=3;*(Cmd+temp)!=0xde;temp++)
					{
						QrCode[temp - 3] = *(Cmd+temp);
						OLED_ShowChar(QrCode[temp - 3],7,temp*8,1);
					}
					break;
				case 2:
					Blob = *(Cmd+3) + 1;
					if(RecordingNum==0)
					{
						Recording[0] = Blob;
						RecordingNum++;
					}else
					{
						for(temp=0;temp<RecordingNum;temp++)
						{
							if(Recording[temp]==Blob)
								flag = 1;
						}
						if(flag==0)
							Recording[RecordingNum] = Blob;
					}
					OLED_ShowNum(Blob,0,0,1);
					if(RecordingNum == 3)
						PositionService_Stop();
					break;
			}
			Usart_Sbuffer_Clear(2);
		}
	}
}

uint8_t*Read_Recording(void)
{
	static uint8_t temp;
	temp = 0xff;
	if(RecordingNum<3)
		return &temp;
	else
		return Recording;
}

uint8_t*Read_QrCode(void)
{
	return QrCode;
}

