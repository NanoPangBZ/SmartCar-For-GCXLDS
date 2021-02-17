#ifndef _STREET_MOTOR_H_
#define _STREET_MOTOR_H_

#include "system_core.h"

#define	PortA_Pin	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7
#define	PortB_Pin	GPIO_Pin_0 | GPIO_Pin_1 

//50Hz PWM频率
#define	SM_Period		20000 - 1
#define	SM_Prescaler	72 - 1


//机械臂的CCR寄存器地址
static uint16_t* street_width[6] = {(uint16_t*)&TIM3->CCR1 , (uint16_t*)&TIM3->CCR2,
							(uint16_t*)&TIM3->CCR3 , (uint16_t*)&TIM3->CCR4,
							(uint16_t*)&TIM2->CCR1 , (uint16_t*)&TIM2->CCR2 };

void StreetMotor_Init(void);
void StreetMotor_GPIO_Config(void);			
void StreetMotor_TIM_Config(void);

#endif

