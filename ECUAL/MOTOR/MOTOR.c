/*
 * MOTOR.c
 *
 *  Created on: Jan 11, 2022
 *      Author: Binary Beasts
 */

#include "MOTOR_interface.h"

// function to initialze motor 
uint8_t MOTOR_init(MotorDef_t* MotorElement)
{
	uint8_t u8ErrorState = STD_TYPES_OK;
	// set PWM pin channel to motor 
	PWMPin_t MotorDef = {MotorElement->port, MotorElement->ENPin};
	// set direction of motor's pins as OUTPUT pins
	u8ErrorState= DIO_u8SetPinDirection(MotorElement->port,MotorElement->DirPinA,DIO_OUTPUT);
	if (u8ErrorState==STD_TYPES_OK)
	{
		u8ErrorState= DIO_u8SetPinDirection(MotorElement->port,MotorElement->DirPinB,DIO_OUTPUT);
	}
	if (u8ErrorState==STD_TYPES_OK)
	{
		u8ErrorState=DIO_u8SetPinDirection(MotorElement->port,MotorElement->ENPin,DIO_OUTPUT);
	}
	// initialize PWM 
	PWM_u8Init(MotorElement->ChannelNum, &MotorDef);
	return u8ErrorState;
}

// function make motor move with specific speed and direction
uint8_t MOTOR_Move(MotorDef_t* MotorElement,uint8_t MotorSpeed,uint8_t MotorDir)
{
	uint8_t u8ErrorState = STD_TYPES_OK;

	if (MotorElement!=NULL && MotorSpeed > 0 && MotorSpeed <100)
	{
		switch (MotorDir)
		{
		// set direction pins and duty cycle to control in speed and direction 
		case CLOCKWISE:
			DIO_u8SetPinData(MotorElement->port , MotorElement->DirPinA, DIO_HIGH);
			DIO_u8SetPinData(MotorElement->port , MotorElement->DirPinB, DIO_LOW);
			PWM_u8DutyCycle(MotorElement->ChannelNum,MotorSpeed);
			break;
		case ANTI_CLOCKWISE:
			DIO_u8SetPinData(MotorElement->port , MotorElement->DirPinA, DIO_LOW);
			DIO_u8SetPinData(MotorElement->port , MotorElement->DirPinB, DIO_HIGH);
			PWM_u8DutyCycle(MotorElement->ChannelNum,MotorSpeed);
			break;
		default:
			u8ErrorState = STD_TYPES_NOK;
			break;
		}

	}else{
		u8ErrorState = STD_TYPES_NOK;
	}

	return u8ErrorState;
}

// function make motor stop 
uint8_t MOTOR_Stop(MotorDef_t* MotorElement)
{
	uint8_t u8ErrorState = STD_TYPES_OK;
	if (MotorElement!=NULL)
	{
		// make 2 pins LOW force motor to stop 
		DIO_u8SetPinData(MotorElement->port , MotorElement->DirPinA, DIO_LOW);
		DIO_u8SetPinData(MotorElement->port , MotorElement->DirPinB, DIO_LOW);
	}else{
		u8ErrorState = STD_TYPES_NOK;
	}

	return u8ErrorState;
}
