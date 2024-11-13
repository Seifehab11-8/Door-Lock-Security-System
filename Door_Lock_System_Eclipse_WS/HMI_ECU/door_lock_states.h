/*
 * 	Description: This file contains all special characters sent between both controllers
 *
 *  Created on: Nov 1, 2024
 *
 *  Author: Seifalla Ehab
 */

#ifndef DOOR_LOCK_STATES_H_
#define DOOR_LOCK_STATES_H_

/*****************************************************
 * 					Definitions
 *****************************************************/

#define UART_SYNC_CHAR			'A'
#define CHANGE_PASSWORD_ID		'-'
#define DOOR_OPEN_ID			'+'
/*******************************************
 * 			UART comm keys:
 * 'F': false password
 * 'T': correct password
 * 'O': opening door
 * 'S': people passing through the door
 * 'C': closing door
 * 'W': System shutdown warning
 * 'K': System reboot
 *******************************************/
#define FALSE_PASSCODE_ID		'F'
#define CORRECT_PASSCODE_ID		'T'
#define OPEN_DOOR_STATE_ID		'O'
#define PEOPLE_PASS_THROUGH_ID	'S'
#define CLOSE_DOOR_STATE_ID		'C'
#define OPEN_CLOSE_DOOR_DONE	'D'
#define SYSTEM_NOK_ID			'W'
#define SYSTEM_OK_ID			'K'

#endif /* DOOR_LOCK_STATES_H_ */
