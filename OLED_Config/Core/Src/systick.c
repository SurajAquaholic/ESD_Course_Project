/*
 * systick.c
 *
 *  Created on: Apr 28, 2023
 *      Author: suraj
 */

#include "systick.h"

#define ALTERNATE_CLOCK 30000000/16
#define ONE_MILLISEC	1000
/******** GLOBAL VARIABLES ***********/
static int Systick_count=0;
int timeout;
int msec_since_startup;
//A Global structure is used to keep a track of the time

/*
 * @name Init_Systick
 *
 * @brief: Configures the timer
 *
 * @Source: Dean Textbook listing 7.1
 *
 * SysTick Interrupt Time Period = (SysTick_LOAD + 1) * Clock Period
*/
void Init_Systick(void){
	SysTick->LOAD = (ALTERNATE_CLOCK/ONE_MILLISEC);	//Set reload to get 1ms interrupts
	NVIC_SetPriority(SysTick_IRQn, 3);			//Set interrupt priority
	SysTick->VAL = 0;							//Force load of reload value
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | 	//Enable interrupt,alt.clocksource
					SysTick_CTRL_ENABLE_Msk;	//Enable SysTick timer
	msec_since_startup = 0;
}
/*
 * @name SysTick_Handler
 *
 * @brief: Runs each time the timer reaches zero, which is 1Hz in this example
 *
 * @Source: Dean Textbook listing 7.2
 *
 */

void SysTick_Handler(void){
	Systick_count++;
	msec_since_startup ++;
}


/*
 * @name Delay
 *
 * @brief runs the while loop till Systick_counts equal to the required time delay in millisecounds
 *
 * @Source Dean 41-43
 *
 * @param millisecounds
 *
 * @return void
 */
void Delay(volatile float millisecounds) {
timeout=0;
Systick_count=0; // Reset Systick count
  while (Systick_count<millisecounds) {
	;
  }
  timeout=1; //Set timeout flag to 1
}

//Getter function for timeout flag
int get_timeout_flag(void) {
	return timeout; }

//Getter functions for msec_since_startup
int getter_msec_since_startup(void){
	return msec_since_startup;
}

//Start the Systick Count
void Start_Systick_Count(void){
	Systick_count=0; //// Reset Systick count
}
//Stop the Systick Count
int get_Systick_Count(void){
	return Systick_count;
}
