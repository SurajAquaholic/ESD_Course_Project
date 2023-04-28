/*
 * rtc.c
 *
 *  Created on: Apr 27, 2023
 *      Author: suraj
 */


#include "rtc.h"

//Macros
#define POWER_INTERFACE_CLK 28
#define NO_WRITE_PROTECT 8
#define LOW_SPEED_OSC 0
#define LOW_SPEED_OSC_READY 1
#define RTC_CLOCK 15
#define LSI_CLOCK 9
#define INIT_MODE 7
#define PREDIV_S 0x13F
#define PREDIV_A 0x63
#define BYPASS 5
#define MASK(x,y)  x<<y
#define ENABLE_	 1


RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

/*
 * @name rtc_init();
 *
 */
void rtc_init()
{
	RCC->APB1ENR |= MASK(ENABLE_,POWER_INTERFACE_CLK); // Enable clock for power interface
	PWR->CR |= MASK(ENABLE_,NO_WRITE_PROTECT); // Disable the write protect to RTC
	RCC->CSR |= MASK(ENABLE_,LOW_SPEED_OSC); // Enable LSI RC oscillator ON
	while(!(RCC->CSR & MASK(ENABLE_,LOW_SPEED_OSC_READY))); // Wait till the LSI RC oscillator is ON
	RCC->BDCR |= MASK(ENABLE_,RTC_CLOCK) | MASK(ENABLE_,LSI_CLOCK); // Enable clock for RTC module and select LSI as clock source
	RTC->WPR |= 0xCA; // Unlock the write protection by using the key
	RTC->WPR |= 0x53; // Unlock the write protection by using the key
	RTC->ISR |= MASK(ENABLE_,INIT_MODE); // The calendar counter is stopped to allow update
	while(!(RTC -> ISR & RTC_ISR_INITF)); //wait till its set
	RTC->PRER |= PREDIV_S; //Set the prescalar to bring down the LSI frequency 1Hz
	RTC->PRER |= PREDIV_A<<16;
	//Set the TR and DR registers for date and time
//	RTC->TR |= (0b001 << 12); //minutes msb is 1
//	RTC->TR |= (0b001 << 16); //hours lsb is 1
//	RTC->TR |= (0b01 << 20); //hours msb is 1 i.e. 11.10.0
	RTC->TR &= ~(0xFFFFFFFF);
	RTC->TR |= (0b100 << 12); //minutes msb is 4
	RTC->TR |= (0b111 << 16); //hours lsb is 7
	RTC->TR |= (0b01 << 20); //hours msb is 1 i.e. 17.40.0
	RTC->DR &= ~(0xFFFFFFFF);
	RTC->DR |= (0b0011 << 0); //date units is 3
	RTC->DR |= (0b10 << 4); //date units is 2
	RTC->DR |= (0b0100 <<8); //month uints is 4
	RTC->DR |= (0b0011 << 16); //years uints is 3
	RTC->DR |= (0b0010 <<20); //years tens position is 2
	RTC->CR |= MASK(ENABLE_,BYPASS); //Calendar values are taken directly from the calendar counters.
	RTC->ISR &= ~MASK(ENABLE_,INIT_MODE); //Clear the Init bit to exit Initialization mode
	PWR->CR &= ~MASK(ENABLE_,NO_WRITE_PROTECT); //Enable the Write protect back
}

RTC_TimeTypeDef RTC_get_time (void)
{
	uint8_t min = 0;
	uint8_t hours = 0;
	sTime.Seconds=(((RTC->TR & 0x7f) >> 4)*10)+(RTC->TR & 0xf);
	min=((RTC->TR & 0x7f00) >> 8);
	sTime.Minutes=(((min & 0x7f)>>4)*10)+(min & 0xf);
	hours=((RTC->TR & 0x7f0000) >> 16);
	sTime.Hours=(((hours & 0x7f)>>4)*10)+(hours & 0xf);

	return sTime;
}

RTC_DateTypeDef RTC_get_date(void)
{
	sDate.Year=((RTC->DR >> 20)*10) + ((RTC->DR >>16) & 0xf);
	sDate.Month=((RTC->DR >> 12) & 1)*10 + ((RTC->DR >>8) & 0xf);
	sDate.Day=((RTC->DR >> 4) & 3)*10 + (RTC->DR & 0xf);

	return sDate;
}
