/*
 *  File: Header file for Timer Driver
 *
 *  Created on: 28/10/2024
 *
 *  Author: Seifalla Ehab
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
/*********************************************************
 * 						Types
 *********************************************************/
typedef enum
{
	TIMER0 = 0,
	TIMER1 = 1,
	TIMER2 = 2
}Timer_ID_Type;

typedef enum
{
	TIMER_OVRFLOW_MODE = 0,
	TIMER_COMPARE_MODE = 2
}Timer_ModeType;

typedef enum
{
	NO_CLOCK,
	F_CLK_PRESCALE_1,
	F_CLK_PRESCALE_8,
	F_CLK_PRESCALE_64,
	F_CLK_PRESCALE_256,
	F_CLK_PRESCALE_1024,
	F_CLK_PRESCALE_32,
	F_CLK_PRESCALE_128
}Timer_ClockType;

typedef struct
{
	uint16 timer_InitialValue;
	uint16 timer_compare_MatchValue;
	Timer_ID_Type timer_ID;
	Timer_ClockType timer_clock;
	Timer_ModeType timer_mode;
}Timer_ConfigType;

/*********************************************************
 * 					Definitions
 *********************************************************/
#define TIMER2_CLK_PRESCALE_1			1u
#define TIMER2_CLK_PRESCALE_8			2u
#define TIMER2_CLK_PRESCALE_32			3u
#define TIMER2_CLK_PRESCALE_64			4u
#define TIMER2_CLK_PRESCALE_128			5u
#define TIMER2_CLK_PRESCALE_256			6u
#define TIMER2_CLK_PRESCALE_1024		7u

/*********************************************************
 * 					Function Prototype
 *********************************************************/
void Timer_init(const Timer_ConfigType* Config_Ptr);
void Timer_deInit(Timer_ID_Type timer_ID);
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID);

#endif /* TIMER_H_ */
