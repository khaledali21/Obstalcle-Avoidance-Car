/*
 * ICU.h
 *
 *  Created on: Feb 13, 2022
 *      Author: Esraa
 */

#ifndef ECUAL_ICU_ICU_H_
#define ECUAL_ICU_ICU_H_


#include "../../LIB/Atmega32.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/Typedef.h"
#include "../../MCAL/TIMER0/TIMER0_interface.h"
#include "../../MCAL/EXTI/EXTI.h"



uint8_t ICU_init();
void ICU_vidCalculation();

#endif /* ECUAL_ICU_ICU_H_ */
