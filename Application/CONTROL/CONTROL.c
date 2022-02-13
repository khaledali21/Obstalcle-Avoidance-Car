/*
 * CONTROL.c
 *
 * Created: 2/13/2022 10:15:27 PM
 *  Author: Khaled Ali
 */


#include "CONTROL.h"
#include "../DRIVE/DRIVE.h"
#include "../../ECUAL/ULTRA_SONIC/US.h"
RobotState_t robotState = MOVE_FORWARD_FAST;
extern USElement_t US;
void TASK_Control(void* vptr){
	switch(robotState){
		case  MOVE_FORWARD_FAST:
		DRIVE_u8Mode(MODE4);
		break;
		case MOVE_FORWARD_SLOW:
		DRIVE_u8Mode(MODE2);
		break;
		case MOVE_RIGHT:
		DRIVE_u8Right();
		break;
		case MOVE_BACKWARD:
		DRIVE_u8Mode(MODE5);
		break;
		default:
		break;
	}
}


void TASK_UpateState(void* vptr){
	uint16_t distance;
	US_u8GetDistance(&US, &distance);
	if(distance < 30){
		DRIVE_u8Mode(MODE1);
		robotState = MOVE_BACKWARD;
	}
	else if(distance >= 30 && robotState == MOVE_BACKWARD){
		robotState = MOVE_RIGHT;
	}
	else if(distance < 50){
		robotState = MOVE_FORWARD_SLOW;
	}
	else{
		robotState = MOVE_FORWARD_FAST;
	}
}