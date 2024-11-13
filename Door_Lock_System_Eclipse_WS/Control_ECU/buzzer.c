/*
 * File:   buzzer.c
 *
 * MODULE: header file for buzzer
 *
 * Author: Seifalla Ehab
 */
#include "gpio.h"
#include "buzzer.h"
/*
 * Description:
 * intializes buzzer direction to output
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
}

/*
 * Description:
 * turns on the buzzer
 */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

/*
 * Description:
 * turns off the buzzer
 */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
