/*
 * US.h
 *
 *  Created on: Feb 13, 2022
 *      Author: Esraa
 */

#ifndef ECUAL_ULTRA_SONIC_US_H_
#define ECUAL_ULTRA_SONIC_US_H_

#include "../../MCAL/DIO/DIO_interface.h"
#include "../ICU/ICU.h"


typedef struct{
	uint8_t US_PORT;
	uint8_t TriggerPin;
	uint8_t EchoPin;
}USElement_t;

uint8_t US_u8Init(USElement_t* USDefinition);
uint8_t US_u8Trigger(USElement_t* USDefinition);
uint8_t US_u8GetDistance(USElement_t* USDefinition,uint16_t* u8Distance);

#endif /* ECUAL_ULTRA_SONIC_US_H_ */
