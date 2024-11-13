/*
 *  File: header file for UART driver
 *
 *  Created on: Oct 22, 2024
 *
 *  Author: Seifalla Ehab
 */

#ifndef UART_H_
#define UART_H_


#include "std_types.h"

/*******************************************************************************
 *                                Types                                        *
 *******************************************************************************/
typedef enum
{
	NO_PARITY = 0,
	EVEN_PARITY = 2,
	ODD_PARITY = 3
}UART_ParityType;

typedef enum
{
	DATA_5_BIT,
	DATA_6_BIT,
	DATA_7_BIT,
	DATA_8_BIT,
	DATA_9_BIT = 7
}UART_BitDataType;

typedef enum
{
	UART_1_STOP_BIT,
	UART_2_STOP_BIT
}UART_StopBitType;

typedef uint16 UART_BaudRateType;

typedef struct {
	UART_BitDataType bit_data;
	UART_ParityType parity;
	UART_StopBitType stop_bit;
	UART_BaudRateType baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                                Defintions                                   *
 *******************************************************************************/
#define UART_RX_INTERRUPT_ENABLE			1u
#define UART_RX_NORMAL_MODE					0u

#define UART_RX_MODE_SELECT					UART_RX_NORMAL_MODE

#define UART_RX_STRING_BREAK				('#')

#if UART_RX_MODE_SELECT == UART_RX_INTERRUPT_ENABLE
/*
 * Global Variables
 */
extern volatile uint8 g_uart_data;
extern volatile uint8 g_uart_rxc_flag;
#endif
/*******************************************************************************
 *                      	Functions Prototypes                               *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType* Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

#if UART_RX_MODE_SELECT == UART_RX_INTERRUPT_ENABLE
#else
/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #
#endif


#endif /* UART_H_ */
