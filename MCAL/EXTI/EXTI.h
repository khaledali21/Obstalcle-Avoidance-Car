/*
 * EXTI.h
 *
 *  Created on: Feb 5, 2022
 *      Author: Esraa
 */

#ifndef MCAL_EXTI_EXTI_H_
#define MCAL_EXTI_EXTI_H_

#include "../../LIB/Atmega32.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/Typedef.h"

typedef enum{

	EXTI_OK=1,
	EXTI_WRONG_INT_NUMBER,
	EXTI_WRONG_TRIGGER_TYPE,
}EXTIErrorState_t;

typedef enum{
	INT0,
	INT1,
	INT2
}EXTINumber_t;

typedef enum{
	EXTI_LOW_LEVEL,
	EXTI_TOGGLE,
	EXTI_FALLING_EDGE,
	EXTI_RISING_EDGE
}EXTITiggerType_t;

uint8_t EXTI_u8Enable(EXTINumber_t u8InterruptNumber, EXTITiggerType_t u8InterruptTrigger, void (*vCallBackFun)(void));


#endif /* MCAL_EXTI_EXTI_H_ */
