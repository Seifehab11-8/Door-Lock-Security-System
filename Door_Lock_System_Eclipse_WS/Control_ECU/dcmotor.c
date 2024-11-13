/*
 * 	File: dcmotor.c
 *
 *  Module: source file for DC Motor Control
 *
 *  Author: Seifalla Ehab
 */
#include "dcmotor.h"
#include "pwm.h"
#include "gpio.h"
#include "common_macros.h"

/*
 * Description:
 * Initializes the DC motor pins
 */
void DcMotor_Init(void)
{
	/*
	 * Motor pins init
	 */
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_INT1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_INT2_PIN_ID, PIN_OUTPUT);
	/*
	 * Motor Stop configuration
	 */
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INT1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INT2_PIN_ID, LOGIC_LOW);
}

/*
 * Description:
 * Control motor speed and adjust motor state
 */
void DcMotor_Rotate(DcMotor_State dcMotor_state, uint8 dcMotor_speed)
{
	switch(dcMotor_state)
	{
	case STOP:
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INT1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INT2_PIN_ID, LOGIC_LOW);
		break;
	case ACW:
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INT1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INT2_PIN_ID, LOGIC_LOW);
		break;
	case CW:
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INT1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INT2_PIN_ID, LOGIC_HIGH);
		break;
	}
	PWM_Timer0_Start(dcMotor_speed);
}
