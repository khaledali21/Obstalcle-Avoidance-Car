/*
 * OS.c
 *
 * Created: 2/13/2022 1:03:50 PM
 *  Author: Khaled Ali
 */ 
#include "OS.h"
static Task_Type tasks[TASKS_SIZE];
static uint8_t numOfTasks = 0;
static volatile uint16_t tick = 0;
static uint16_t prev_tick = 0;
void OS_Start(void){
	TCCR2_REG = (1 << WGM21_BIT) | (1<<CS22_BIT);
	TCNT2_REG = 0;
	OCR2_REG = (OS_CLK / OS_PRESCALER) / 1000;
	TIMSK_REG |= (1 << OCIE2_BIT);
	SREG_REG |= (1 << I_BIT);
	while(1){
		while(tick == prev_tick);
		prev_tick++;
		OS_Schedule();		
	}
}

uint8_t OS_AddTask( void (*vTaskFunction)(void*), uint8_t priority, uint16_t period, void* parameter){
	uint8_t u8ErrorStatus = STD_TYPES_OK;
	if(vTaskFunction == NULL || numOfTasks == TASKS_SIZE){
		u8ErrorStatus = STD_TYPES_NOK;
	}
	else{
		tasks[priority].periodicity = period;
		tasks[priority].FpTr = vTaskFunction;
		tasks[priority].parameter = parameter;
		numOfTasks++;
	}
	return u8ErrorStatus;
}

void OS_Schedule(void){
	for(uint8_t itr = 0; itr < numOfTasks; itr++){
		if(tick % tasks[itr].periodicity == 0)
		{
			tasks[itr].FpTr(tasks[itr].parameter);
		}
	}
	tick %= 65000;
}

void OS_Stop(void){
	TCCR2_REG = 0;
}


void __vector_4(void){
	tick++;
}
