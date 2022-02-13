/*
 * KEYPAD.h
 *
 * Created: 1/22/2022 1:31:51 AM
 *  Author: Khaled Ali
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../LIB/Typedef.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "KEYPAD_cfg.h"

#define NO_KEY_PRESSED 0xFF

#define DEBOUNCING_DELAY 50

#define BOUNCING_DONE 1

#define BOUNCING_NOT_DONE 0
typedef enum{
	NOT_PRESSED,
	DEBOUNCING,
	PRESSED
}KEY_STATE;

typedef enum{
	KEYPAD_ERR,
	KEYPAD_OK
}KEYPAD_ERR_STATUS;


KEYPAD_ERR_STATUS KEYPAD_u8Init(void);

KEYPAD_ERR_STATUS KEYPAD_u8GetKey(uint8_t* key);

void KEYPAD_CallBack(void*);
#endif /* KEYPAD_H_ */