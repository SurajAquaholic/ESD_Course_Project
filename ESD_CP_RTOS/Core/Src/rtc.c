#include "rtc.h"

//Macros
#define POWER_INTERFACE_CLK 28
#define NO_WRITE_PROTECT 8
#define LOW_SPEED_OSC 0
#define LOW_SPEED_OSC_READY 1
#define RTC_CLOCK 15
#define LSI_CLOCK 9
#define INIT_MODE 7
#define PREDIV_S 0xF9
#define PREDIV_A 0x7F
#define BYPASS 5
#define RESET_MASK 0x00000000


/**********Current Date Time Settings**********************/
#define DATE_ONES	 	0b0000
#define DATE_ONES_POS	0
#define DATE_TENS		0b11
#define DATE_TENS_POS	4
#define MONTH_ONES		0b0100
#define MONTH_ONES_POS	8
#define YEAR_ONES		0b0011
#define YEAR_ONES_POS	16
#define YEARS_TENS		0b0010
#define YEARS_TENS_POS	20

#define CLEAR_MASK	0xFFFFFFFF

static uint8_t Hours = 0;
static uint8_t Minutes = 0;
static uint8_t Seconds = 0;
static uint8_t Month = 0;
static uint8_t Day = 0;
static uint8_t Year = 0;
volatile static int test = 0;

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
	RTC -> PRER = RESET_MASK;
	RTC->PRER |= PREDIV_S; //Set the prescalar to bring down the LSI frequency 1Hz
	RTC->PRER |= PREDIV_A<<16;
	//Set the TR and DR registers for date and time
	RTC->TR &= ~(CLEAR_MASK);
	RTC->TR |= (0b100 << 12); //minutes msb is 4
	RTC->TR |= (0b111 << 16); //hours lsb is 7
	RTC->TR |= (0b01 << 20); //hours msb is 1 i.e. 17.40.0
	RTC->DR &= ~(CLEAR_MASK);
	RTC->DR |= MASK(DATE_ONES,DATE_ONES_POS); //date ones is 0
	RTC->DR |= MASK(DATE_TENS,DATE_TENS_POS); //date tens is 3
	RTC->DR |= MASK(MONTH_ONES,MONTH_ONES_POS); //month ones is 4
	RTC->DR |= MASK(YEAR_ONES,YEAR_ONES_POS); //years once is 3
	RTC->DR |= MASK(YEARS_TENS,YEARS_TENS_POS); //years tens position is 2
	RTC->CR |= MASK(ENABLE_,BYPASS); //Calendar values are taken directly from the calendar counters.
	RTC->ISR &= ~MASK(ENABLE_,INIT_MODE); //Clear the Init bit to exit Initialization mode
	PWR->CR &= ~MASK(ENABLE_,NO_WRITE_PROTECT); //Enable the Write protect back
}

void RTC_calculate_time (void)
{
	uint8_t min = 0;
	uint8_t hrs = 0;
	Seconds=(((RTC->TR & 0x7f) >> 4)*10)+(RTC->TR & 0xf);
	min=((RTC->TR & 0x7f00) >> 8);
	Minutes=(((min & 0x7f)>>4)*10)+(min & 0xf);
	hrs=((RTC->TR & 0x7f0000) >> 16);
	Hours=(((hrs & 0x7f)>>4)*10)+(hrs & 0xf);
}

void RTC_calculate_date(void)
{
	Year=((RTC->DR >> 20)*10) + ((RTC->DR >>16) & 0xf);
	Month=((RTC->DR >> 12) & 1)*10 + ((RTC->DR >>8) & 0xf);
	Day=((RTC->DR >> 4) & 3)*10 + (RTC->DR & 0xf);
}

/*
 * Getter functions for
 */
uint8_t get_minutes()
{
	return Minutes;
}

uint8_t get_hours()
{
	return Hours;
}

uint8_t get_year()
{
	return Year;
}

uint8_t get_month()
{
	return Month;
}

uint8_t get_day()
{
	return Day;
}