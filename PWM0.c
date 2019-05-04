/*
 * PWM0.c
 *
 *  Created on: 16 mar. 2019
 *      Author: josefe
 */


#include <avr/io.h>
#include "PWM0.h"

void pwm0_begin(uint8_t PWMmode, uint8_t prescaler, uint8_t top)
{
		switch (PWMmode)
		{
			case PWM0_PHASECORRECT_8BIT:
			{
				TCCR0A = (TCCR0A & ((1<<COM0A1) | (1<<COM0A0) | (1<<COM0B1) | (1<<COM0B0))) | (1<<WGM00);
				TCCR0B = (TCCR0B & (~(1<<WGM02)));
				break;
			}
			case PWM0_PHASECORRECT_OCR0A:
			{
				TCCR0A = (TCCR0A & ((1<<COM0A1) | (1<<COM0A0) | (1<<COM0B1) | (1<<COM0B0))) | (1<<WGM00);
				TCCR0B = (TCCR0B & (~(1<<WGM02))) | (1<<WGM02);
				break;
			}
			case PWM0_FASTPWM_8BIT:
			{
				TCCR0A = (TCCR0A & ((1<<COM0A1) | (1<<COM0A0) | (1<<COM0B1) | (1<<COM0B0))) | (1<<WGM01) | (1<<WGM00);
				TCCR0B = (TCCR0B & (~(1<<WGM02)));
				break;
			}

			case PWM0_FASTPWM_OCR0A:
			{
				TCCR0A = (TCCR0A & ((1<<COM0A1) | (1<<COM0A0) | (1<<COM0B1) | (1<<COM0B0))) | (1<<WGM01) | (1<<WGM00);
				TCCR0B = (TCCR0B & (~(1<<WGM02))) | (1<<WGM02);
				break;
			}
			default:
			{
				break;
			}
		}
		//Prescaler setting
		TCNT0=0;
		TCCR0B = (TCCR0B & (~((1<<CS02) | (1<<CS01) | (1<<CS00)))) | (prescaler & ((1<<CS02) | (1<<CS01) | (1<<CS00)));
		//Top setting
		if((PWMmode == PWM0_PHASECORRECT_OCR0A) || (PWMmode == PWM0_FASTPWM_OCR0A))
		{
			OCR0A=top; // On zero update
		}
}

void pwm0_configurePin(uint8_t channel, uint8_t waveformMode, uint8_t dutyCycle)
{
	switch (channel)
	{
		case PWM0_CHANNEL_A:
		{
			switch (waveformMode)
			{
				case PWM0_WAVEFORMMODE_DISABLED:
				{
					TCCR0A &= ~((1<<COM0A1) | (1<<COM0A0));
					break;
				}
				case PWM0_WAVEFORMMODE_NORMAL:
				{
					PWM0_OC0A_PIN_DDR|=(1<<PWM0_OC0A_PIN_BIT);
					TCCR0A = (TCCR0A & (~((1<<COM0A1) | (1<<COM0A0)))) | (1<<COM0A1);
					break;
				}
				case PWM0_WAVEFORMMODE_INVERTED:
				{
					PWM0_OC0A_PIN_DDR|=(1<<PWM0_OC0A_PIN_BIT);
					TCCR0A = (TCCR0A & (~((1<<COM0A1) | (1<<COM0A0)))) | (1<<COM0A1) | (1<<COM0A0);
					break;
				}
				case PWM0_WAVEFORMMODE_CH_A_50_DUTY:
				{
					PWM0_OC0A_PIN_DDR &= ~(1<<PWM0_OC0A_PIN_BIT);
					TCCR0A = (TCCR0A & (~((1<<COM0A1) | (1<<COM0A0)))) | (1<<COM0A0);
					break;
				}
				default:
				{
					break;
				}
			}
			OCR0A=dutyCycle;
			break;
		}
		case PWM0_CHANNEL_B:
		{
			switch (waveformMode)
			{
				case PWM0_WAVEFORMMODE_DISABLED:
				{
					TCCR0A &= ~((1<<COM0B1) | (1<<COM0B0));
					break;
				}
				case PWM0_WAVEFORMMODE_NORMAL:
				{
					PWM0_OC0B_PIN_DDR|=(1<<PWM0_OC0B_PIN_BIT);
					TCCR0A = (TCCR0A & (~((1<<COM0B1) | (1<<COM0B0)))) | (1<<COM0B1);
					break;
				}
				case PWM0_WAVEFORMMODE_INVERTED:
				{
					PWM0_OC0B_PIN_DDR|=(1<<PWM0_OC0B_PIN_BIT);
					TCCR0A = (TCCR0A & (~((1<<COM0B1) | (1<<COM0B0)))) | (1<<COM0B1) | (1<<COM0B0);
					break;
				}
				default:
				{
					break;
				}
			}
			OCR0B=dutyCycle;
			break;
		}
		default:
		{
			break;
		}
	}
}

void pwm0_setDuty(uint8_t channel, uint8_t dutyCycle)
{
	if (channel==PWM0_CHANNEL_A && !((TCCR0A & (1<<WGM00)) && (TCCR0B & (1<<WGM02)))) // If PWM OCRA top mode enable, pin 1 cannot work as pwm
	{
		OCR0A = dutyCycle;
	}
	if(channel==PWM0_CHANNEL_B)
	{
		OCR0B=dutyCycle;
	}
}

void pwm0_end(void)
{
	TCCR0B=0;
	TCCR0A=0;
	TCNT0=0;
	PWM0_OC0A_PIN_DDR &= ~(1<<PWM0_OC0A_PIN_BIT);
	PWM0_OC0B_PIN_DDR &= ~(1<<PWM0_OC0B_PIN_BIT);
}

