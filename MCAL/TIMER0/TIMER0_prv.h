/*
 * TIMER0_prv.h
 *
 *  Created on: Jan 15, 2022
 *      Author: vip
 */

#ifndef MCAL_TIMER0_TIMER0_PRV_H_
#define MCAL_TIMER0_TIMER0_PRV_H_

#define TIMER0_MAX		255


//ISR for TIMER0 COMP
void __vector_10(void) __attribute__ ((signal, used));

//ISR for TIMER0 OVF
void __vector_11(void) __attribute__ ((signal, used));


#endif /* MCAL_TIMER0_TIMER0_PRV_H_ */
