/*
 * File:   buzzer.h
 *
 * MODULE: header file for buzzer
 *
 * Author: Seifalla Ehab
 */
#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"

/****************************************************************
 * 						Definitions
 ****************************************************************/
#define BUZZER_PORT_ID								PORTC_ID
#define BUZZER_PIN_ID								PIN7_ID

/****************************************************************
 * 					Function Prototypes
 ****************************************************************/
/*
 * Description:
 * intializes buzzer direction to output
 */
void Buzzer_init(void);

/*
 * Description:
 * turns on the buzzer
 */
void Buzzer_on(void);

/*
 * Description:
 * turns off the buzzer
 */
void Buzzer_off(void);



#endif /* BUZZER_H_ */
