#include "adc.h"

//Macros
#define ADC_CLOCK 8
#define GPIOA_CLOCK 0
#define PA0 0
#define ADC_RESOLUTION 24
#define ANALOG_MODE 3
#define ADC_ENABLE 0
#define INTERRUPT_EOC 5
#define EOC 1
#define START_CONVERSION 30

float static volatile adc_value = 0;
static int temperature = 0;

const int lookupTable[] = {
  1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
  11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000,
  21000, 22000, 23000, 24000, 25000, 26000, 27000, 28000, 29000
};


void adc_init(void)
{
	RCC->AHB1ENR |= MASK(ENABLE_, GPIOA_CLOCK); // Enable clock source for PORT A
	GPIOA->MODER |= MASK(ANALOG_MODE, PA0); // PA0 pin is Analog Mode
	RCC->APB2ENR |= MASK(ENABLE_, ADC_CLOCK);  // Enable clock source for ADC1
	ADC1->CR1 |= MASK(ENABLE_, ADC_RESOLUTION);  //  set ADC resolution to 10bit i.e. max is 1023
	ADC1->CR2 &= ~ MASK(ENABLE_, ADC_ENABLE);  //  ADC disable
	ADC1->SQR3 |= 0; // Enable ADC 0th Channel
	ADC1->CR1 |= MASK(ENABLE_, INTERRUPT_EOC); //end of conversion interrupt
	ADC1->CR2 |=  MASK(ENABLE_, ADC_ENABLE);  // ADC ON
	NVIC_EnableIRQ(ADC_IRQn);
	NVIC_SetPriority(ADC_IRQn,2);
	ADC1->CR2 |= MASK(ENABLE_, START_CONVERSION);  // Start  ADC conversion
}


void ADC_IRQHandler()
{
	//store the DR register contents in a variable,
	//no need to clear the EOC as its cleared when you read the DR register
	if(ADC1->SR & MASK(ENABLE_, EOC))
	{
		adc_value = ADC1->DR;
	}
}

void calculate_temperature()
{
	float analog_voltage = 0;
	int ntc_resistance = 0;
	analog_voltage = (3*adc_value)/1023; //gets the analog voltage corresponding to adc output value
	ntc_resistance = ((-analog_voltage*10000)/(analog_voltage-3)); //3 is vcc, 10k is nominal resistance
	if(ntc_resistance == lookupTable[28])
	{
		temperature = 2;
	}
	else if(ntc_resistance < lookupTable[28] && ntc_resistance >= lookupTable[27])
	{
		temperature = 3;
	}
	else if(ntc_resistance < lookupTable[27] && ntc_resistance >= lookupTable[26])
	{
		temperature = 4;
	}
	else if(ntc_resistance < lookupTable[26] && ntc_resistance >= lookupTable[25])
	{
		temperature = 5;
	}
	else if(ntc_resistance < lookupTable[25] && ntc_resistance >= lookupTable[24])
	{
		temperature = 6;
	}
	else if(ntc_resistance < lookupTable[24] && ntc_resistance >= lookupTable[23])
	{
		temperature = 7;
	}
	else if(ntc_resistance < lookupTable[23] && ntc_resistance >= lookupTable[22])
	{
		temperature = 8;
	}
	else if(ntc_resistance < lookupTable[22] && ntc_resistance >= lookupTable[21])
	{
		temperature = 9;
	}
	else if(ntc_resistance < lookupTable[21] && ntc_resistance >= lookupTable[20])
	{
		temperature = 10;
	}
	else if(ntc_resistance < lookupTable[20] && ntc_resistance >= lookupTable[19])
	{
		temperature = 11;
	}
	else if(ntc_resistance < lookupTable[19] && ntc_resistance >= lookupTable[18])
	{
		temperature = 12;
	}
	else if(ntc_resistance < lookupTable[18] && ntc_resistance >= lookupTable[17])
	{
		temperature = 13;
	}
	else if(ntc_resistance < lookupTable[17] && ntc_resistance >= lookupTable[16])
	{
		temperature = 14;
	}
	else if(ntc_resistance < lookupTable[16] && ntc_resistance >= lookupTable[15])
	{
		temperature = 15;
	}
	else if(ntc_resistance < lookupTable[15] && ntc_resistance >= lookupTable[14])
	{
		temperature = 17;
	}
	else if(ntc_resistance < lookupTable[14] && ntc_resistance >= lookupTable[13])
	{
		temperature = 19;
	}
	else if(ntc_resistance < lookupTable[13] && ntc_resistance >= lookupTable[12])
	{
		temperature = 20;
	}
	else if(ntc_resistance < lookupTable[12] && ntc_resistance >= lookupTable[11])
	{
		temperature = 22;
	}
	else if(ntc_resistance < lookupTable[11] && ntc_resistance >= lookupTable[10])
	{
		temperature = 23;
	}
	else if(ntc_resistance < lookupTable[10] && ntc_resistance >= lookupTable[9])
	{
		temperature = 25;
	}
	else if(ntc_resistance < lookupTable[9] && ntc_resistance >= lookupTable[8])
	{
		temperature = 28;
	}
	else if(ntc_resistance < lookupTable[8] && ntc_resistance >= lookupTable[7])
	{
		temperature = 33;
	}
	else if(ntc_resistance < lookupTable[7] && ntc_resistance >= lookupTable[6])
	{
		temperature = 35;
	}
	else if(ntc_resistance < lookupTable[6] && ntc_resistance >= lookupTable[5])
	{
		temperature = 40;
	}
	else if(ntc_resistance < lookupTable[5] && ntc_resistance >= lookupTable[4])
	{
		temperature = 45;
	}
	else if(ntc_resistance < lookupTable[4] && ntc_resistance >= lookupTable[3])
	{
		temperature = 50;
	}

	else if(ntc_resistance < lookupTable[3] && ntc_resistance >= lookupTable[2])
	{
		temperature = 55;
	}
	else if(ntc_resistance < lookupTable[2] && ntc_resistance >= lookupTable[1])
	{
		temperature = 75;
	}
	else if(ntc_resistance < lookupTable[1] && ntc_resistance >= lookupTable[0])
	{
		temperature = 95;
	}
}

int get_temp(void){
	return temperature;
}
