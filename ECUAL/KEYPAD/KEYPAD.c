/*
 * KEYPAD.c
 *
 * Created: 1/22/2022 1:31:39 AM
 *  Author: Khaled Ali
 */ 

#include "KEYPAD.h"
#include "../LED/LED.h"
const static uint8_t KEYPAD[KEYPAD_ROWS][KEYPAD_COLS] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
static KEY_STATE key_state = NOT_PRESSED;
static uint8_t volatile debounce = BOUNCING_NOT_DONE;

static KEYPAD_ERR_STATUS KEYPAD_u8ReadKey(uint8_t* key);
/*
* brief: This function is used to initialize pin directions of the keypad as defined in the configurations
* return: (output) the Error status of the function 0 if an error happens and 1 otherwise
*/
KEYPAD_ERR_STATUS KEYPAD_u8Init(void){
	KEYPAD_ERR_STATUS status = KEYPAD_OK;
	//Set Cols direction output
	status = DIO_u8SetPinDirection(COL0_PORT, COL0_PIN, DIO_OUTPUT);
	if(status == KEYPAD_OK){
		status = DIO_u8SetPinDirection(COL1_PORT, COL1_PIN, DIO_OUTPUT);	
	}
	if(status == KEYPAD_OK){
		status = DIO_u8SetPinDirection(COL2_PORT, COL2_PIN, DIO_OUTPUT);
	}
	
	//Set Cols DIO_HIGH
	if(status == KEYPAD_OK){
		status = DIO_u8SetPinData(COL0_PORT, COL0_PIN, DIO_HIGH);
	}
	if(status == KEYPAD_OK){
		status = DIO_u8SetPinData(COL1_PORT, COL1_PIN, DIO_HIGH);
	}
	if(status == KEYPAD_OK){
		status = DIO_u8SetPinData(COL2_PORT, COL2_PIN, DIO_HIGH);
	}
	
	//Set rows direction input with pullup
	if(status == KEYPAD_OK){
		status = DIO_u8SetPinDirection(ROW0_PORT, ROW0_PIN, DIO_INPUT_PULLUP);
	}
	if(status == KEYPAD_OK){
		status = DIO_u8SetPinDirection(ROW1_PORT, ROW1_PIN, DIO_INPUT_PULLUP);
	}
	if(status == KEYPAD_OK){
		status = DIO_u8SetPinDirection(ROW2_PORT, ROW2_PIN, DIO_INPUT_PULLUP);
	}
	return status;
}

KEYPAD_ERR_STATUS KEYPAD_u8GetKey(uint8_t* key){
	KEYPAD_ERR_STATUS status = KEYPAD_OK;
	if(key == NULL){
		status = KEYPAD_ERR;
	}
	else{
		switch(key_state){
			case NOT_PRESSED:
			status = KEYPAD_u8ReadKey(key);
			if(status == KEYPAD_OK && *key != NO_KEY_PRESSED){
				key_state = DEBOUNCING;
			}
			*key = NO_KEY_PRESSED;
			break;
			case DEBOUNCING:
			if(debounce == BOUNCING_DONE){
				debounce = BOUNCING_NOT_DONE;
				status = KEYPAD_u8ReadKey(key);
				key_state = PRESSED;
			}
			else{
				*key = NO_KEY_PRESSED;
			}
			break;
			case PRESSED:
				status = KEYPAD_u8ReadKey(key);
				if(*key == NO_KEY_PRESSED){
					key_state = NOT_PRESSED;
				}
				else{
					*key = NO_KEY_PRESSED;
				}
			default:
			break;
		}
	}
	return status;
}


/*
* brief: This function is used to get the value of the key pressed in the keypad
* param.: (input) a pointer to a variable to hold the key value that was pressed and MAX value if none pressed
* return: (output) the Error status of the function 0 if an error happens and 1 otherwise
*/
static KEYPAD_ERR_STATUS KEYPAD_u8ReadKey(uint8_t* key){
	KEYPAD_ERR_STATUS status = KEYPAD_OK;
	if(key == NULL){
		status = KEYPAD_ERR;
	}
	else{
		uint8_t pin;
		*key = NO_KEY_PRESSED;
		for(uint8_t col = 0; col < KEYPAD_COLS; col++){
			switch(col){
				case  0:
					status = DIO_u8SetPinData(COL0_PORT, COL0_PIN, DIO_LOW);
					break;
				case 1:
					status = DIO_u8SetPinData(COL1_PORT, COL1_PIN, DIO_LOW);
					break;
				case 2:
					status = DIO_u8SetPinData(COL2_PORT, COL2_PIN, DIO_LOW);
					break;
				default:
					break;
			}
			if(status != KEYPAD_OK){
				break;
			}
			for(uint8_t row = 0; row < KEYPAD_ROWS; row++){
				switch(row){
					case  0:
						status = DIO_u8GetPinData(ROW0_PORT, ROW0_PIN, &pin);
						break;
					case 1:
						status = DIO_u8GetPinData(ROW1_PORT, ROW1_PIN, &pin);
						break;
					case 2:
						status = DIO_u8GetPinData(ROW2_PORT, ROW2_PIN, &pin);
						break;
					default:
						break;
				}
				if(pin == DIO_LOW){
					*key = KEYPAD[row][col];
				}
			}
			switch(col){
				case  0:
				status = DIO_u8SetPinData(COL0_PORT, COL0_PIN, DIO_HIGH);
				break;
				case 1:
				status = DIO_u8SetPinData(COL1_PORT, COL1_PIN, DIO_HIGH);
				break;
				case 2:
				status = DIO_u8SetPinData(COL2_PORT, COL2_PIN, DIO_HIGH);
				break;
				default:
				break;
			}
		}
	}
	return status;
}


void KEYPAD_CallBack(void* vptr){
	static uint8_t counter = 0;
	if(key_state == DEBOUNCING){
		counter += 10;
		if(counter == 50){
			debounce = BOUNCING_DONE;
			counter = 0;
		}
	}
}