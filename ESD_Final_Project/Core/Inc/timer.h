#ifndef __TIMER_H__
#define __TIMER_H__

#include<main.h>
#include<stdbool.h>
#define TIM2_CLK 0
#define URS 2
#define UG 0
#define UIE 0
#define CEN 0
#define UIF 0
#define TEN_POWER_3 1000

void timer_init();
void TIM2_IRQHandler(void);
void delay_in_millisec(int milliSec);


#endif /*__TIMER_H__*/

