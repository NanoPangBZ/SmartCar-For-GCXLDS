#include "motor_driver.h"

void Disitance_clear(void)
{
	uint16_t n;
	for( n=0 ; n<4 ; n++)
		distance[n] = 0;
}

int* Read_Speed(void)
{
	static int speed[4] = {0,0,0,0};
	long long check;
	long long temp;
	uint8_t n;
	for(n=0;n<4;n++)
	{
		check = TIM6->CNT - that_time[n];
		if(over_time != that_over_time[n])
			check += 60000*(over_time - that_over_time[n]);
		if(check < 20000)
		{
				temp = that_time[n] - last_time[n];
				if(last_over_time[n] != that_over_time[n])
					temp += 60000*(that_over_time[n] - last_over_time[n]);
				temp = 20000 / temp;
				if(last_dir[n] != that_dir[n] && temp - speed[n] < 60 && temp -speed[n] > -60 )
					temp = temp / 2;
				if(that_dir[n] != 0)
					temp = -temp;
				if(temp < 500 && temp >-500)
					speed[n] =temp;
		}else
		{
			speed[n] = 0;
		}
	}
	return speed;
}

long int*Read_Distance(void)
{
	return distance;
}

void PWM_Out(int*PWM)
{
	if(*PWM != 0)
	{
		if(*PWM>0)
		{
			GPIO_SetBits(GPIOC,MAD2);
			GPIO_ResetBits(GPIOC,MAD1);
			TIM_SetCompare1(TIM4,*PWM);
		}else
		{
			GPIO_SetBits(GPIOC,MAD1);
			GPIO_ResetBits(GPIOC,MAD2);
			TIM_SetCompare1(TIM4,-*PWM);
		}
	}else
	{
		GPIO_SetBits(GPIOC,MAD1 | MAD2);
		TIM_SetCompare1(TIM4,0xffff);
	}
	PWM++;
	if(*PWM != 0)
	{
		if(*PWM>0)
		{
			GPIO_SetBits(GPIOC,MBD1);
			GPIO_ResetBits(GPIOC,MBD2);
			TIM_SetCompare2(TIM4,*PWM);
		}else
		{
			GPIO_SetBits(GPIOC,MBD2);
			GPIO_ResetBits(GPIOC,MBD1);
			TIM_SetCompare2(TIM4,-*PWM);
		}
	}else
	{
		GPIO_SetBits(GPIOC,MBD1 | MBD2);
		TIM_SetCompare2(TIM4,0xffff);
	}
	PWM++;
	if(*PWM != 0)
	{
		if(*PWM>0)
		{
			GPIO_SetBits(GPIOC,MCD1);
			GPIO_ResetBits(GPIOC,MCD2);
			TIM_SetCompare3(TIM4,*PWM);
		}else
		{
			GPIO_SetBits(GPIOC,MCD2);
			GPIO_ResetBits(GPIOC,MCD1);
			TIM_SetCompare3(TIM4,-*PWM);
		}
	}else
	{
		GPIO_SetBits(GPIOC,MCD1 | MCD2);
		TIM_SetCompare3(TIM4,0xffff);
	}
	PWM++;
	if(*PWM != 0)
	{
		if(*PWM>0)
		{
			GPIO_SetBits(GPIOC,MDD1);
			GPIO_ResetBits(GPIOC,MDD2);
			TIM_SetCompare4(TIM4,*PWM);
		}else
		{
			GPIO_SetBits(GPIOC,MDD2);
			GPIO_ResetBits(GPIOC,MDD1);
			TIM_SetCompare4(TIM4,-*PWM);
		}
	}else
	{
		GPIO_SetBits(GPIOC,MDD1 | MDD2);
		TIM_SetCompare4(TIM4,0xffff);
	}
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) == SET)
	{
		last_over_time[3] = that_over_time[3];
		last_time[3] = that_time[3];
		that_over_time[3] = over_time;
		that_time[3] = TIM6->CNT;
		EXTI_ClearITPendingBit(EXTI_Line2);
		last_dir[3] = that_dir[3];
		if(GPIO_ReadInputDataBit(GPIOC,HallD2_Pin) != SET)
		{
			distance[3]++;
			that_dir[3] = 0;
		}else
		{
			distance[3]--;
			that_dir[3] = 1;
		}
	}
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		last_over_time[2] = that_over_time[2];
		last_time[2] = that_time[2];
		that_over_time[2] = over_time;
		that_time[2] = TIM6->CNT;
		EXTI_ClearITPendingBit(EXTI_Line0);
		last_dir[2] = that_dir[2];
		if(GPIO_ReadInputDataBit(GPIOC,HallC2_Pin) != SET)
		{
			distance[2]--;
			that_dir[2] = 1;
		}else
		{
			distance[2]++;
			that_dir[2] = 0;
		}
	}
}

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) == SET)
	{
		last_over_time[1] = that_over_time[1];
		last_time[1] = that_time[1];
		that_over_time[1] = over_time;
		that_time[1] = TIM6->CNT;
		EXTI_ClearITPendingBit(EXTI_Line4);
		last_dir[1] = that_dir[1];
		if(GPIO_ReadInputDataBit(GPIOC,HallB2_Pin) != SET)
		{
			distance[1]--;
			that_dir[1] = 1;
		}else
		{
			distance[1]++;
			that_dir[1] = 0;
		}
	}
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) == SET)
	{
		last_over_time[0] = that_over_time[0];
		last_time[0] = that_time[0];
		that_over_time[0] = over_time;
		that_time[0] = TIM6->CNT;
		EXTI_ClearITPendingBit(EXTI_Line5);
		last_dir[0] = that_dir[0];
		if(GPIO_ReadInputDataBit(GPIOC,HallA2_Pin) != SET)
		{
			distance[0]++;
			that_dir[0] = 0;
		}else
		{
			distance[0]--;
			that_dir[0] = 1;
		}
	}
}

void  TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update) == SET)
	{
		over_time++;
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	}
}
