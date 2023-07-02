/******************************************************************************
 *
 * Module: LM_35
 *
 * File Name: lm_35.c
 *
 * Author: Mohamed Nasser
 *
 * Date Created: Oct 5, 2022
 *
 * Description: Source file for the LM35 Temperature Sensor module driver
 *
 *******************************************************************************/

#include "lm_35.h"
#include "std_types.h"
#include "adc.h"

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM_35_readTemp (void)
{
	uint16 digitalRead = 0;
	uint8 temp = 0;

	/* Read ADC channel where the temperature sensor is connected */
	digitalRead =  ADC_readChannel (LM_35_SENSOR_CHANNEL);

	/* Calculate the temperature from the ADC value */
	temp =(uint8)((LM_35_MAX_TEMPERATURE * (uint32)digitalRead * ADC_VOLTAGE_REFERENCE) \
			/ (ADC_MAX_DIGITAL_VALUE * LM_35_MAX_VOLTAGE));
	return temp;
}
