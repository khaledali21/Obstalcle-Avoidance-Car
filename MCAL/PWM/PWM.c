/*
 * PWM.c
 *
 * Created: 1/9/2022 11:07:10 PM
 *  Author: Binary Beasts
 */ 

#include "PWM.h"

// creat 2 PWM struct contain port and pin for each channel  
static PWMPin_t PWM1;
static PWMPin_t PWM2;

// function to toggle PWM pin channel 1
void channelA_callBack(void){	
	DIO_u8TogglePinData(PWM1.port, PWM1.pin);
}

// function to toggle PWM pin channel 2
void channelB_callBack(void){
	DIO_u8TogglePinData(PWM2.port, PWM2.pin);
}

// initialize PWM channel for selected pin 
uint8_t PWM_u8Init(CHANNEL channel,PWMPin_t* pwm){
	switch(channel){
		case CHANNELA:
			PWM1 = *pwm;		// set port and pin value 
			break;
		case CHANNELB:
			PWM2 = *pwm;		// set port and pin value 
			break;
		default:
			return 0;
	}
	return TIMER1_u8Init();		// initialize TIMER1
}

// function set duty cycle on the selected channel 
uint8_t PWM_u8DutyCycle(CHANNEL channel, uint32_t dutyCycle)
{
	uint32_t dutyValue = ((float) dutyCycle * MAX_VALUE) / MAX_DUTY;  // calculate real duty value 
	
	// depend on channel initalize it to HIGH 
	// toggle pin depend on duty cycle and frequency  
	switch(channel){
		case CHANNELA:	
			DIO_u8SetPinData(PWM1.port, PWM1.pin, DIO_HIGH);
			TIMER1_u8StopChannel(channel);							
			TIMER1_u8SetComapre(channel, (uint16_t) dutyValue);
			TIMER1_u8SetChannelInterrupt(channel, channelA_callBack);
			break;
		case CHANNELB:
			DIO_u8SetPinData(PWM2.port, PWM2.pin, DIO_HIGH);
			TIMER1_u8StopChannel(channel);
			TIMER1_u8SetComapre(channel, (uint16_t) dutyValue);
			TIMER1_u8SetChannelInterrupt(channel, channelB_callBack);
			break;
		default:
			return 0;
	}
	return TIMER1_u8Start();
}
