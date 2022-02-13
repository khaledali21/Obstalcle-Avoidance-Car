/*
 * CONTROL.h
 *
 * Created: 2/13/2022 10:15:38 PM
 *  Author: Khaled Ali
 */ 


#ifndef CONTROL_H_
#define CONTROL_H_

typedef enum
{
	MOVE_FORWARD_FAST,
	MOVE_FORWARD_SLOW,
	MOVE_RIGHT,
	MOVE_BACKWARD
}RobotState_t;



void TASK_Control(void*);
void TASK_UpateState(void*);
#endif /* CONTROL_H_ */