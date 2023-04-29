#ifndef __RTC_H__
#define __RTC_H__

#include "main.h"
void rtc_init();
void RTC_calculate_time(void);
void RTC_calculate_date(void);

uint8_t get_minutes();
uint8_t get_hours();
uint8_t get_year();
uint8_t get_month();
uint8_t get_day();

#endif /*__RTC_H__*/
