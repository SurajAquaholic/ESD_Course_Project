#include "timer.h"

int count = 0;
void timer_init()
{
	RCC->APB1ENR |= (SET << TIM2_CLK); //Enable the clock for Timer2
	TIM2->PSC = 0; //The PSC and ARR values are set to provide 1millisec delay
	TIM2->ARR = 15999;
	TIM2->CR1 |= (SET << URS); //By setting this bit counter overflow/underflow generates an update interrupt
	TIM2->DIER |= (SET << UIE); //Update interrupt enable
	TIM2->EGR |= (SET << UG); //To clear the counter and generate the interrupt again
	NVIC_EnableIRQ(TIM2_IRQn); //Enable the Interrupt IRQ for TIM2
}


/*
 * @brief This Function will provide delay in milliseconds
 *
 * @Parameters milliSec is the delay that needs to be passed as an argument
 */
void delay_in_millisec(int milliSec)
{
	TIM2->CR1 |= (SET << CEN); //Start the timer counter
	while(count<milliSec); //Wait till the delay is completed
	TIM2->CR1 &= ~(SET << CEN); //Clear the timer counter
	count = 0; //set the count to Zero
}

/*
  * @brief This is the interrupt handler that is called when ever the counter overflows
  *  It gets called for every 1millisec as we have set the ARR and PSC for 1Millisec
  *
  */
void TIM2_IRQHandler(void)
{
	if(TIM2->SR & (SET << UIF))  //Check for the interrupt
	{
		TIM2->SR &= ~(SET << UIF); //Clear the interrupt
		count++;
	}
}
