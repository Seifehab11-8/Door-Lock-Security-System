/*
 *  File: header file for UART driver
 *
 *  Created on: Oct 22, 2024
 *
 *  Author: Seifalla Ehab
 */

#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "avr/interrupt.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

#if UART_RX_MODE_SELECT == UART_RX_INTERRUPT_ENABLE
volatile uint8 g_uart_data;
/*
 * global rxc flag is used to identify a recieve success
 * to make the user know that an interrupt occurred
 */
volatile uint8 g_uart_rxc_flag;

ISR(USART_RXC_vect)
{
	g_uart_rxc_flag = UART_recieveByte();
}
#endif
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType* Config_Ptr)
{
	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
#if UART_RX_MODE_SELECT == UART_RX_INTERRUPT_ENABLE
	UCSRB = (1<<RXEN) | (1<<TXEN) | (1<<RXCIE);
#else
	UCSRB = (1<<RXEN) | (1<<TXEN);
#endif


	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1<<URSEL);

	if(Config_Ptr->bit_data == DATA_9_BIT)
	{
		CLEAR_BIT(UCSRC, UCSZ0);
		CLEAR_BIT(UCSRC, UCSZ1);
		CLEAR_BIT(UCSRB, UCSZ2);
		UCSRC |= (((Config_Ptr->bit_data)&0x03) << UCSZ0);
		UCSRB |= ((GET_BIT(Config_Ptr->bit_data,2)) << UCSZ2);
	}
	else
	{
		CLEAR_BIT(UCSRC, UCSZ0);
		CLEAR_BIT(UCSRC, UCSZ1);
		UCSRC |= (((Config_Ptr->bit_data)&0x03) << UCSZ0);
	}

	UCSRC |= (((Config_Ptr->stop_bit)&0x01) << USBS);
	UCSRC |= ((Config_Ptr->parity) << UPM0);

	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
#if UART_RX_MODE_SELECT == UART_RX_INTERRUPT_ENABLE
	g_uart_data = UDR;
	/*
	 * when using interrupt mode the return acts as a flag
	 */
	return TRUE;
#else
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return UDR;
#endif
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
#if UART_RX_MODE_SELECT == UART_RX_INTERRUPT_ENABLE
#else
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != UART_RX_STRING_BREAK)
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
#endif
