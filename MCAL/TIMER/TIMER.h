/*
 * Timer.h
 *
 * Created: 1/9/2022 12:20:30 AM
 *  Author: Binary Beasts
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "../../LIB/atmega32.h"
#include "../../LIB/Typedef.h"
#include "../../LIB/BIT_Math.h"
#include "../TIMER/TIMER.h"

#define INIT_TIME 65536U - 256U       // set initial value make timer overflow after 256 ticks 
#define PRESCALER 64U			      // devide by 64 as a prescaler  

/* TCCR0 BITS */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0


/* TCCR1A_REG BITS */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

/* TCCR1B_REG BITS */
#define ICNC1   7
#define ICES1   6
/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0


/* TCCR2_REG BITS */
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0

/* TIMSK_REG BITS */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0


/* SREG_REG GLOBAL INTERRUPT BIT */
#define I_BIT 7

/* enum to select which channel PWM will be used  */
typedef enum{
	CHANNELA,
	CHANNELB
}CHANNEL;

// function to initialize TIMER1 
uint8_t TIMER1_u8Init(void);

// function set clock and start TIMER1
uint8_t TIMER1_u8Start(void);

// function to set channel register value to compare with 
uint8_t TIMER1_u8SetComapre(CHANNEL channel,uint16_t compareValue);

// function to set pointer to the function run in interrupt  
uint8_t TIMER1_u8SetChannelInterrupt(CHANNEL channel, void (*fnCallBack)(void));

// function to stop channel 
uint8_t TIMER1_u8StopChannel(CHANNEL channel);

// ISR for TIMER1 COMA
void __vector_7(void) __attribute__ ((signal, used));

// ISR for TIMER1 COMB
void __vector_8(void) __attribute__ ((signal, used));

// ISR for TIMER1 OVF
void __vector_9(void) __attribute__ ((signal, used));


#endif /* TIMER_H_ */
