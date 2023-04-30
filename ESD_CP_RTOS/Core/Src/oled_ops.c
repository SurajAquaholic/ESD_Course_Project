/*
 * oled_ops.c
 *
 *  Created on: Apr 28, 2023
 *      Author: suraj
 */


#include "oled_ops.h"

//Row Position to print
#define TIME_ROW 			35
#define DATE_ROW			0
#define TEMP_ROW			0
#define START_CONVERSION 30
//Column Position to print
#define HOURS_TENS_POSITION 30
#define HOURS_ONES_POSITION 44
#define MIN_TENS_POSITION 	72
#define MIN_ONES_POSITION 	86
#define COLON_POSITION		58

#define DATE_COLUMN			0
#define TEMP_COLUMN			96

//USE
#define ASCII_CONVERT(x)	x + 48

static uint8_t prev_min_val = 0;
static uint8_t prev_hour_val = 0;
static char min_ones = '\0';
static char min_tens = '\0';
static char hours_ones = '\0';
static char hours_tens = '\0';

static uint8_t date_val = 0;
static uint8_t month_val = 0;
static uint8_t year_val = 0;

static char date_ones = '\0';
static char date_tens = '\0';
static char month_ones = '\0';
static char month_tens = '\0';
static char year_ones = '\0';
static char year_tens = '\0';

static uint8_t temp_val = 0;

static char temp_tens  = '\0';
static char temp_ones = '\0';

static char date_string[] ={'0','4','/','3','0','/','2','3','\0'};
static char temp_string[] = {'2','7','C','\0'};
void Time_Update(void){
	//SSD1306_Clear();
	SSD1306_GotoXY (COLON_POSITION,TIME_ROW);
	SSD1306_Putc(':', &Font_16x26, 1);
	//SSD1306_UpdateScreen(); //display

	/*Calculation to seperate the 10s with the ones*/
		prev_min_val = get_minutes();

		min_ones = (prev_min_val % 10) + '0';

		min_tens = (prev_min_val / 10) + '0';

		SSD1306_GotoXY(MIN_TENS_POSITION, TIME_ROW);
		SSD1306_Putc(min_tens, &Font_16x26, 1);
		//SSD1306_UpdateScreen();

		SSD1306_GotoXY(MIN_ONES_POSITION, TIME_ROW);
		SSD1306_Putc(min_ones, &Font_16x26, 1);
		//SSD1306_UpdateScreen();

		/*Calculation to seperate the 10s with the ones*/
		prev_hour_val = get_hours();

		hours_ones = (prev_hour_val % 10)+ '0';

		hours_tens = (prev_hour_val / 10) + '0';

		SSD1306_GotoXY(HOURS_TENS_POSITION, TIME_ROW);
		SSD1306_Putc(hours_tens, &Font_16x26, 1);
		//SSD1306_UpdateScreen();

		SSD1306_GotoXY(HOURS_ONES_POSITION, TIME_ROW);
		SSD1306_Putc(hours_ones, &Font_16x26, 1);
		//SSD1306_UpdateScreen();

		month_val = get_month();

		month_tens = (month_val / 10) + '0';
		date_string[0] = month_tens;

		month_ones = (month_val % 10)+ '0';
		date_string[1] = month_ones;

		date_val = get_day();

		date_tens = (date_val / 10) + '0';
		date_string[3] = date_tens;

		date_ones = (date_val % 10)+ '0';
		date_string[4] = date_ones;

		year_val = get_year();

		year_tens = (year_val / 10) + '0';
		date_string[6] = year_tens;

		year_ones = (year_val % 10)+ '0';
		date_string[7] = year_ones;

		SSD1306_GotoXY (DATE_COLUMN,DATE_ROW);
		SSD1306_Puts (date_string, &Font_7x10, 1);
		//SSD1306_UpdateScreen();

		temp_val = get_temp();

		temp_tens = (temp_val / 10) + '0';
		temp_string[0] = temp_tens;

		temp_ones = (temp_val % 10) + '0';
		temp_string[1] = temp_ones;

		SSD1306_GotoXY (TEMP_COLUMN,TEMP_ROW);
		SSD1306_Puts (temp_string, &Font_7x10, 1);
		SSD1306_UpdateScreen();
		ADC1->CR2 |= MASK(ENABLE_, START_CONVERSION); //Start the next conversion
}
