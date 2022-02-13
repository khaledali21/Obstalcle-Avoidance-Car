/*
 * LCD.c
 *
 * Created: 1/17/2022 12:19:06 AM
 *  Author: Khaled Ali
 */

#include "LCD.h"
#include "LCD_Queue.h"
static LCD_ERR_STATUS LCD_u8SendCommandPrivate(uint8_t command);
static LCD_ERR_STATUS LCD_u8SendDataPrivate(uint8_t data);
/*
* brief: This function is used to initialize pin directions of the LCD as defined in the configurations and in 4-Bit Mode
* return: (output) the Error state of the function LCD_ERR if an error happens and LCD_OK otherwise
*/
LCD_ERR_STATUS LCD_u8Init(void) {
	LCD_ERR_STATUS status = LCD_OK;
	DIO_u8SetPinDirection(RS_PORT, RS_PIN, DIO_OUTPUT);
	DIO_u8SetPinDirection(RW_PORT, RW_PIN, DIO_OUTPUT);
	DIO_u8SetPinDirection(E_PORT, E_PIN, DIO_OUTPUT);
	DIO_u8SetPinDirection(D4_PORT, D4_PIN, DIO_OUTPUT);
	DIO_u8SetPinDirection(D4_PORT, D5_PIN, DIO_OUTPUT);
	DIO_u8SetPinDirection(D4_PORT, D6_PIN, DIO_OUTPUT);
	DIO_u8SetPinDirection(D4_PORT, D7_PIN, DIO_OUTPUT);
	status = LCD_enQueue((LCD_QUEUE_ITEM) {0x33, COMMAND});
	if(status == LCD_OK){
		LCD_enQueue((LCD_QUEUE_ITEM) {0x32, COMMAND});
	}
	if(status == LCD_OK){
		LCD_enQueue((LCD_QUEUE_ITEM) {LCD_4BIT_MODE, COMMAND});
	}
	if(status == LCD_OK){
		LCD_enQueue((LCD_QUEUE_ITEM) {LCD_DISPLAY_ON, COMMAND});
	}
	if(status == LCD_OK){
		LCD_enQueue((LCD_QUEUE_ITEM) {LCD_SHIFT_CURSOR_RIGHT, COMMAND});
	}
	if(status == LCD_OK){
		LCD_enQueue((LCD_QUEUE_ITEM) {LCD_CLEAR, COMMAND});
	}
	return status;
}
/*
* brief: This function is used to add a command to the LCD queue
* param.: (input) the command to be queued
* return: (output) the Error state of the function LCD_ERR if the queue was full and LCD_OK if command has been queued
*/
LCD_ERR_STATUS LCD_u8SendCommand(uint8_t command){
	LCD_QUEUE_ITEM item = {command, COMMAND};
	LCD_ERR_STATUS status = LCD_OK;
	status = LCD_enQueue(item);
	return status;
}
/*
* brief: This function is used to add a data byte to the LCD queue
* param.: (input) the data byte to be queued
* return: (output) the Error state of the function LCD_ERR if the queue was full and LCD_OK if data has been queued
*/
LCD_ERR_STATUS LCD_u8SendData(uint8_t data){
	LCD_QUEUE_ITEM item = {data, DATA};
	LCD_ERR_STATUS status = LCD_OK;
	status = LCD_enQueue(item);
	return status;
}
/*
* brief: This function is used to send a command to the LCD without blocking the application
* param.: (input) the command to be sent
* return: (output) the Error state of the function LCD_ERR if an error happens and LCD_OK if command has been sent and LCD_Busy if
* command hasn't been fully sent yet
*/
static LCD_ERR_STATUS LCD_u8SendCommandPrivate(uint8_t command){
	static LCD_STATE lcd_state = FIRST_NIBBLE;
	uint8_t bit;
	LCD_ERR_STATUS status = LCD_OK;
	switch(lcd_state){
		case FIRST_NIBBLE:
		bit = GET_BIT(command, 4);
		DIO_u8SetPinData(D4_PORT,D4_PIN,bit);
		bit = GET_BIT(command, 5);
		DIO_u8SetPinData(D5_PORT,D5_PIN,bit);
		bit = GET_BIT(command, 6);
		DIO_u8SetPinData(D6_PORT,D6_PIN,bit);
		bit = GET_BIT(command, 7);
		DIO_u8SetPinData(D7_PORT,D7_PIN,bit);
		DIO_u8SetPinData(RS_PORT,RS_PIN,DIO_LOW);
		DIO_u8SetPinData(RW_PORT,RW_PIN,DIO_LOW);
		DIO_u8SetPinData(E_PORT,E_PIN,DIO_HIGH);
		lcd_state = SECOND_NIBBLE;
		status = LCD_BUSY;
		break;
		case SECOND_NIBBLE:
		DIO_u8SetPinData(E_PORT,E_PIN,DIO_LOW);
		bit = GET_BIT(command, 0);
		DIO_u8SetPinData(D4_PORT,D4_PIN,bit);
		bit = GET_BIT(command, 1);
		DIO_u8SetPinData(D5_PORT,D5_PIN,bit);
		bit = GET_BIT(command, 2);
		DIO_u8SetPinData(D6_PORT,D6_PIN,bit);
		bit = GET_BIT(command, 3);
		DIO_u8SetPinData(D7_PORT,D7_PIN,bit);
		DIO_u8SetPinData(RS_PORT,RS_PIN,DIO_LOW);
		DIO_u8SetPinData(RW_PORT,RW_PIN,DIO_LOW);
		DIO_u8SetPinData(E_PORT,E_PIN,DIO_HIGH);
		lcd_state = WAIT;
		status = LCD_BUSY;
		break;
		case WAIT:
		DIO_u8SetPinData(E_PORT,E_PIN,DIO_LOW);
		lcd_state = FIRST_NIBBLE;
		status = LCD_OK;
		break;
		default:
		break;
	}
	return status;
}
/*
* brief: This function is used to send a data character to the LCD without blocking the application
* param.: (input) the data to be sent 
* return: (output) the Error state of the function LCD_ERR if an error happens and LCD_OK if data has been sent and LCD_Busy if
* data hasn't been fully sent yet
*/
LCD_ERR_STATUS LCD_u8SendDataPrivate(uint8_t data) {
	static LCD_STATE lcd_state = FIRST_NIBBLE;
	uint8_t bit;
	LCD_ERR_STATUS status = LCD_OK;
	switch(lcd_state){
		case FIRST_NIBBLE:
		bit = GET_BIT(data, 4);
		DIO_u8SetPinData(D4_PORT,D4_PIN,bit);
		bit = GET_BIT(data, 5);
		DIO_u8SetPinData(D5_PORT,D5_PIN,bit);
		bit = GET_BIT(data, 6);
		DIO_u8SetPinData(D6_PORT,D6_PIN,bit);
		bit = GET_BIT(data, 7);
		DIO_u8SetPinData(D7_PORT,D7_PIN,bit);
		DIO_u8SetPinData(RS_PORT,RS_PIN,DIO_HIGH);
		DIO_u8SetPinData(RW_PORT,RW_PIN,DIO_LOW);
		DIO_u8SetPinData(E_PORT,E_PIN,DIO_HIGH);
		lcd_state = SECOND_NIBBLE;
		status = LCD_BUSY;
		break;
		case SECOND_NIBBLE:
		DIO_u8SetPinData(E_PORT,E_PIN,DIO_LOW);
		bit = GET_BIT(data, 0);
		DIO_u8SetPinData(D4_PORT,D4_PIN,bit);
		bit = GET_BIT(data, 1);
		DIO_u8SetPinData(D5_PORT,D5_PIN,bit);
		bit = GET_BIT(data, 2);
		DIO_u8SetPinData(D6_PORT,D6_PIN,bit);
		bit = GET_BIT(data, 3);
		DIO_u8SetPinData(D7_PORT,D7_PIN,bit);
		DIO_u8SetPinData(RS_PORT,RS_PIN,DIO_HIGH);
		DIO_u8SetPinData(RW_PORT,RW_PIN,DIO_LOW);
		DIO_u8SetPinData(E_PORT,E_PIN,DIO_HIGH);
		lcd_state = WAIT;
		status = LCD_BUSY;
		break;
		case WAIT:
		DIO_u8SetPinData(E_PORT,E_PIN,DIO_LOW);
		lcd_state = FIRST_NIBBLE;
		status = LCD_OK;
		break;
		default:
		break;
	}
	return status;

}

