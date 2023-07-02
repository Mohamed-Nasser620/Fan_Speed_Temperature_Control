/*
 * project.c
 *
 *  Created on: Oct 6, 2022
 *      Author: Mohamed
 */

#include "std_types.h"
#include "lcd.h"
#include "dc_motor.h"
#include "lm_35.h"
#include "adc.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ON                             1
#define OFF                            0
#define MAX_SPEED                      100
#define THREE_QUARTERS_SPEED           75
#define HALF_SPEED                     50
#define QUARTER_SPEED                  25

/*******************************************************************************
 *                                    Globals                                  *
 *******************************************************************************/
uint8 g_motorState = OFF;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
int main (void)
{
	/* Created as register variable as it will be used too much in the program */
	register uint8 temprature = 0;

	/* ADC initialization Vref and prescaler */
	ADC_ConfigType s_configuration = {INTERNAL, FCPU_8};
	ADC_init (& s_configuration);

	/* Initialize LCD and DC motor modules */
	LCD_init();
	DcMotor_init();

	/* Display the fixed data on LCD */
	LCD_moveCursor (1,3);
	LCD_displayString ("FAN IS ");
	LCD_moveCursor (2,2);
	LCD_displayString ("TEMP =     C");

	for(;;)
	{
		temprature = LM_35_readTemp ();               /* Read the temperature each loop */
		/* Display the temperature on LCD */
		LCD_moveCursor (2,9);
		if (temprature >= 100)
		{
			LCD_displayInteger((sint32)temprature);
		}
		else
		{
			LCD_displayInteger((sint32)temprature);
			LCD_sendData (' ');
		}

		/* Check the temperature value then determine the speed and state of the fan */
		if (temprature >= 120)
		{
			DcMotor_rotate (CW, MAX_SPEED);
			g_motorState = ON;
		}
		else if (temprature >= 90)
		{
			DcMotor_rotate (CW, THREE_QUARTERS_SPEED);
			g_motorState = ON;
		}
		else if (temprature >= 60)
		{
			DcMotor_rotate (CW, HALF_SPEED);
			g_motorState = ON;
		}
		else if (temprature >= 30)
		{
			DcMotor_rotate (CW, QUARTER_SPEED);
			g_motorState = ON;
		}
		else
		{
			DcMotor_stop ();
			g_motorState = OFF;
		}

		/* Display the fan state after determining it */
		switch (g_motorState)
		{
		case ON:
			LCD_moveCursor (1,10);
			LCD_displayString("ON ");
			break;
		case OFF:
			LCD_moveCursor (1,10);
			LCD_displayString("OFF");
		}
	}
}

