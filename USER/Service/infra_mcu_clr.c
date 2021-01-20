#include "infra_mcu_clr.h"

void Send_Beat(void)
{
	Usart_Sbuffer_Clear(2);
}

