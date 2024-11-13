 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Seif Ehab
 *
 *******************************************************************************/
#include "gpio.h"
#include "common_macros.h"

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will return Error Status.
 */
GPIO_ErrorStatus GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
	GPIO_ErrorStatus gpio_error_enumState = GPIO_OK;
	if((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT))
	{
		gpio_error_enumState = GPIO_NOK;
	}
	else
	{
		switch (port_num)
		{
		case PORTA_ID:
			(direction == PIN_OUTPUT) ? SET_BIT(GPIO_PORTA_DIR_R, pin_num) : CLEAR_BIT(GPIO_PORTA_DIR_R, pin_num);
			break;
		case PORTB_ID:
			(direction == PIN_OUTPUT) ? SET_BIT(GPIO_PORTB_DIR_R, pin_num) : CLEAR_BIT(GPIO_PORTB_DIR_R, pin_num);
			break;
		case PORTC_ID:
			(direction == PIN_OUTPUT) ? SET_BIT(GPIO_PORTC_DIR_R, pin_num) : CLEAR_BIT(GPIO_PORTC_DIR_R, pin_num);
			break;
		case PORTD_ID:
			(direction == PIN_OUTPUT) ? SET_BIT(GPIO_PORTD_DIR_R, pin_num) : CLEAR_BIT(GPIO_PORTD_DIR_R, pin_num);
			break;
		}
	}
	return gpio_error_enumState;
}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will return Error Status.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
GPIO_ErrorStatus GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	GPIO_ErrorStatus gpio_error_enumState = GPIO_OK;
	if((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT))
	{
		gpio_error_enumState = GPIO_NOK;
	}
	else
	{
		switch (port_num)
		{
		case PORTA_ID:
			(value == LOGIC_HIGH) ? SET_BIT(GPIO_PORTA_DATA_R, pin_num) : CLEAR_BIT(GPIO_PORTA_DATA_R, pin_num);
			break;
		case PORTB_ID:
			(value == LOGIC_HIGH) ? SET_BIT(GPIO_PORTB_DATA_R, pin_num) : CLEAR_BIT(GPIO_PORTB_DATA_R, pin_num);
			break;
		case PORTC_ID:
			(value == LOGIC_HIGH) ? SET_BIT(GPIO_PORTC_DATA_R, pin_num) : CLEAR_BIT(GPIO_PORTC_DATA_R, pin_num);
			break;
		case PORTD_ID:
			(value == LOGIC_HIGH) ? SET_BIT(GPIO_PORTD_DATA_R, pin_num) : CLEAR_BIT(GPIO_PORTD_DATA_R, pin_num);
			break;
		}
	}
	return gpio_error_enumState;
}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Error Status.
 */
GPIO_ErrorStatus GPIO_readPin(uint8 port_num, uint8 pin_num, uint8* pin_value)
{
	GPIO_ErrorStatus gpio_error_enumState = GPIO_OK;
	if((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT))
	{
		gpio_error_enumState = GPIO_NOK;
	}
	else
	{
		switch (port_num)
		{
		case PORTA_ID:
			(*pin_value) = BIT_IS_SET(GPIO_PORTA_STATS_R, pin_num) ? LOGIC_HIGH : LOGIC_LOW;
			break;
		case PORTB_ID:
			(*pin_value) = BIT_IS_SET(GPIO_PORTB_STATS_R, pin_num) ? LOGIC_HIGH : LOGIC_LOW;
			break;
		case PORTC_ID:
			(*pin_value) = BIT_IS_SET(GPIO_PORTC_STATS_R, pin_num) ? LOGIC_HIGH : LOGIC_LOW;
			break;
		case PORTD_ID:
			(*pin_value) = BIT_IS_SET(GPIO_PORTD_STATS_R, pin_num) ? LOGIC_HIGH : LOGIC_LOW;
			break;
		}
	}
	return gpio_error_enumState;
}

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will return Error.
 */
GPIO_ErrorStatus GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	GPIO_ErrorStatus gpio_error_enumState = GPIO_OK;
	if((port_num >= NUM_OF_PORTS))
	{
		gpio_error_enumState = GPIO_NOK;
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			GPIO_PORTA_DIR_R = direction;
			break;
		case PORTB_ID:
			GPIO_PORTB_DIR_R = direction;
			break;
		case PORTC_ID:
			GPIO_PORTC_DIR_R = direction;
			break;
		case PORTD_ID:
			GPIO_PORTD_DIR_R = direction;
			break;
		}
	}
	return gpio_error_enumState;
}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will return Error.
 */
GPIO_ErrorStatus GPIO_writePort(uint8 port_num, uint8 value)
{
	GPIO_ErrorStatus gpio_error_enumState = GPIO_OK;
	if((port_num >= NUM_OF_PORTS))
	{
		gpio_error_enumState = GPIO_NOK;
	}
	else
	{
		switch (port_num)
		{
		case PORTA_ID:
			GPIO_PORTA_DATA_R = value;
			break;
		case PORTB_ID:
			GPIO_PORTB_DATA_R = value;
			break;
		case PORTC_ID:
			GPIO_PORTC_DATA_R = value;
			break;
		case PORTD_ID:
			GPIO_PORTD_DATA_R = value;
			break;
		}
	}
	return gpio_error_enumState;
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return Error.
 */
GPIO_ErrorStatus GPIO_readPort(uint8 port_num, uint8* port_value)
{
	GPIO_ErrorStatus gpio_error_enumState = GPIO_OK;
	if((port_num >= NUM_OF_PORTS))
	{
		gpio_error_enumState = GPIO_NOK;
	}
	else
	{
		switch (port_num)
		{
		case PORTA_ID:
			(*port_value) = GPIO_PORTA_STATS_R;
			break;
		case PORTB_ID:
			(*port_value) = GPIO_PORTB_STATS_R;
			break;
		case PORTC_ID:
			(*port_value) = GPIO_PORTC_STATS_R;
			break;
		case PORTD_ID:
			(*port_value) = GPIO_PORTD_STATS_R;
			break;
		}
	}
	return gpio_error_enumState;
}



