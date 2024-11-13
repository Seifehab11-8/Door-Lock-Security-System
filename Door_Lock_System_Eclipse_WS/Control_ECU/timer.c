/*
 *  File: Source file for Timer Driver
 *
 *  Created on: 28/10/2024
 *
 *  Author: Seifalla Ehab
 */
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"

/*
 * pointer to be assigned in callback function
 * since we can't use compare mode and overflow mode at same time so only 3 pointers are needed
 */
static volatile void(*g_timer0_ptr)(void) = NULL_PTR;
static volatile void(*g_timer1_ptr)(void) = NULL_PTR;
static volatile void(*g_timer2_ptr)(void) = NULL_PTR;

/******************************************************
 * 						ISRs
 ******************************************************/
/*
 * Timer 0 ISRs
 */
ISR(TIMER0_OVF_vect)
{
	if(g_timer0_ptr != NULL_PTR)
	{
		(*g_timer0_ptr)();
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_timer0_ptr != NULL_PTR)
	{
		(*g_timer0_ptr)();
	}
}

/*
 * Timer 1 ISRs
 */
ISR(TIMER1_OVF_vect)
{
	if(g_timer1_ptr != NULL_PTR)
	{
		(*g_timer1_ptr)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_timer1_ptr != NULL_PTR)
	{
		(*g_timer1_ptr)();
	}
}

/*
 * Timer 2 ISRs
 */
ISR(TIMER2_OVF_vect)
{
	if(g_timer2_ptr != NULL_PTR)
	{
		(*g_timer2_ptr)();
	}
}

ISR(TIMER2_COMP_vect)
{
	if(g_timer2_ptr != NULL_PTR)
	{
		(*g_timer2_ptr)();
	}
}
/******************************************************
 * 				Function Definitions
 ******************************************************/

void Timer_init(const Timer_ConfigType* Config_Ptr)
{
	switch(Config_Ptr->timer_ID)
	{
	case TIMER0:
		SET_BIT(TCCR0, FOC0);
		TCNT0 = Config_Ptr->timer_InitialValue;
		if(Config_Ptr->timer_mode == TIMER_COMPARE_MODE)
		{
			SET_BIT(TCCR0, WGM01);
			OCR0 = Config_Ptr->timer_compare_MatchValue;
			SET_BIT(TIMSK, OCIE0);
			CLEAR_BIT(TIMSK, TOIE0);
		}
		else
		{
			SET_BIT(TIMSK, TOIE0);
			CLEAR_BIT(TIMSK, OCIE0);
		}

		if((Config_Ptr->timer_clock) == F_CLK_PRESCALE_32)
		{
			return;
		}
		/*
		 * setting up the interrupt
		 */
		TCCR0 |= (Config_Ptr->timer_clock);
		break;
	case TIMER1:
		TCCR1A = (1<<FOC1A) | (1<<FOC1B);
		TCNT1 = Config_Ptr->timer_InitialValue;
		if(Config_Ptr->timer_mode == TIMER_COMPARE_MODE)
		{
			TCCR1B |= (1<<WGM12);
			OCR1A = Config_Ptr->timer_compare_MatchValue;
			SET_BIT(TIMSK, OCIE1A);
			CLEAR_BIT(TIMSK, TOIE1);
		}
		else
		{
			SET_BIT(TIMSK, TOIE1);
			CLEAR_BIT(TIMSK, OCIE1A);
		}

		if((Config_Ptr->timer_clock) == F_CLK_PRESCALE_32)
		{
			return;
		}
		/*
		 * setting up the interrupt
		 */
		TCCR1B |= Config_Ptr->timer_clock;
		break;
	case TIMER2:
		SET_BIT(TCCR2, FOC2);
		TCNT2 = Config_Ptr->timer_InitialValue;
		/*
		 * setting up the interrupt
		 */
		if(Config_Ptr->timer_mode == TIMER_COMPARE_MODE)
		{
			SET_BIT(TCCR2, WGM21);
			OCR2 = Config_Ptr->timer_compare_MatchValue;
			SET_BIT(TIMSK, OCIE2);
			CLEAR_BIT(TIMSK, TOIE2);
		}
		else
		{
			SET_BIT(TIMSK, TOIE2);
			CLEAR_BIT(TIMSK, OCIE2);
		}


		switch(Config_Ptr->timer_clock)
		{
		case F_CLK_PRESCALE_1:
			TCCR2 |= TIMER2_CLK_PRESCALE_1;
			break;
		case F_CLK_PRESCALE_8:
			TCCR2 |= TIMER2_CLK_PRESCALE_8;
			break;
		case F_CLK_PRESCALE_32:
			TCCR2 |= TIMER2_CLK_PRESCALE_32;
			break;
		case F_CLK_PRESCALE_64:
			TCCR2 |= TIMER2_CLK_PRESCALE_64;
			break;
		case F_CLK_PRESCALE_128:
			TCCR2 |= TIMER2_CLK_PRESCALE_128;
			break;
		case F_CLK_PRESCALE_256:
			TCCR2 |= TIMER2_CLK_PRESCALE_256;
			break;
		case F_CLK_PRESCALE_1024:
			TCCR2 |= TIMER2_CLK_PRESCALE_1024;
			break;
		}
		break;
	}
}

void Timer_deInit(Timer_ID_Type timer_ID)
{
	switch(timer_ID)
	{
	case TIMER0:
		TCCR0 = 0;
		CLEAR_BIT(TIMSK, OCIE0);
		CLEAR_BIT(TIMSK, TOIE0);
		break;
	case TIMER1:
		TCCR1A = 0;
		TCCR1B = 0;
		CLEAR_BIT(TIMSK, TOIE1);
		CLEAR_BIT(TIMSK, OCIE1A);
		break;
	case TIMER2:
		TCCR2 = 0;
		CLEAR_BIT(TIMSK, OCIE2);
		CLEAR_BIT(TIMSK, TOIE2);
		break;
	}
}

void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID)
{
	switch(a_timer_ID)
	{
	case TIMER0:
		g_timer0_ptr = a_ptr;
		break;
	case TIMER1:
		g_timer1_ptr = a_ptr;
		break;
	case TIMER2:
		g_timer2_ptr = a_ptr;
		break;
	}
}
