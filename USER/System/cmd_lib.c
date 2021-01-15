#include "cmd_lib.h"

void Byte_Carry(uint8_t*EpAdd,uint8_t*CpAdd,uint8_t len)
{
	uint8_t temp;
	for(temp = 0;temp<len;len++)
		EpAdd[temp] = CpAdd[temp];
}

void Byte_Push(uint8_t*Add,uint8_t len)
{
	uint8_t temp;
	for(temp=0;temp<len;temp++)
	{
		Add[temp] = Add[temp + len];
		Add[temp + len] = 0;
	}
}
