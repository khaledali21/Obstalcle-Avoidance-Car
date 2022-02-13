/*
 * LCD.h
 *
 * Created: 1/17/2022 12:19:20 AM
 *  Author: Khaled Ali
 */

#ifndef LCD_H_
#define LCD_H_

#include "../../LIB/Typedef.h"
#include "LCD_cfg.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../LIB/BIT_Math.h"
#define LCD_PERIOD 1
typedef enum{
	FIRST_NIBBLE,
	SECOND_NIBBLE,
	WAIT
}LCD_STATE;


typedef enum{
	LCD_ERR,
	LCD_OK,
	LCD_BUSY
}LCD_ERR_STATUS;
LCD_ERR_STATUS LCD_u8Init(void);

LCD_ERR_STATUS LCD_u8SendCommand(uint8_t command);

LCD_ERR_STATUS LCD_u8SendData(uint8_t data);
LCD_ERR_STATUS LCD_u8SendNumber(uint16_t num);
LCD_ERR_STATUS LCD_u8SendString(uint8_t *str);
LCD_ERR_STATUS LCD_u8SetCursor(uint8_t row, uint8_t col);
void LCD_callBack(void*);
#endif /* LCD_H_ */
