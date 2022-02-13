/*
 * PWM.h
 *
 * Created: 1/9/2022 11:06:56 PM
 *  Author: Binary Beasts
 */ 


#ifndef PWM_H_
#define PWM_H_
#include "../../LIB/Typedef.h"
#include "../DIO/DIO_interface.h"
#include "../TIMER/TIMER.h"
#include "PWM.h"


#define MAX_VALUE 256U		// max value passed to the timer 
#define MAX_DUTY 100U		// max duty cycle value 

// struct to define which pin will be used as PWM pin
typedef struct{
	uint8_t port;
	uint8_t pin;
}PWMPin_t;

// function to initialize channel in the selected pin 
uint8_t PWM_u8Init(CHANNEL channel,PWMPin_t* pwm);

// function set duty cycle on the selected channel 
uint8_t PWM_u8DutyCycle(CHANNEL channel, uint32_t dutyCycle);

// function to stop PWM 
uint8_t PWM_u8Stop(void);
#endif /* PWM_H_ */
