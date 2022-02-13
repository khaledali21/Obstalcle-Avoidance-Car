/*
 * Obstacle-Avoidance-Car.c
 *
 * Created: 2/13/2022 12:37:15 PM
 * Author : Khaled Ali
 */ 

#include "SERVICE/OS/OS.h"
#include "ECUAL/LED/LED.h"
#include "ECUAL/LCD/LCD.h"
#include "Application/DRIVE/DRIVE.h"
#include "ECUAL/ULTRA_SONIC/US.h"
#include "Application/CONTROL/CONTROL.h"


USElement_t US={PORTB,PIN1,PIN2};

void TASK_TriggerUS(void* vptr){
	US_u8Trigger(&US);
}
int main(void)
{
	CONTROL_Init();
	LCD_u8Init();
	DRIVE_u8Init();
	US_u8Init(&US);
	OS_AddTask(LCD_callBack, 0, 1, NULL);
	OS_AddTask(TASK_TriggerUS, 1, 5, NULL);	
	OS_AddTask(TASK_Control, 2, 10, NULL);
	OS_AddTask(TASK_UpateState, 3, 10, NULL);
	OS_Start();
}
