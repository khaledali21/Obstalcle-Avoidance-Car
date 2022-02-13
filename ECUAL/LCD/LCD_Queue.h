/*
 * LCD_Queue.h
 *
 * Created: 2/9/2022 1:19:36 AM
 *  Author: Khaled Ali
 */ 


#ifndef LCD_QUEUE_H_
#define LCD_QUEUE_H_
#include "../../LIB/Typedef.h"
typedef enum{
	COMMAND,
	DATA	
}LCD_TYPE;

typedef struct{
	uint8_t data;
	LCD_TYPE type;	
}LCD_QUEUE_ITEM;


#define SIZE 128

#define QUEUE_INIT_VALUE -1
uint8_t isFull(void);

uint8_t isEmpty(void);

uint8_t LCD_enQueue(LCD_QUEUE_ITEM element);

uint8_t LCD_deQueue(LCD_QUEUE_ITEM* element);

#endif /* LCD_QUEUE_H_ */