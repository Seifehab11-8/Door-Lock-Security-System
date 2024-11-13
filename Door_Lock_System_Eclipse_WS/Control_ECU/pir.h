 /******************************************************************************
 *
 * Module: PIR sensor
 *
 * File Name: pir.h
 *
 * Description: Header file for the TWI(I2C) AVR driver
 *
 * Author: Seifalla Ehab Mohamed
 *
 *******************************************************************************/

#ifndef PIR_H_
#define PIR_H_

#include "std_types.h"

/***********************************************
 * 				Definitions
 ***********************************************/
#define PIR_PORT_ID				PORTC_ID
#define PIR_PIN_ID				PIN2_ID

/***********************************************
 * 			Function Prototypes
 ***********************************************/

void PIR_init(void);
uint8 PIR_getState(void);


#endif /* PIR_H_ */
