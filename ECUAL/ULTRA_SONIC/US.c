/*
 * US.c
 *
 *  Created on: Feb 13, 2022
 *      Author: Esraa
 */


#include "US.h"
#include "../LCD/LCD.h"
#define US_TIMER_TICK_TIMER 128

uint8_t US_u8Init(USElement_t* USDefinition)
{
	DIO_u8SetPinDirection(USDefinition->US_PORT,USDefinition->TriggerPin,DIO_OUTPUT);
	DIO_u8SetPinDirection(USDefinition->US_PORT,USDefinition->EchoPin,DIO_INPUT_PULLUP);
	ICU_init();

}
uint8_t US_u8Trigger(USElement_t* USDefinition)
{
	DIO_u8SetPinData(USDefinition->US_PORT,USDefinition->TriggerPin,DIO_HIGH);
	for(volatile uint8_t u8iterator=0;u8iterator<60;u8iterator++);
	DIO_u8SetPinData(USDefinition->US_PORT,USDefinition->TriggerPin,DIO_LOW);
}

uint8_t US_u8GetDistance(USElement_t* USDefinition,uint16_t* u8Distance)
{
	if (u8Distance!=NULL)
	{
		ICU_Read(u8Distance);
		float f32Distance = *u8Distance;
		
		*u8Distance = ((US_TIMER_TICK_TIMER * (f32Distance)) / 58UL);
	}else
	{
		//NOP
	}
}
