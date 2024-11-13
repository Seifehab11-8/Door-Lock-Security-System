 /******************************************************************************
 *
 * Module: PIR sensor
 *
 * File Name: pir.c
 *
 * Description: Source file for the TWI(I2C) AVR driver
 *
 * Author: Seifalla Ehab Mohamed
 *
 *******************************************************************************/
#include "pir.h"
#include "gpio.h"


void PIR_init(void)
{
	GPIO_setupPinDirection(PIR_PORT_ID, PIR_PIN_ID, PIN_INPUT);
}

uint8 PIR_getState(void)
{
	uint8 pir_state_value;
	GPIO_readPin(PIR_PORT_ID, PIR_PIN_ID, &pir_state_value);

	return pir_state_value;
}
