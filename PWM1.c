/*
 * PWM1.c
 *
 * Created: 03/03/2019 10:30:46
 *  Author: josefe
 */ 

#include <avr/io.h>
#include "PWM1.h"

void pwm1_begin(uint8_t PWMmode, uint8_t prescaler, uint16_t top)
{
		switch (PWMmode)
		{
			case PWM1_PHASECORRECT_8BIT:
			{
				TCCR1A = (TCCR1A & ((1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0))) | (1<<WGM10);
				break;
			}
			case PWM1_PHASECORRECT_9BIT:
			{				
				TCCR1A = (TCCR1A & ((1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0))) | (1<<WGM11);
				break;
			}
			case PWM1_PHASECORRECT_10BIT:
			{				
				TCCR1A = (TCCR1A & ((1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0))) | (1<<WGM11) | (1<<WGM10) ;
				break;
			}
			case PWM1_PHASECORRECT_ICR1:
			{				
				TCCR1A = (TCCR1A & ((1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0))) | (1<<WGM11);
				TCCR1B = (TCCR1B & ((1<<CS12) | (1<<CS11) | (1<<CS10))) | (1<<WGM13);
				break;
			}
			case PWM1_PHASECORRECT_OCR1A:
			{
				TCCR1A = (TCCR1A & ((1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0))) | (1<<WGM11) | (1<<WGM10);
				TCCR1B = (TCCR1B & ((1<<CS12) | (1<<CS11) | (1<<CS10))) | (1<<WGM13);
				break;	
			}
			case PWM1_FASTPWM_8BIT:
			{
				TCCR1A = (TCCR1A & ((1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0))) | (1<<WGM10);
				TCCR1B = (TCCR1B & ((1<<CS12) | (1<<CS11) | (1<<CS10))) | (1<<WGM12);				
				break;
			}
			case PWM1_FASTPWM_9BIT:
			{
				TCCR1A = (TCCR1A & ((1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0))) | (1<<WGM11);
				TCCR1B = (TCCR1B & ((1<<CS12) | (1<<CS11) | (1<<CS10))) | (1<<WGM12);
				break;
			}
			case PWM1_FASTPWM_10BIT:
			{
				TCCR1A = (TCCR1A & ((1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0))) | (1<<WGM11) | (1<<WGM10);
				TCCR1B = (TCCR1B & ((1<<CS12) | (1<<CS11) | (1<<CS10))) | (1<<WGM12);
				break;
			}
			case PWM1_FASTPWM_ICR1:
			{
				TCCR1A = (TCCR1A & ((1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0))) | (1<<WGM11);
				TCCR1B = (TCCR1B & ((1<<CS12) | (1<<CS11) | (1<<CS10))) | (1<<WGM13) | (1<<WGM12);
				break;
			}
			case PWM1_FASTPWM_OCR1A:
			{
				TCCR1A = (TCCR1A & ((1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0))) | (1<<WGM11) | (1<<WGM10);
				TCCR1B = (TCCR1B & ((1<<CS12) | (1<<CS11) | (1<<CS10))) | (1<<WGM13) | (1<<WGM12);
				break;
			}
			case PWM1_PHASE_FREQUENCYCORRECT_ICR1:
			{
				TCCR1B = (TCCR1B & ((1<<CS12) | (1<<CS11) | (1<<CS10))) | (1<<WGM13);
				break;
			}
			case PWM1_PHASE_FREQUENCYCORRECT_OCR1A:
			{
				TCCR1A = (TCCR1A & ((1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0))) | (1<<WGM10);
				TCCR1B = (TCCR1B & ((1<<CS12) | (1<<CS11) | (1<<CS10))) | (1<<WGM13);
				break;
			}
			default:
			{
				break;
			}
		}
		//Prescaler setting
		TCNT1=0;
		TCCR1B = (TCCR1B & (~((1<<CS12) | (1<<CS11) | (1<<CS10)))) | (prescaler & ((1<<CS12) | (1<<CS11) | (1<<CS10)));
		//Top setting
		if((PWMmode == PWM1_PHASE_FREQUENCYCORRECT_ICR1) || (PWMmode == PWM1_PHASECORRECT_ICR1) || (PWMmode == PWM1_FASTPWM_ICR1))
		{
			ICR1=top; //Instant update
		}
		if((PWMmode == PWM1_PHASE_FREQUENCYCORRECT_OCR1A) || (PWMmode == PWM1_PHASECORRECT_OCR1A) || (PWMmode == PWM1_FASTPWM_OCR1A))
		{
			OCR1A=top; // On zero update
		}
}

