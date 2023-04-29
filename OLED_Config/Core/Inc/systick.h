/*
 * systick.h
 *
 *  Created on: Apr 28, 2023
 *      Author: suraj
 */

#ifndef INC_SYSTICK_H_
#define INC_SYSTICK_H_

#include "stm32f4xx.h"

/******************* Function Prototype ***********************/
void Init_Systick(void);
void SysTick_Handler(void);
void Delay(volatile float time_del);
int get_timeout_flag(void);
int getter_msec_since_startup(void);
int get_Systick_Count(void);
void Start_Systick_Count(void);

#endif /* INC_SYSTICK_H_ */
