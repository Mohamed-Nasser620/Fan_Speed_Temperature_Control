/******************************************************************************
 *
 * Module: LM_35
 *
 * File Name: lm_35.h
 *
 * Author: Mohamed Nasser
 *
 * Date Created: Oct 5, 2022
 *
 * Description: Header file for the LM35 Temperature Sensor module driver
 *
 *******************************************************************************/
#ifndef LM_35_H_
#define LM_35_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Static Configurations */
#define LM_35_SENSOR_CHANNEL                     2

/* Parameters Definitions */
#define LM_35_MAX_TEMPERATURE                    150
#define LM_35_MAX_VOLTAGE                        1.5

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM_35_readTemp (void);

#endif /* LM_35_H_ */
