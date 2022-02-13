/*
 * DRIVE.h
 *
 *  Created on: Jan 11, 2022
 *      Author: Binary Beasts
 */
 
#ifndef _DRIVE_H_
#define _DRIVE_H_

#include "../../LIB/BIT_Math.h"
#include "../../LIB/Typedef.h"
#include "../../ECUAL/MOTOR/MOTOR_interface.h"

// speeds
#define SLOW 30 
#define MIDIUM 50 
#define FAST 80 

// move modes 
#define MODE1 0 
#define MODE2 1
#define MODE3 2
#define MODE4 3
#define MODE5 4

// function to initialize motors to drive 
uint8_t DRIVE_u8Init ( void );

// function to rotate right 
uint8_t DRIVE_u8Right ( void );

// function to rotate left
uint8_t DRIVE_u8Left ( void );

// function to move depend on mode ( speed and direction )
uint8_t DRIVE_u8Mode ( uint8_t mode);

#endif
