/*
 * OS.h
 *
 * Created: 2/13/2022 1:03:36 PM
 *  Author: Khaled Ali
 */ 


#ifndef OS_H_
#define OS_H_

#include "../../LIB/Atmega32.h"
#include "../../LIB/Typedef.h"
typedef struct
{
	uint16_t periodicity;
	void* parameter;
	void (*FpTr)(void*);
}Task_Type;

#define OS_CLK 8000000UL

#define OS_PRESCALER 64U

#define TASKS_SIZE 20


void OS_Start(void);

uint8_t OS_AddTask(void (*vTaskFunction)(void*), uint8_t priority, uint16_t period, void* parameter);
void OS_Schedule(void);
void OS_Stop(void);

void __vector_4(void) __attribute__ ((signal, used));

#endif /* OS_H_ */