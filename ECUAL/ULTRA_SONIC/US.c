/*
 * US.c
 *
 *  Created on: Feb 13, 2022
 *      Author: Esraa
 */


#include "US.h"

#define US_TIMER_TICK_TIMER 32UL

uint8_t US_u8Init(USElement_t* USDefinition)
{
	DIO_u8SetPinDirection(USDefinition->US_PORT,USDefinition->TriggerPin,DIO_OUTPUT);
	DIO_u8SetPinDirection(USDefinition->US_PORT,USDefinition->EchoPin,DIO_INPUT);

}
uint8_t US_u8Trigger(USElement_t* USDefinition)
{
	DIO_u8SetPinData(USDefinition->US_PORT,USDefinition->TriggerPin,DIO_HIGH);
	for(volatile uint8_t u8iterator=0;u8iterator<60;u8iterator++);
	DIO_u8SetPinData(USDefinition->US_PORT,USDefinition->TriggerPin,DIO_LOW);
}

uint8_t US_u8GetDistance(USElement_t* USDefinition,uint8_t* u8Distance)
{
	if (u8Distance!=NULL)
	{
		ICU_init(u8Distance);
		*u8Distance = ((US_TIMER_TICK_TIMER * (*u8Distance)) / 58UL);
	}else
	{
		//NOP
	}
}
