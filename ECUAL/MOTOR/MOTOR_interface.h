/*
 * MOTOR_interface.h
 *
 *  Created on: Jan 11, 2022
 *      Author: Binary Beasts
 */

#ifndef ECUAL_MOTOR_MOTOR_INTERFACE_H_
#define ECUAL_MOTOR_MOTOR_INTERFACE_H_

#include "../../LIB/Typedef.h"
#include "../../LIB/BIT_Math.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/PWM/PWM.h"

// struct to configure motor connection 
typedef struct{
	uint8_t port;
	uint8_t DirPinA;
	uint8_t DirPinB;
	uint8_t ENPin;
	uint8_t ChannelNum;
}MotorDef_t;

// enum to describe motion direction 
typedef enum{
	 CLOCKWISE,
	 ANTI_CLOCKWISE
}MotorDir_t;

// function to initialze motor 
uint8_t MOTOR_init(MotorDef_t* MotorElement);

// function make motor move with specific speed and direction 
uint8_t MOTOR_Move(MotorDef_t* MotorElement,uint8_t MotorSpeed,uint8_t MotorDir);

// function make motor stop 
uint8_t MOTOR_Stop(MotorDef_t* MotorElement);

#endif /* ECUAL_MOTOR_MOTOR_INTERFACE_H_ */
