/*
 * DRIVE.c
 *
 *  Created on: Jan 11, 2022
 *      Author: Binary Beasts
 */

#include "DRIVE.h"

// creat 2 Motor structure describe port and pins an PWM channel 
MotorDef_t Right_Motors = { PORTD , PIN2 ,PIN3 , PIN4,CHANNELA };
MotorDef_t Left_Motors = { PORTD , PIN6 ,PIN7 , PIN5, CHANNELB};

// function to initialize motors to drive 
uint8_t DRIVE_u8Init (void)
{
	uint8_t Error_State = STD_TYPES_OK ;
 	Error_State = MOTOR_init(&Right_Motors);   // initialize right motors 
	if ( Error_State == STD_TYPES_NOK )      // check if MOTOR_init return error state NOK
	{
		return Error_State ;
	}
	Error_State = MOTOR_init(&Left_Motors);	// initialize left motors
	if ( Error_State == STD_TYPES_NOK )		 // check if MOTOR_init return error state NOK
	{
		return Error_State ;
	}	
	return Error_State ;
}

uint8_t DRIVE_u8Right ( void )
{
	uint8_t Error_State = STD_TYPES_OK ;
	// move right motors backward 
	Error_State = MOTOR_Move( &Right_Motors , SLOW , ANTI_CLOCKWISE ) ;
	if ( Error_State == STD_TYPES_NOK ) // check if MOTOR_Move return error state NOK
	{
		return Error_State ;
	}
	// move left motors forward 
	Error_State = MOTOR_Move( &Left_Motors , SLOW , CLOCKWISE ) ;
	if ( Error_State == STD_TYPES_NOK )	// check if MOTOR_Move return error state NOK
	{
		return Error_State ;
	}
	return Error_State ;
}

uint8_t DRIVE_u8Left ( void )
{
	uint8_t Error_State = STD_TYPES_OK ;
	// move left motors backward 
	Error_State = MOTOR_Move( &Left_Motors , SLOW , ANTI_CLOCKWISE ) ;
	if ( Error_State == STD_TYPES_NOK )	// check if MOTOR_Move return error state NOK
	{
		return Error_State ;
	}
	// move right motors forward 
	Error_State = MOTOR_Move( &Right_Motors , SLOW , CLOCKWISE ) ;
	if ( Error_State == STD_TYPES_NOK )	// check if MOTOR_Move return error state NOK
	{
		return Error_State ;
	}
	return Error_State ;
}

uint8_t DRIVE_u8Mode ( uint8_t mode )
{
	uint8_t Error_State = STD_TYPES_OK ;
	switch ( mode )
	{
		case MODE1 :
			// stop left motors 
			Error_State = MOTOR_Stop( &Left_Motors ) ;
			if ( Error_State == STD_TYPES_NOK )	// check if MOTOR_Stop return error state NOK
			{
				return Error_State ;
			}
			// stop right motors 		
			Error_State = MOTOR_Stop( &Right_Motors ) ;
			if ( Error_State == STD_TYPES_NOK )	// check if MOTOR_Stop return error state NOK
			{
				return Error_State ;
			}
			break ;	
			
		case MODE2 :
			// move left motors with the first speed 
			Error_State = MOTOR_Move( &Left_Motors , SLOW , CLOCKWISE ) ;
			if ( Error_State == STD_TYPES_NOK )	// check if MOTOR_Move return error state NOK
			{
				return Error_State ;
			}
			// move right motors with the first speed 		
			Error_State = MOTOR_Move( &Right_Motors , SLOW , CLOCKWISE ) ;
			if ( Error_State == STD_TYPES_NOK )	// check if MOTOR_Move return error state NOK
			{
				return Error_State ;
			}
			break ;		
		case MODE4 :
			// move left motors with the third speed 
			Error_State = MOTOR_Move( &Left_Motors , FAST , CLOCKWISE ) ;
			if ( Error_State == STD_TYPES_NOK )	// check if MOTOR_Move return error state NOK
			{
				return Error_State ;
			}	
			// move right motors with the third speed 	
			Error_State = MOTOR_Move( &Right_Motors , FAST , CLOCKWISE ) ;
			if ( Error_State == STD_TYPES_NOK )	// check if MOTOR_Move return error state NOK
			{
				return Error_State ;
			}
			break;
		case MODE5 :
			// move left motors backward 
			Error_State = MOTOR_Move( &Left_Motors , SLOW , ANTI_CLOCKWISE) ;
			if ( Error_State == STD_TYPES_NOK )	// check if MOTOR_Move return error state NOK
			{
				return Error_State ;
			}	
			// move right motors backward 	
			Error_State = MOTOR_Move( &Right_Motors , SLOW , ANTI_CLOCKWISE) ;
			if ( Error_State == STD_TYPES_NOK )	// check if MOTOR_Move return error state NOK
			{
				return Error_State ;
			}
			break;
		default:
			break;
	}
}
