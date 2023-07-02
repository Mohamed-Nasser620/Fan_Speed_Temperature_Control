/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Author: Mohamed Nasser
 *
 * Date Created: Oct 1, 2022
 *
 * Description: Source file for the ATmega32 ADC peripheral driver
 *
 *******************************************************************************/

#include "adc.h"
#include "common_macros.h"
#include "std_types.h"
#include <avr/io.h>

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC peripheral.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* Puts the input value of Vref in ADMUX register last 2 bits */
	ADMUX = (ADMUX & 0x3F) | (((Config_Ptr -> ref_volt) & 0x03) << 6);

	/* Puts the input value of prescaler in ADCSRA register first 3 bits */
	ADCSRA = (ADCSRA & 0xF8) | ((Config_Ptr -> prescaler) & 0x07);

	SET_BIT (ADCSRA, ADEN);           /* Enables the ADC peripheral */
}

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel (uint8 channelNum)
{
	ADMUX = (ADMUX & 0xE0) | (channelNum & 0x07);   /* Selects the ADC channel and puts it in ADMUX register */
	SET_BIT (ADCSRA, ADSC);  			   		    /* Start the conversion for this channel */
	while (BIT_IS_CLEAR (ADCSRA, ADIF)); 	        /* polling on the flag until the conversion is done */
	SET_BIT (ADCSRA, ADIF);    				        /* Reset the flag by putting logic high */
	return (ADC & 0x03FF);     					    /* Returning the digital value after conversion */
}

/*
 * Description :
 * Function responsible for de-initialize the ADC peripheral.
 */
void ADC_deinit (void)
{
	/* Clear the whole ADC registers */
	ADMUX = 0;
	ADCSRA = 0;

	CLEAR_BIT (ADCSRA, ADEN);                       /* De-enable the ADC peripheral */
}
