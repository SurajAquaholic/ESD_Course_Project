#include "ir_sensor.h"
//#include "ssd1306.h"
//#include "bitmap.h"
#include "stdbool.h"
//pa 7 and pa10
#define GPIOA_EN 0
#define PA7_MODER 14
#define PA6_MODER 12
#define PA7 7
#define PA6 6
#define INPUT_MODE 3
#define PUPD_PA7 15
#define PUPD_PA6 13
#define PA5 10
#define GPIOA_EN 0
#define PA5_SET 5
#define PA5_CLEAR 21


static bool vehicle_leftside = false;
static bool vehicle_rightside = false;
void ir_init()
{
	RCC->AHB1ENR |= MASK(ENABLE_, GPIOA_EN); //Enable the Clock for GPIO A
	GPIOA->MODER &= ~(MASK(INPUT_MODE, PA7_MODER)); //Set the mode to GPIO Input for PA7
	GPIOA->PUPDR |= MASK(ENABLE_, PUPD_PA7); //Configure a Pull down resistor to PA7
	GPIOA->MODER &= ~(MASK(INPUT_MODE, PA6_MODER)); //Set the mode to GPIO Input for PA6
	GPIOA->PUPDR |= MASK(ENABLE_, PUPD_PA6); //Configure a Pull down resistor to PA6
	GPIOA->MODER |= MASK(ENABLE_, PA5); //Set output mode to GPIO5 for buzzer
	GPIOA->OTYPER &= ~MASK(ENABLE_, PA5_SET); //output type register push - pull
	GPIOA->PUPDR |= MASK(ENABLE_, PA5); // pull up for buzzer
}

void check_ir_sensor()
{
	if(GPIOA->IDR & MASK(ENABLE_, PA7))
	{
		vehicle_leftside = true;
		GPIOA->BSRR |= MASK(ENABLE_, PA5_SET); //Set the buzzer
//		SSD1306_Clear();
//		SSD1306_DrawBitmap(0,0,Left_Alert, 128, 64, 1);
//		SSD1306_UpdateScreen();

	}
	else
	{
		vehicle_leftside = false;
		if(!vehicle_rightside)
		{
			GPIOA->BSRR |= MASK(ENABLE_, PA5_CLEAR); //Clear the buzzer
		}
//		SSD1306_Clear();
	}
	if(GPIOA->IDR & MASK(ENABLE_, PA6))
	{
		vehicle_rightside = true;
		GPIOA->BSRR |= MASK(ENABLE_, PA5_SET); //Set the buzzer
//		SSD1306_Clear();
//		SSD1306_DrawBitmap(0,0,Right_Alert, 128, 64, 1);
//		SSD1306_UpdateScreen();

	}
	else
	{
		vehicle_rightside = false;
		if(!vehicle_leftside)
		{
			GPIOA->BSRR |= MASK(ENABLE_, PA5_CLEAR); //Clear the buzzer
		}
//		SSD1306_Clear();
	}
//	if(vehicle_leftside && vehicle_rightside)
//	{
//		SSD1306_Clear();
//		SSD1306_DrawBitmap(0,0,Both_Side_Alert, 128, 64, 1);
//		SSD1306_UpdateScreen();
//	}
}
