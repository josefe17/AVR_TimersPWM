/*
 * PWM2.c
 *
 *  Created on: 16 mar. 2019
 *      Author: josefe
 */

#include <avr/io.h>
#include "PWM2.h"

void pwm2_begin(uint8_t PWMmode, uint8_t prescaler, uint8_t top)
{
		switch (PWMmode)
		{
			case PWM2_PHASECORRECT_8BIT:
			{
				TCCR2A = (TCCR2A & ((1<<COM2A1) | (1<<COM2A0) | (1<<COM2B1) | (1<<COM2B0))) | (1<<WGM20);
				TCCR2B = (TCCR2B & (~(1<<WGM22)));
				break;
			}
			case PWM2_PHASECORRECT_OCR2A:
			{
				TCCR2A = (TCCR2A & ((1<<COM2A1) | (1<<COM2A0) | (1<<COM2B1) | (1<<COM2B0))) | (1<<WGM20);
				TCCR2B = (TCCR2B & (~(1<<WGM22))) | (1<<WGM22);
				break;
			}
			case PWM2_FASTPWM_8BIT:
			{
				TCCR2A = (TCCR2A & ((1<<COM2A1) | (1<<COM2A0) | (1<<COM2B1) | (1<<COM2B0))) | (1<<WGM21) | (1<<WGM20);
				TCCR2B = (TCCR2B & (~(1<<WGM22)));
				break;
			}

			case PWM2_FASTPWM_OCR2A:
			{
				TCCR2A = (TCCR2A & ((1<<COM2A1) | (1<<COM2A0) | (1<<COM2B1) | (1<<COM2B0))) | (1<<WGM21) | (1<<WGM20);
				TCCR2B = (TCCR2B & (~(1<<WGM22))) | (1<<WGM22);
				break;
			}
			default:
			{
				break;
			}
		}
		//Prescaler setting
		TCNT2=0;
		TCCR2B = (TCCR2B & (~((1<<CS22) | (1<<CS21) | (1<<CS20)))) | (prescaler & ((1<<CS22) | (1<<CS21) | (1<<CS20)));
		//Top setting
		if((PWMmode == PWM2_PHASECORRECT_OCR2A) || (PWMmode == PWM2_FASTPWM_OCR2A))
		{
			OCR2A=top; // On zero update
		}
}

void pwm2_configurePin(uint8_t channel, uint8_t waveformMode, uint8_t dutyCycle)
{
	switch (channel)
	{
		case PWM2_CHANNEL_A:
		{
			switch (waveformMode)
			{
				case PWM2_WAVEFORMMODE_DISABLED:
				{
					TCCR2A &= ~((1<<COM2A1) | (1<<COM2A0));
					break;
				}
				case PWM2_WAVEFORMMODE_NORMAL:
				{
					PWM2_OC2A_PIN_DDR|=(1<<PWM2_OC2A_PIN_BIT);
					TCCR2A = (TCCR2A & (~((1<<COM2A1) | (1<<COM2A0)))) | (1<<COM2A1);
					break;
				}
				case PWM2_WAVEFORMMODE_INVERTED:
				{
					PWM2_OC2A_PIN_DDR|=(1<<PWM2_OC2A_PIN_BIT);
					TCCR2A = (TCCR2A & (~((1<<COM2A1) | (1<<COM2A0)))) | (1<<COM2A1) | (1<<COM2A0);
					break;
				}
				case PWM2_WAVEFORMMODE_CH_A_50_DUTY:
				{
					PWM2_OC2A_PIN_DDR &= ~(1<<PWM2_OC2A_PIN_BIT);
					TCCR2A = (TCCR2A & (~((1<<COM2A1) | (1<<COM2A0)))) | (1<<COM2A0);
					break;
				}
				default:
				{
					break;
				}
			}
			OCR2A=dutyCycle;
			break;
		}
		case PWM2_CHANNEL_B:
		{
			switch (waveformMode)
			{
				case PWM2_WAVEFORMMODE_DISABLED:
				{
					TCCR2A &= ~((1<<COM2B1) | (1<<COM2B0));
					break;
				}
				case PWM2_WAVEFORMMODE_NORMAL:
				{
					PWM2_OC2B_PIN_DDR|=(1<<PWM2_OC2B_PIN_BIT);
					TCCR2A = (TCCR2A & (~((1<<COM2B1) | (1<<COM2B0)))) | (1<<COM2B1);
					break;
				}
				case PWM2_WAVEFORMMODE_INVERTED:
				{
					PWM2_OC2B_PIN_DDR|=(1<<PWM2_OC2B_PIN_BIT);
					TCCR2A = (TCCR2A & (~((1<<COM2B1) | (1<<COM2B0)))) | (1<<COM2B1) | (1<<COM2B0);
					break;
				}
				default:
				{
					break;
				}
			}
			OCR2B=dutyCycle;
			break;
		}
		default:
		{
			break;
		}
	}
}

void pwm2_setDuty(uint8_t channel, uint8_t dutyCycle)
{
	if (channel==PWM2_CHANNEL_A && !((TCCR2A & (1<<WGM20)) && (TCCR2B & (1<<WGM22)))) // If PWM OCRA top mode enable, pin 1 cannot work as pwm
	{
		OCR2A = dutyCycle;
	}
	if(channel==PWM2_CHANNEL_B)
	{
		OCR2B=dutyCycle;
	}
}

void pwm2_end(void)
{
	TCCR2B=0;
	TCCR2A=0;
	TCNT2=0;
	PWM2_OC2A_PIN_DDR &= ~(1<<PWM2_OC2A_PIN_BIT);
	PWM2_OC2B_PIN_DDR &= ~(1<<PWM2_OC2B_PIN_BIT);
}


