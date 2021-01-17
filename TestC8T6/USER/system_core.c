#include "system_core.h"

void PCB_System_Init(void)
{
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        Usart_Config();
        IIC_Init();
	OLED_Init();
	OLED_ShowNum(111,0,0,2);
	OLED_ShowNum(232,2,0,1);
	OLED_ShowNum(100,3,0,2);
	OLED_ShowNum(123,0,12,1);
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
