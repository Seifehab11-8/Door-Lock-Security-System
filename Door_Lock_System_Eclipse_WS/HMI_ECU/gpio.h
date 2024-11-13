 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description: Header file for the AVR GPIO driver
 *
 * Author: Seif Ehab
 *
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

/*
 * Description:
 * PORT Addresses are used to write values to output ports and internal pullup for input ports
 */
#define GPIO_PORTA_DATA_R			   (*((volatile uint8*)0x003B))
#define GPIO_PORTB_DATA_R			   (*((volatile uint8*)0x0038))
#define GPIO_PORTC_DATA_R			   (*((volatile uint8*)0x0035))
#define GPIO_PORTD_DATA_R			   (*((volatile uint8*)0x0032))
/*
 * Description:
 * DDR Addresses are used to select port mode
 */
#define GPIO_PORTA_DIR_R			   (*((volatile uint8*)0x003A))
#define GPIO_PORTB_DIR_R			   (*((volatile uint8*)0x0037))
#define GPIO_PORTC_DIR_R			   (*((volatile uint8*)0x0034))
#define GPIO_PORTD_DIR_R			   (*((volatile uint8*)0x0031))
/*
 * Description:
 * PIN Addresses are used to know the pin value and they are read-only registers
 */
#define GPIO_PORTA_STATS_R			   (*((volatile uint8*const)0x0039))
#define GPIO_PORTB_STATS_R			   (*((volatile uint8*const)0x0036))
#define GPIO_PORTC_STATS_R			   (*((volatile uint8*const)0x0033))
#define GPIO_PORTD_STATS_R			   (*((volatile uint8*const)0x0030))

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	PIN_INPUT = 0,PIN_OUTPUT = 1
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT = 0x00,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/*
 * Description:
 * if an error exist the function will return an error flag which is GPIO_ErrorStatus = 1
 */
typedef enum
{
	GPIO_OK,GPIO_NOK
}GPIO_ErrorStatus;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will return Error Status.
 */
GPIO_ErrorStatus GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will return Error Status.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
GPIO_ErrorStatus GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Error Status.
 */
GPIO_ErrorStatus GPIO_readPin(uint8 port_num, uint8 pin_num, uint8* pin_value);

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will return Error.
 */
GPIO_ErrorStatus GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will return Error.
 */
GPIO_ErrorStatus GPIO_writePort(uint8 port_num, uint8 value);

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return Error.
 */
GPIO_ErrorStatus GPIO_readPort(uint8 port_num, uint8* port_value);

#endif /* GPIO_H_ */
