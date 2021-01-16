#include "system_core.h"

void PCB_System_Init(void)
{
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        Usart_Config();
        IIC_Init();
	OLED_Init();
	OLED_ShowChar('F',0,0,2);
        SysTick_Config(5*72000);			//系统主心跳
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	System_Time++;
}
