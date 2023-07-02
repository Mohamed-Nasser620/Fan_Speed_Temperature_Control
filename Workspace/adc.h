/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Author: Mohamed Nasser
 *
 * Date Created: Oct 1, 2022
 *
 * Description: Header file for the ATmega32 ADC peripheral driver
 *
 *******************************************************************************/


#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Parameters Definitions */
#define ADC_VOLTAGE_REFERENCE                    2.56
#define ADC_MAX_DIGITAL_VALUE                    1023

/*******************************************************************************
 *                               Enumerations                                  *
 *******************************************************************************/
typedef enum{
	AREF, AVCC, INTERNAL = 3
} ADC_ReferenceVolatge;


typedef enum{
	FCPU_2 = 1, FCPU_4, FCPU_8, FCPU_16, FCPU_32, FCPU_64, FCPU_128
} ADC_Prescaler;

/*******************************************************************************
 *                      Structures And Unions                                  *
 *******************************************************************************/
typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
} ADC_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC peripheral.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel (uint8 channelNum);

/*
 * Description :
 * Function responsible for de-initialize the ADC peripheral.
 */
void ADC_deinit (void);

#endif /* ADC_H_ */
