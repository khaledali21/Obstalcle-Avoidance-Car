/*
 * CONTROL.c
 *
 * Created: 2/13/2022 10:15:27 PM
 *  Author: Khaled Ali
 */


#include "CONTROL.h"
#include "../DRIVE/DRIVE.h"
#include "../../ECUAL/LED/LED.h"
#include "../../ECUAL/LCD/LCD.h"
#include "../../ECUAL/ULTRA_SONIC/US.h"
RobotState_t volatile robotState = MOVE_FORWARD_FAST;
LED_t led0 = {PORTB, PIN4};
LED_t led1 = {PORTB, PIN5};
LED_t led2 = {PORTB, PIN6};
LED_t led3 = {PORTB, PIN7};
extern USElement_t US;
uint16_t distance;
void CONTROL_Init(void){
	LED_u8Init(&led0);
	LED_u8Init(&led1);
	LED_u8Init(&led2);
	LED_u8Init(&led3);
}
void TASK_Control(void* vptr){
	switch(robotState){
		case  MOVE_FORWARD_FAST:
		DRIVE_u8Mode(MODE4);
		LED_u8ON(&led0);
		LED_u8OFF(&led1);
		LED_u8OFF(&led2);
		LED_u8OFF(&led3);
		break;
		case MOVE_FORWARD_SLOW:
		DRIVE_u8Mode(MODE2);
		LED_u8OFF(&led0);
		LED_u8ON(&led1);
		LED_u8OFF(&led2);
		LED_u8OFF(&led3);
		break;
		case MOVE_RIGHT:
		DRIVE_u8Right();
		LED_u8OFF(&led0);
		LED_u8OFF(&led1);
		LED_u8ON(&led2);
		LED_u8OFF(&led3);
		break;
		case MOVE_BACKWARD:
		DRIVE_u8Mode(MODE5);
		LED_u8OFF(&led0);
		LED_u8OFF(&led1);
		LED_u8OFF(&led2);
		LED_u8ON(&led3);
		break;
		default:
		break;
	}
}


void TASK_UpateState(void* vptr){
	distance = 0;
	US_u8GetDistance(&US, &distance);
	switch(robotState){
		case  MOVE_FORWARD_FAST:
		if(distance < 70 && distance >= 30){
			robotState = MOVE_FORWARD_SLOW;
		}
		else if(distance < 30){
			robotState = MOVE_BACKWARD;
		}
		break;
		case MOVE_FORWARD_SLOW:
		if(distance >= 100){
			robotState = MOVE_FORWARD_FAST;
		}
		else if(distance < 30){
			robotState = MOVE_BACKWARD;
		}
		break;
		case MOVE_RIGHT:
		if(distance >= 70){
			robotState = MOVE_FORWARD_SLOW;
		}
		else if(distance < 30){
			robotState = MOVE_BACKWARD;
		}
		break;
		case MOVE_BACKWARD:
		if(distance >= 50){
			robotState = MOVE_RIGHT;
		}
		break;
		default:
		break;
	}
}
void TASK_PrintDistance(void* vptr){
	LCD_u8SendCommand(LCD_CLEAR);
	LCD_u8SendNumber(distance);
}