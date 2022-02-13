/*
 * Obstacle-Avoidance-Car.c
 *
 * Created: 2/13/2022 12:37:15 PM
 * Author : Khaled Ali
 */ 

#include "SERVICE/OS/OS.h"
#include "ECUAL/LED/LED.h"
#include "Application/DRIVE/DRIVE.h"
#include "ECUAL/ULTRA_SONIC/US.h"
#include "Application/CONTROL/CONTROL.h"
LED_t led0 = {PORTB, PIN4};
USElement_t US={PORTB,PIN1,PIN2};

void TASK_TriggerUS(void* vptr){
	US_u8Trigger(&US);
}
int main(void)
{
	DRIVE_u8Init();
	US_u8Init(&US);
	OS_AddTask(TASK_TriggerUS, 0, 20, NULL);	
	OS_AddTask(TASK_Control, 1, 10, NULL);
	OS_AddTask(TASK_UpateState, 2, 10, NULL);
	OS_Start();
}
