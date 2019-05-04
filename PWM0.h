/*
 * PWM0.h
 *
 *  Created on: 16 mar. 2019
 *      Author: josefe
 */

#ifndef PWM0_H_
#define PWM0_H_

#include <avr/io.h>

#define PWM0_CHANNEL_A 0
#define PWM0_CHANNEL_B 1

#define PWM0_PHASECORRECT_8BIT 1
#define PWM0_PHASECORRECT_OCR0A 11 //may 5

#define PWM0_FASTPWM_8BIT 5 //may 3
#define PWM0_FASTPWM_OCR0A 15 // may 7

#define TIMER0_STOPPPED 0x00
#define TIMER0_NOPRESCALER 0x01
#define TIMER0_PRESCALER_8 0x02
#define TIMER0_PRESCALER_64 0x03
#define TIMER0_PRESCALER_256 0x04
#define TIMER0_PRESCALER_1024 0X05
#define TIMER0_EXTERNALCLOCK_FALLING 0x06
#define TIMER0_EXTERNALCLOCK_RISING 0x07

#define PWM0_WAVEFORMMODE_DISABLED 0x00
#define PWM0_WAVEFORMMODE_CH_A_50_DUTY 0x01
#define PWM0_WAVEFORMMODE_NORMAL 0x02
#define PWM0_WAVEFORMMODE_INVERTED 0X03

#define PWM0_OC0A_PIN_BIT 6
#define PWM0_OC0A_PIN_PORT PORTD
#define PWM0_OC0A_PIN_DDR DDRD

#define PWM0_OC0B_PIN_BIT 5
#define PWM0_OC0B_PIN_PORT PORTD
#define PWM0_OC0B_PIN_DDR DDRD

void pwm0_begin(uint8_t PWMmode, uint8_t prescaler, uint8_t top);
void pwm0_configurePin(uint8_t channel, uint8_t waveformMode, uint8_t dutyCycle);
void pwm0_setDuty(uint8_t channel, uint8_t dutyCycle);
void pwm0_end(void);

#endif /* PWM0_H_ */
