/*
 * rtc.h
 *
 *  Created on: Apr 27, 2023
 *      Author: suraj
 */

#ifndef SRC_RTC_H_
#define SRC_RTC_H_


#include "main.h"

typedef struct{
  uint8_t Hours;
  uint8_t Minutes;
  uint8_t Seconds;
}RTC_TimeTypeDef;


typedef struct{
  uint8_t Month;
  uint8_t Day;
  uint8_t Year;

}RTC_DateTypeDef;

void rtc_init();
RTC_TimeTypeDef RTC_get_time(void);
RTC_DateTypeDef RTC_get_date(void);

#endif /* SRC_RTC_H_ */
