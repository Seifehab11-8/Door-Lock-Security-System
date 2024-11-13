#include "pwm.h"
#include "gpio.h"
#include "common_macros.h"
#include "avr/io.h"

static void PWM_Timer0_Setup(void)
{
	/*
     * Force output compare is set to zero for PWM mode
     */
    TIMER0_TCCR_REG.timer0_tccr.FOC_bit = LOGIC_LOW;
    /*
     * Selecting generation type
     */
    TIMER0_TCCR_REG.timer0_tccr.WGM00_bit = LOGIC_HIGH;
    TIMER0_TCCR_REG.timer0_tccr.WGM01_bit = LOGIC_HIGH;
    /*
     * Selecting the line that generates the input and its mode (inverting or non inverting)
     */
    TIMER0_TCCR_REG.timer0_tccr.COM_bits = TIMER0_FAST_PWM_OCR_NON_INVERTING;
    /*
     * selecting the clk and its prescale
     */
    TIMER0_TCCR_REG.timer0_tccr.Clk_select_bits = TIMER0_PRESCALE_SELECT;
}

void PWM_Timer0_Start(uint8 pwm_duty_cycle)
{
    /*
     * Selecting timer count start value
     */
    TCNT0 = TIMER0_START_COUNT_VALUE;
    /*
     * Selecting the duty cycle value
     */
    OCR0 = (uint8)((float32)pwm_duty_cycle*2.56 -1);
    /*
	 * Setting OCR to output mode
	 */
	GPIO_setupPinDirection(TIMER0_OCR0_PORT_ID, TIMER0_OCR0_PIN_ID, PIN_OUTPUT);
    /*
     * intial values and data
     */
    PWM_Timer0_Setup();
}
