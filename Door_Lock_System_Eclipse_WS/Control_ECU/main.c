/*
 ================================================================================================
 Name        : Control ECU Main Source
 Author      : Seifalla Ehab
 Description : Control ECU main logic implementation
 Date        : 31/10/2024
 ================================================================================================
 */
#include <string.h>
#include "avr/io.h"
#include "util/delay.h"
#include "external_eeprom.h"
#include "pir.h"
#include "dcmotor.h"
#include "buzzer.h"
#include "twi.h"
#include "uart.h"
#include "timer.h"
#include "door_lock_states.h"

#define NUM_OF_CTC_PER_15_SEC		15
#define NUM_OF_CTC_PER_MIN			60
uint8 system_ticks = 0, is_timer_finished = FALSE;
uint8 motor_ticks = 0, is_door_open = FALSE, password_size = 0;

void write_new_password(void);
boolean check_password(uint8* re_password);
void timer_callBack_motorOP(void);
void timer_callBack_systemNOK_OP(void);
int main(void)
{
	uint8 is_login_successful = 0, operator_request = 0;
	uint8 login_attempt[6];
	/*************************************************
	 * 				Intialization Stage
	 *************************************************/

	/*
	 * initializing MCAL layer components
	 */
	TWI_ConfigType twi_config = {0x01, 400000};
	UART_ConfigType uart_config = {DATA_8_BIT, NO_PARITY, UART_1_STOP_BIT, 19200};
	Timer_ConfigType timer_config = {0, 7811, TIMER1, F_CLK_PRESCALE_1024, TIMER_COMPARE_MODE};
	TWI_init(&twi_config);
	UART_init(&uart_config);
	SREG|=(1<<7);/* Global interrupt enable */
	/*
	 * initializing HAL layer components
	 */
	PIR_init();
	DcMotor_Init();
	Buzzer_init();

	/* Syncing the ECUs */
	UART_sendByte(UART_SYNC_CHAR);
	while(UART_recieveByte() != UART_SYNC_CHAR);

	write_new_password();

	while(TRUE)
	{

		UART_receiveString(login_attempt);
		is_login_successful = check_password(login_attempt);
		if(is_login_successful == TRUE)
		{
			UART_sendByte(CORRECT_PASSCODE_ID); /* telling the HMI ECU that the password is correct */
			UART_recieveByte();/* stores redundant system ok status */
			operator_request = UART_recieveByte();
			if(operator_request == DOOR_OPEN_ID)
			{
					Timer_init(&timer_config);
					Timer_setCallBack(timer_callBack_motorOP, TIMER1);
					DcMotor_Rotate(CW, 100); /* Opening the door */
					/* Opening door state */
					while(is_door_open == FALSE){}
					Timer_deInit(TIMER1); /* To stop the counter from counting */
					DcMotor_Rotate(STOP, 0);

					/* People pass through send */
					while(PIR_getState() == LOGIC_HIGH){}
					UART_sendByte(CLOSE_DOOR_STATE_ID);
					/* Turning the timer back on to begin closing the door */
					Timer_init(&timer_config);
					Timer_setCallBack(timer_callBack_motorOP, TIMER1);

					/* Closing door state */
					DcMotor_Rotate(ACW, 100); /* Closing the door */
					while(is_door_open == TRUE){}
					Timer_deInit(TIMER1);/* Closing timer until needed in the future */
					DcMotor_Rotate(STOP, 0);
					/* operation done */
			}
			else if(operator_request == CHANGE_PASSWORD_ID)
			{
				write_new_password();
			}
		}
		else
		{
			UART_sendByte(FALSE_PASSCODE_ID); /* telling the HMI ECU that the password is incorrect */
			if(UART_recieveByte() == SYSTEM_NOK_ID)
			{
				Timer_init(&timer_config);
				Timer_setCallBack(timer_callBack_systemNOK_OP, TIMER1);
				Buzzer_on();

				while(is_timer_finished == FALSE){}
				is_timer_finished = FALSE;
				Buzzer_off();
				Timer_deInit(TIMER1);
			}
		}
	}
	return 0;
}

void write_new_password(void)
{
	uint8 is_password_true = FALSE_PASSCODE_ID;
	//uint8 eeprom_address_index = 0;
	uint8 re_password[6], password[6];
	/*
	 * Checking that the password assignment is correct
	 */
	password_size = 0;
	do
	{
		UART_receiveString(password);
		UART_receiveString(re_password);
		if(!strcmp((char*)re_password, (char*)password))
		{
			is_password_true = CORRECT_PASSCODE_ID;
		}
		UART_sendByte(is_password_true);
	}while(is_password_true == FALSE_PASSCODE_ID);

	/*
	 * Storing the password in the EEPROM
	 */
	/*
	for(eeprom_address_index = 0; password[eeprom_address_index] != '\0'; eeprom_address_index++)
	{
		EEPROM_writeByte((uint16)(0x0200 + eeprom_address_index), password[eeprom_address_index]);
		password_size++;
	}
	*/
	EEPROM_writeByteStream(0x0200, password, &password_size);
}

boolean check_password(uint8* re_password)
{
	uint8 saved_password[6];
	uint8 eeprom_address_index = 0;
	/*
	 * sign-in attempt check for equality between login attempted and password stored in eeprom
	 */
	/* delay to make sure that the password is stored in the eeprom */
	/*
	_delay_ms(50);
	for(eeprom_address_index = 0; eeprom_address_index < password_size; eeprom_address_index++)
	{
		EEPROM_readByte((uint16)(0x0200 + eeprom_address_index), &saved_password[eeprom_address_index]);
	}
	*/

	eeprom_address_index = EEPROM_readByteStream(0x0200, saved_password, password_size);
	saved_password[eeprom_address_index] = '\0';

	return (!strcmp((char*)saved_password, (char*)re_password));
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


