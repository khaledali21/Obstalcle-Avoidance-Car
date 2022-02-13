/*
 * ICU.c
 *
 *  Created on: Feb 13, 2022
 *      Author: Esraa
 */

#include "ICU.h"

#define ICU_EXTI_RISING	 0
#define ICU_EXTI_FALLING 1
#define ICU_TIMER_START	 0

uint8_t gu8_EXTIFlag=ICU_EXTI_RISING;
uint8_t* gu8_ICUPeriod=NULL;



uint8_t ICU_init(uint8_t* pu8PeriodReader)
{
	uint8_t u8ErrorState=STD_TYPES_OK;
	TIM0_Config_t ICUTimer= {
			TIM0_NORMAL,
			PRESCALAR_256
	};
	gu8_ICUPeriod=pu8PeriodReader;
	TIM0_u8Init(&ICUTimer);
	TIM0_u8TimerStart();
	EXTI_u8Enable(INT2,EXTI_RISING_EDGE,ICU_vidCalculation);
	return u8ErrorState;
}


void ICU_vidCalculation()
{
	switch (gu8_EXTIFlag) {
		case ICU_EXTI_RISING:
			TIM0_u8SetStart(ICU_TIMER_START);
			TIM0_u8TimerStart();
			//TIM0_u8GetCounts(&gu8_ICUStart);
			EXTI_u8Enable(INT2,EXTI_FALLING_EDGE,ICU_vidCalculation);
			gu8_EXTIFlag=ICU_EXTI_FALLING;
			break;
		case ICU_EXTI_FALLING:
			TIM0_u8TimerStop();
			TIM0_u8GetCounts(gu8_ICUPeriod);
			TIM0_u8SetStart(ICU_TIMER_START);
			EXTI_u8Enable(INT2,EXTI_RISING_EDGE,ICU_vidCalculation);
			gu8_EXTIFlag=ICU_EXTI_RISING;
			break;
		default:
			break;
	}
}
