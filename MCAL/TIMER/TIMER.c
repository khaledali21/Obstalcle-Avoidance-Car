/*
 * TIMER.c
 *
 * Created: 1/9/2022 2:41:02 AM
 *  Author: Binary Beasts
 */ 

#include "TIMER.h"

// pointer to function that will be called when COMPA interrupt 
static void (*COMPA_callBack)(void);

// pointer to function that will be called when COMPB interrupt 	
static void (*COMPB_callBack)(void);

// function to intialize values of control registers 
uint8_t TIMER1_u8Init(void)
{
	TCCR1A_REG = 0;
	TCCR1B_REG = 0;
	return 1;
}

// function to set start counting and set intitial value 
uint8_t TIMER1_u8Start(void)
{
	TCCR1B_REG |= (1 << CS10) | (1 << CS11);
	TCNT1_REG = INIT_TIME;							
	return 1;
}

// function to set channel register ( OCR1X_REG ) value to compare with 
uint8_t TIMER1_u8SetComapre(CHANNEL channel,uint16_t compareValue)
{
	switch(channel){
		case CHANNELA:
		OCR1A_REG = compareValue + INIT_TIME;	// set channel register value to compare with 
		break;
		case CHANNELB:
		OCR1B_REG = compareValue + INIT_TIME;	// set channel register value to compare with
		break;
		default:
		return 0;
	}
	return 1;
}

// function to set pointer to the function run in interrupt
// take channel and pointer to function to run in ISR   
uint8_t TIMER1_u8SetChannelInterrupt(CHANNEL channel, void (*fnCallBack)(void)){
	if(fnCallBack == NULL){
		return 0;
	}
	switch(channel){
		case CHANNELA:
			SET_BIT(TIMSK_REG, OCIE1A);			// Enable interrupt when COMPA 
			COMPA_callBack = fnCallBack;      	// set function in interrupt to the passed function
		break;
		case CHANNELB:
			SET_BIT(TIMSK_REG, OCIE1B);			// Enable interrupt when COMPB 
			COMPB_callBack = fnCallBack;		// set function in interrupt to the passed function 
		break;
		default:
		return 0;
	}
	SET_BIT(TIMSK_REG, TOIE1);				// Enable interrupt 
	SET_BIT(SREG_REG, I_BIT);
	return 1;	
}

// function to stop comparing with channel 
uint8_t TIMER1_u8StopChannel(CHANNEL channel)
{
	switch(channel){
		case CHANNELA:
			CLR_BIT(TIMSK_REG, OCIE1A);      // disable interrupt 
			COMPA_callBack = NULL;           // make sure no function to run in interrupt
			break;
		case CHANNELB:
			CLR_BIT(TIMSK_REG, OCIE1B);	 	 // disable interrupt 
			COMPB_callBack = NULL;		 	 // make sure no function to run in interrupt
			break;
		default:
		return 0;	
	}
	return 1;
}

//ISR for TIMER1 COMPA
void __vector_7(void){
	if(COMPA_callBack != NULL){
		COMPA_callBack();
	}
}
//ISR for TIMER1 COMPB
void __vector_8(void){
	if(COMPB_callBack != NULL){
		COMPB_callBack();
	}
}
//ISR for TIMER1 OVF
void __vector_9(void){
	TCNT1_REG = INIT_TIME;    // reset counter value to initial value 
	if(COMPA_callBack != NULL){
		COMPA_callBack();
	}
	if(COMPB_callBack != NULL){
		COMPB_callBack();
	}		
}

