/*
 * LCD_Queue.c
 *
 * Created: 2/9/2022 1:19:25 AM
 *  Author: Khaled Ali
 */ 
#include "LCD_Queue.h"

LCD_QUEUE_ITEM items[SIZE];
sint8_t front = QUEUE_INIT_VALUE, rear = QUEUE_INIT_VALUE;

// Check if the queue is full
uint8_t isFull() {
	if ((front == rear + 1) || (front == 0 && rear == SIZE - 1)) return TRUE;
	return FALSE;
}

// Check if the queue is empty
uint8_t isEmpty() {
	if (front == QUEUE_INIT_VALUE) return TRUE;
	return FALSE;
}

// Adding an element
uint8_t LCD_enQueue(LCD_QUEUE_ITEM element) {
	if (isFull()){
		return STD_TYPES_NOK;
	}
	else {
		if (front == QUEUE_INIT_VALUE){
			front = 0;
		}
		rear = (rear + 1) % SIZE;
		items[rear] = element;
	}
	return STD_TYPES_OK;
}

uint8_t LCD_deQueue(LCD_QUEUE_ITEM* element) {
	uint8_t status = STD_TYPES_OK;
	if (isEmpty()) {
		status =  STD_TYPES_NOK;
		}
		else {
			element->data = items[front].data;
			element->type = items[front].type;
			if (front == rear) {
				front = QUEUE_INIT_VALUE;
				rear = QUEUE_INIT_VALUE;
			}
			else
			{
				front = (front + 1) % SIZE;
		}
	}
	return status;
}