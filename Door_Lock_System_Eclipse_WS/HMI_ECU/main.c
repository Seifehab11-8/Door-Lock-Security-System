/*
 ================================================================================================
 Name        : HMI ECU Main Source
 Author      : Seifalla Ehab
 Description : HMI ECU main logic implementation
 Date        : 31/10/2024
 ================================================================================================
 */

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "timer.h"
#include "door_lock_states.h"

#define MAX_NUM_OF_ATTEMPTS		3
#define PASSWORD_MAX_SIZE       5
#define NUM_OF_CTC_PER_15_SEC		15
#define NUM_OF_CTC_PER_MIN			60

void timer_callBack_motorOP(void);
void timer_callBack_systemNOK_OP(void);
void read_send_password(void);
void new_password_task(void);

uint8 system_ticks = 0, is_timer_finished = FALSE;
uint8 motor_ticks = 0, is_door_open = FALSE, password_size = 0;

int main(void) {
	uint8 keypad_pressedKey_value, is_password_correct = FALSE_PASSCODE_ID, num_of_attempts = 0, current_state;
	/*************************************************
	 * 				Intialization Stage
	 *************************************************/
	/*
	 * initializing MCAL layer components
	 */
	UART_ConfigType uart_config = {DATA_8_BIT, NO_PARITY, UART_1_STOP_BIT, 19200};
	Timer_ConfigType timer_config = {0, 7811, TIMER1, F_CLK_PRESCALE_1024, TIMER_COMPARE_MODE};
	UART_init(&uart_config);
	SREG|=(1<<7);/* Global interrupt enable */

	/*
	 * initializing MCAL layer components
	 */
	LCD_init();
	/* Syncing the ECUs */
	UART_sendByte(UART_SYNC_CHAR);
	while(UART_recieveByte() != UART_SYNC_CHAR);
	/* Assigning a password for the system */
	new_password_task();
	while (TRUE) {
		if(is_password_correct == FALSE_PASSCODE_ID)
		{
			if(num_of_attempts == MAX_NUM_OF_ATTEMPTS)
			{
				Timer_init(&timer_config);
				Timer_setCallBack(timer_callBack_systemNOK_OP, TIMER1);

				LCD_clearScreen();
				LCD_displayStringRowColumn(0,1, "System LOCKED");
				LCD_displayStringRowColumn(1,0, "wait for 1 min");

				while(is_timer_finished == FALSE){}
				is_timer_finished = FALSE;
				num_of_attempts = 0;
				Timer_deInit(TIMER1);
				/* system ok send */
			}

			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"+ : OPEN DOOR");
			LCD_displayStringRowColumn(1,0,"- : CHANGE PASS");
			do
			{
				keypad_pressedKey_value = KEYPAD_getPressedKey();
				_delay_ms(400); /* pressed key latency */
			}while((keypad_pressedKey_value != DOOR_OPEN_ID) && (keypad_pressedKey_value != CHANGE_PASSWORD_ID));

			do{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0, "Plz enter old");
				LCD_displayStringRowColumn(1,0, "pass :");
				read_send_password();
				is_password_correct = UART_recieveByte();
				num_of_attempts++;
				if(num_of_attempts >= MAX_NUM_OF_ATTEMPTS)
				{
					UART_sendByte(SYSTEM_NOK_ID);
				}
				else{
					UART_sendByte(SYSTEM_OK_ID);
				}
			}while(num_of_attempts < MAX_NUM_OF_ATTEMPTS && is_password_correct != CORRECT_PASSCODE_ID);
		}
		else if(is_password_correct == CORRECT_PASSCODE_ID)
		{
			is_password_correct = FALSE_PASSCODE_ID;
			num_of_attempts = 0;
			UART_sendByte(keypad_pressedKey_value);
			if(keypad_pressedKey_value == DOOR_OPEN_ID)
			{
				LCD_clearScreen();
				Timer_init(&timer_config);
				Timer_setCallBack(timer_callBack_motorOP, TIMER1);
				LCD_displayStringRowColumn(0,1,"Door Unlocking");
				LCD_displayStringRowColumn(1,4,"Please wait");
				while(is_door_open == FALSE){}
				Timer_deInit(TIMER1); /* deactivating until further updates */

				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"wait for people");
				LCD_displayStringRowColumn(1,3,"To Enter");
				do
				{
					current_state = UART_recieveByte();
				}while(current_state == PEOPLE_PASS_THROUGH_ID);

				Timer_init(&timer_config);
				Timer_setCallBack(timer_callBack_motorOP, TIMER1);
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,2,"Door Locking");
				while(is_door_open == TRUE){}
				Timer_deInit(TIMER1); /* deactivating until further updates */
			}
			else if(keypad_pressedKey_value == CHANGE_PASSWORD_ID)
			{
				new_password_task();
			}
		}

	}

	return 0;
}

void timer_callBack_motorOP(void)
{
	motor_ticks++;
	if(motor_ticks == NUM_OF_CTC_PER_15_SEC)
	{
		/*
		 * if door is opened close it and viceversa
		 */
		if(is_door_open == TRUE)
		{
			is_door_open = FALSE;
		}
		else
		{
			is_door_open = TRUE;
		}
		motor_ticks = 0;
	}
}

void timer_callBack_systemNOK_OP(void)
{
	system_ticks++;
	if(system_ticks == NUM_OF_CTC_PER_MIN)
	{
		system_ticks = 0;
		is_timer_finished = TRUE;
	}
}



void read_send_password(void)
{
	uint8 password[7], keypad_pressedKey_value, password_index = 0;
	for(;;)
	{
		keypad_pressedKey_value = KEYPAD_getPressedKey();
		_delay_ms(400); /* delay for the press duration */
		if(keypad_pressedKey_value == '=')
		{
			break;
		}

		if(password_index < PASSWORD_MAX_SIZE)
		{
			password[password_index++] = keypad_pressedKey_value+ 48;
			LCD_displayCharacter('*');
		}
	}
	password[password_index] = UART_RX_STRING_BREAK;
	password[password_index+1] = '\0';

	UART_sendString(password);
}
void new_password_task(void)
{
	do{
		LCD_clearScreen();
		LCD_displayString("Plz enter pass:");
		LCD_moveCursor(1,0);

		read_send_password();

		LCD_clearScreen();

		LCD_displayStringRowColumn(0,0, "Plz re-enter the");
		LCD_displayStringRowColumn(1,0, "same pass: ");

		read_send_password();

		LCD_clearScreen();
	}while(UART_recieveByte() != CORRECT_PASSCODE_ID);
}

