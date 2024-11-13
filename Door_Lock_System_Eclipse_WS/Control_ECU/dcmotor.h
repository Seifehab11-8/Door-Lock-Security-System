/*
 * 	File: dcmotor.h
 *
 *  Module: header file for DC Motor Control
 *
 *  Author: Seifalla Ehab
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"
/*************************************************************
 * 						Types
 *************************************************************/
typedef enum{
	STOP,
	ACW,
	CW
}DcMotor_State;

/*************************************************************
 * 					Definitions
 *************************************************************/
/*
 * Motor connections with the MCu
 */
#define DC_MOTOR_PORT_ID									PORTD_ID
#define DC_MOTOR_INT1_PIN_ID								PIN6_ID
#define DC_MOTOR_INT2_PIN_ID								PIN7_ID
/*
 * MOTOR_SPEEDs
 */
#define DC_MOTOR_SPEED_0									0u
#define DC_MOTOR_SPEED_25									25u
#define DC_MOTOR_SPEED_50									50u
#define DC_MOTOR_SPEED_75									75u

/*************************************************************
 * 					Function Prototypes
 *************************************************************/
/*
 * Description:
 * Initializes the DC motor pins
 */
void DcMotor_Init(void);
/*
 * Description:
 * Control motor speed and adjust motor state
 */
void DcMotor_Rotate(DcMotor_State dcMotor_state, uint8 dcMotor_speed);

#endif /* DCMOTOR_H_ */















