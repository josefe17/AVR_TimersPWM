/*
 * PWM2.h
 *
 *  Created on: 16 mar. 2019
 *      Author: josefe
 */

#ifndef PWM2_H_
#define PWM2_H_

#include <avr/io.h>

#define PWM2_CHANNEL_A 0
#define PWM2_CHANNEL_B 1

#define PWM2_PHASECORRECT_8BIT 1
#define PWM2_PHASECORRECT_OCR2A 11 //may 5

#define PWM2_FASTPWM_8BIT 5 //may 3
#define PWM2_FASTPWM_OCR2A 15 // may 7

#define TIMER2_STOPPPED 0x00
#define TIMER2_NOPRESCALER 0x01
#define TIMER2_PRESCALER_8 0x02
#define TIMER2_PRESCALER_64 0x03
#define TIMER2_PRESCALER_256 0x04
#define TIMER2_PRESCALER_1024 0X05
#define TIMER2_EXTERNALCLOCK_FALLING 0x06
#define TIMER2_EXTERNALCLOCK_RISING 0x07

#define PWM2_WAVEFORMMODE_DISABLED 0x00
#define PWM2_WAVEFORMMODE_CH_A_50_DUTY 0x01
#define PWM2_WAVEFORMMODE_NORMAL 0x02
#define PWM2_WAVEFORMMODE_INVERTED 0X03

#define PWM2_OC2A_PIN_BIT 3
#define PWM2_OC2A_PIN_PORT PORTB
#define PWM2_OC2A_PIN_DDR DDRB

#define PWM2_OC2B_PIN_BIT 3
#define PWM2_OC2B_PIN_PORT PORTD
#define PWM2_OC2B_PIN_DDR DDRD

void pwm2_begin(uint8_t PWMmode, uint8_t prescaler, uint8_t top);
void pwm2_configurePin(uint8_t channel, uint8_t waveformMode, uint8_t dutyCycle);
void pwm2_setDuty(uint8_t channel, uint8_t dutyCycle);
void pwm2_end(void);

#endif /* PWM2_H_ */