void pwm1_configurePin(uint8_t channel, uint8_t waveformMode, uint16_t dutyCycle)
{
	switch (channel)
	{
		case PWM1_CHANNEL_A:
		{
			switch (waveformMode)
			{
				case PWM1_WAVEFORMMODE_DISABLED:
				{
					TCCR1A &= ~((1<<COM1A1) | (1<<COM1A0));
					break;
				}	
				case PWM1_WAVEFORMMODE_NORMAL:
				{
					PWM1_OC1A_PIN_DDR &= ~(1<<PWM1_OC1A_PIN_BIT);
					TCCR1A = (TCCR1A & (~((1<<COM1A1) | (1<<COM1A0)))) | (1<<COM1A1);
					break;
				}
				case PWM1_WAVEFORMMODE_INVERTED:
				{
					PWM1_OC1A_PIN_DDR &= ~(1<<PWM1_OC1A_PIN_BIT);
					TCCR1A = (TCCR1A & (~((1<<COM1A1) | (1<<COM1A0)))) | (1<<COM1A1) | (1<<COM1A0);
					break;					
				}
				case PWM1_WAVEFORMMODE_CH_A_50_DUTY:
				{
					PWM1_OC1A_PIN_DDR &= ~(1<<PWM1_OC1A_PIN_BIT);
					TCCR1A = (TCCR1A & (~((1<<COM1A1) | (1<<COM1A0)))) | (1<<COM1A0);
					break;
				}
			}
			OCR1A=dutyCycle;
			break;
		}
		case PWM1_CHANNEL_B:
		{
			switch (waveformMode)
			{
				case PWM1_WAVEFORMMODE_DISABLED:
				{
					TCCR1A &= ~((1<<COM1B1) | (1<<COM1B0));
					break;
				}
				case PWM1_WAVEFORMMODE_NORMAL:
				{
					PWM1_OC1B_PIN_DDR &= ~(1<<PWM1_OC1B_PIN_BIT);
					TCCR1A = (TCCR1A & (~((1<<COM1B1) | (1<<COM1B0)))) | (1<<COM1B1);
					break;
				}
				case PWM1_WAVEFORMMODE_INVERTED:
				{
					PWM1_OC1B_PIN_DDR &= ~(1<<PWM1_OC1B_PIN_BIT);
					TCCR1A = (TCCR1A & (~((1<<COM1B1) | (1<<COM1B0)))) | (1<<COM1B1) | (1<<COM1B0);
					break;
				}
				default:
				{
					break;
				}
			}
			OCR1B=dutyCycle;
			break;
		}
		default:
		{
			break;
		}
	}
}

void pwm1_setDuty(uint8_t channel, uint16_t dutyCycle)
{
	if (channel==PWM1_CHANNEL_A && !((TCCR1A & (1<<WGM10)) && (TCCR1B & (1<<WGM13)))) // If PWM OCRA top mode enable, pin 1 cannot work as pwm
	{
		OCR1A = dutyCycle;
	}
	if(channel==PWM1_CHANNEL_B)
	{
		OCR1B=dutyCycle;
	}
}

void pwm1_end(void)
{
	TCCR1B=0;
	TCCR1A=0;
	TCNT1=0;
	PWM1_OC1A_PIN_DDR &= ~(1<<PWM1_OC1A_PIN_BIT);
	PWM1_OC1B_PIN_DDR &= ~(1<<PWM1_OC1B_PIN_BIT);
}

