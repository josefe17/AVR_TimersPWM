/*
 * PWM1.h
 *
 * Created: 03/03/2019 10:26:25
 *  Author: josefe
 */ 


#ifndef PWM1_H_
#define PWM1_H_

#include <avr/io.h>

#define PWM1_CHANNEL_A 0
#define PWM1_CHANNEL_B 1

#define PWM1_PHASECORRECT_8BIT 1
#define PWM1_PHASECORRECT_9BIT 2
#define PWM1_PHASECORRECT_10BIT 3
#define PWM1_PHASECORRECT_ICR1 10
#define PWM1_PHASECORRECT_OCR1A 11

#define PWM1_FASTPWM_8BIT 5
#define PWM1_FASTPWM_9BIT 6
#define PWM1_FASTPWM_10BIT 7
#define PWM1_FASTPWM_ICR1 14
#define PWM1_FASTPWM_OCR1A 15

#define PWM1_PHASE_FREQUENCYCORRECT_ICR1 8
#define PWM1_PHASE_FREQUENCYCORRECT_OCR1A 9

#define TIMER1_STOPPPED 0x00
#define TIMER1_NOPRESCALER 0x01
#define TIMER1_PRESCALER_8 0x02
#define TIMER1_PRESCALER_64 0x03
#define TIMER1_PRESCALER_256 0x04
#define TIMER1_PRESCALER_1024 0X05
#define TIMER1_EXTERNALCLOCK_FALLING 0x06
#define TIMER1_EXTERNALCLOCK_RISING 0x07

#define PWM1_WAVEFORMMODE_DISABLED 0x00
#define PWM1_WAVEFORMMODE_NORMAL 0x02
#define PWM1_WAVEFORMMODE_INVERTED 0X03
#define PWM1_WAVEFORMMODE_CH_A_50_DUTY 0x01

#define PWM1_OC1A_PIN_BIT 1
#define PWM1_OC1A_PIN_PORT PORTB
#define PWM1_OC1A_PIN_DDR DDRB

#define PWM1_OC1B_PIN_BIT 2
#define PWM1_OC1B_PIN_PORT PORTB
#define PWM1_OC1B_PIN_DDR DDRB

void pwm1_begin(uint8_t PWMmode, uint8_t prescaler, uint16_t top);
void pwm1_configurePin(uint8_t channel, uint8_t waveformMode, uint16_t dutyCycle);
void pwm1_setDuty(uint8_t channel, uint16_t dutyCycle);
void pwm1_end(void);

#endif /* PWM1_H_ */
