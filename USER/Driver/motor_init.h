#ifndef	_MOTOR_INIT_H_
#define	_MOTOR_INIT_H_

#include "system_core.h"

#define ARR			7200 - 1

#define Dir_Pin		GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | \
					GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 
#define Motor_Pin	GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9
#define Hall_Pin		GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | \
					GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7
#define PWM_TIM	TIM4
#define HALL_TIM	TIM6

void Motor_Init(void);

void TB6612_Init(void);			//TB6612初始化,Dir的引脚初始化
void Motor_TIM_Config(void);		//电机PWM定时器配置
void Motor_GPIO_Config(void);		//电机PWM引脚配置
void Hall_TIM_Config(void);		//霍尔测速时间轴配置
void Hall_GPIO_Config(void);		//霍尔测速引脚初始化
void Hall_EXTI_Config(void);		//霍尔测速引脚中断线配置

#endif

