/* 
 * File:   pwm.h
 * 
 * MODULE: generate signals with different duty cycles
 * 
 * Author: Seifalla Ehab
 */

#ifndef PWM_H
#define	PWM_H

#include "std_types.h"

/*******************************************************
 *                        Types
 *******************************************************/
typedef struct{
    uint8 Clk_select_bits           :3;
    uint8 WGM01_bit                 :1;
    uint8 COM_bits                  :2;
    uint8 WGM00_bit                 :1;
    uint8 FOC_bit                   :1;
}Timer0_TCCR;

typedef union{
    uint8 byte;
    Timer0_TCCR timer0_tccr;
}Timer0_TCCR_union;

/*******************************************************
 *                     Definitions
 *******************************************************/
#define TIMER0_START_COUNT_VALUE                                        0u
/*
 * Timer setup definitions
 */
#define TIMER0_FAST_PWM_OCR_NON_INVERTING                               0x02

/*
 * Prescaler for the timer input
 */
#define TIMER0_OFF                                                      0x00
#define TIMER0_NO_PRESCALE                                              0x01
#define TIMER0_PRESCALE_8                                               0x02
#define TIMER0_PRESCALE_64                                              0x03
#define TIMER0_PRESCALE_256                                             0x04
#define TIMER0_PRESCALE_1024                                            0x05

#define TIMER0_PRESCALE_SELECT                                          TIMER0_PRESCALE_64

/*
 * Duty Cycle Values
 */
#define TIMER0_DUTYCYCLE_0                                              0u
#define TIMER0_DUTYCYCLE_25                                             63u
#define TIMER0_DUTYCYCLE_50                                             127u
#define TIMER0_DUTYCYCLE_75                                             191u
#define TIMER0_DUTYCYCLE_100                                            255u

/*
 * count up register size
 */
#define TIMER0_COUNT_REG_SIZE                                           0xFF

/*
 * Register initialization 
 */
#define TIMER0_TCCR_REG (*((volatile Timer0_TCCR_union*)0x0053))
/*
 * OCR ID to digital output
 */

#define TIMER0_OCR0_PORT_ID												PORTB_ID
#define TIMER0_OCR0_PIN_ID												PIN3_ID

/*******************************************************
 *                  Function prototype
 *******************************************************/

/*
 * Description: starts and sets PWM wave
 */
void PWM_Timer0_Start(uint8 pwm_duty_cycle);

#endif	/* PWM_H */