/*
* brief: This function is used to send a string to the LCD
* param.: (input) a pointer to char pointing to the string
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
LCD_ERR_STATUS LCD_u8SendString(uint8_t *str){
	LCD_ERR_STATUS status = LCD_OK;
	if(str == NULL){
		status = LCD_ERR;
	}
	else{
		uint8_t* iterator = str;
		while(*iterator != '\0' && status == LCD_OK){
			status = LCD_u8SendData(*iterator);
			iterator++;
		}	
	}
	return status;

}
/*
* brief: This function is used to send a positive integer to the LCD
* param.: (input) the integer to be sent
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
LCD_ERR_STATUS LCD_u8SendNumber(uint16_t num)
{
	LCD_ERR_STATUS status = LCD_OK;
	uint16_t y = 1;
	do{
		y = (y * 10) + (num % 10);
		num = num /10;
	}while(num > 0);
	
	while(y>1 && status == LCD_OK)
	{
		status = LCD_u8SendData((y%10)+48);
		y=y/10;
	}
	return status;
}
/*
* brief: This function is used to set the cursor at a certain position on the Display
* param.: (input) the row to set the cursor at, should be 0 or 1
* param.: (input) the column to set the cursor at, should be an integer between 0 and 15
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/
LCD_ERR_STATUS LCD_u8SetCursor(uint8_t row, uint8_t col)
{	uint8_t status = LCD_OK;
	if(col > 15){
		status = LCD_ERR;
	}
	else{
		switch (row)
		{
			case 0:
			col |= 0x80;
			break;
			case 1:
			col |= 0xC0;
			break;
			default:
			status = LCD_ERR;
			break;
		}
	}
	if(status == LCD_OK){
		status = LCD_u8SendCommand(col);
	}
	return status;
}
/*
* brief: This function is called back by the timer every 1 ms and checks if the last data/command has been sent completely
*if it was it dequeues new item if the queue isn't empty and start sending it and if it wasn't sent completely
*it continous sending it  
*/
void LCD_callBack(void* vptr){
	uint8_t queue_status;
	static LCD_ERR_STATUS LCD_Status = LCD_OK;
	static LCD_QUEUE_ITEM item;
	if(LCD_Status == LCD_OK){
		queue_status = LCD_deQueue(&item);
		if(queue_status == STD_TYPES_OK){
			if(item.type == COMMAND){
				LCD_Status = LCD_u8SendCommandPrivate(item.data);
			}
			else{
				LCD_Status = LCD_u8SendDataPrivate(item.data);
			}
		}
	}
	else{
		if(item.type == COMMAND){
			LCD_Status = LCD_u8SendCommandPrivate(item.data);
		}
		else{
			LCD_Status = LCD_u8SendDataPrivate(item.data);
		}
	}	
}