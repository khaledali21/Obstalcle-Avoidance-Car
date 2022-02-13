/*
 * DIO.c
 *
 *  Created on: Jan 8, 2022
 *      Author: Binary Beasts
 */

#include "../../LIB/Typedef.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/Atmega32.h"
#include "DIO_interface.h"

// function to set direction of pin 
uint8_t DIO_u8SetPinDirection(DIOPort_t u8_PortName, DIOPin_t u8_PinNum,
		DIODir_t u8_PinDir) {
	uint8_t u8ErrorState = STD_TYPES_OK;

	/*Check if the inputs are in the right range*/
	if (u8_PinNum < DIO_PINS_NUMBER && u8_PortName < DIO_PORTS_NUMBER) {
		/*Check which port */
		switch (u8_PortName) {
		case PORTA:
			/*Check which Direction the user wants the pin to be in */
			switch (u8_PinDir) {

			case DIO_INPUT:
				// for input tristate mode ({DDxn, PORTxn} = 0b00)
				CLR_BIT(DDRA_REG, u8_PinNum);
				CLR_BIT(PORTA_REG, u8_PinNum);
				break;
			case DIO_INPUT_PULLUP:
				// for input PULLUP mode ({DDxn, PORTxn,PUD} = 0b010)
				CLR_BIT(SFIOR_REG, PUD_BIT);
				CLR_BIT(DDRA_REG, u8_PinNum);
				SET_BIT(PORTA_REG, u8_PinNum);
				break;
			case DIO_OUTPUT:
				// for OUTPUT mode ({DDxn, PORTxn} = 0b1x)
				SET_BIT(DDRA_REG, u8_PinNum);
				break;
			default:
				// If the input state is not one of the above cases return error state NOK
				u8ErrorState = STD_TYPES_NOK;
			}
			break;
		case PORTB:
			/*Check if the inputs are in the right range*/
			switch (u8_PinDir) {
			case DIO_INPUT:
				// for input tristate mode ({DDxn, PORTxn} = 0b00)
				CLR_BIT(DDRB_REG, u8_PinNum);
				CLR_BIT(PORTB_REG, u8_PinNum);
				break;
			case DIO_INPUT_PULLUP:
				// for input PULLUP mode ({DDxn, PORTxn,PUD} = 0b010)
				CLR_BIT(SFIOR_REG, PUD_BIT);
				CLR_BIT(DDRB_REG, u8_PinNum);
				SET_BIT(PORTB_REG, u8_PinNum);
				break;
			case DIO_OUTPUT:
				// for OUTPUT mode ({DDxn, PORTxn} = 0b1x)
				SET_BIT(DDRB_REG, u8_PinNum);
				break;
			default:
				// If the input state is not one of the above cases return error state NOK
				u8ErrorState = STD_TYPES_NOK;
			}
			break;
		case PORTC:
			switch (u8_PinDir) {
			case DIO_INPUT:
				// for input tristate mode ({DDxn, PORTxn} = 0b00)
				CLR_BIT(DDRC_REG, u8_PinNum);
				CLR_BIT(PORTC_REG, u8_PinNum);
				break;
			case DIO_INPUT_PULLUP:
				// for input PULLUP mode ({DDxn, PORTxn,PUD} = 0b010)
				CLR_BIT(SFIOR_REG, PUD_BIT);
				CLR_BIT(DDRC_REG, u8_PinNum);
				SET_BIT(PORTC_REG, u8_PinNum);
				break;
			case DIO_OUTPUT:
				// for OUTPUT mode ({DDxn, PORTxn} = 0b1x)
				SET_BIT(DDRC_REG, u8_PinNum);
				break;
			default:
				// If the input state is not one of the above cases return error state NOK
				u8ErrorState = STD_TYPES_NOK;
			}
			break;
		case PORTD:
			switch (u8_PinDir) {
			case DIO_INPUT:
				// for input tristate mode ({DDxn, PORTxn} = 0b00)
				CLR_BIT(DDRD_REG, u8_PinNum);
				CLR_BIT(PORTA_REG, u8_PinNum);
				break;
			case DIO_INPUT_PULLUP:
				// for input PULLUP mode ({DDxn, PORTxn,PUD} = 0b010)
				CLR_BIT(SFIOR_REG, PUD_BIT);
				CLR_BIT(DDRD_REG, u8_PinNum);
				SET_BIT(PORTD_REG, u8_PinNum);
				break;
			case DIO_OUTPUT:
				// for OUTPUT mode ({DDxn, PORTxn} = 0b1x)
				SET_BIT(DDRD_REG, u8_PinNum);
				break;
			default:
				// If the input state is not one of the above cases return error state NOK
				u8ErrorState = STD_TYPES_NOK;
			}
			break;
		default:
			// If the input port is not one of the above cases return error state NOK
			u8ErrorState = STD_TYPES_NOK;
		}
	} else {
		// If the input port or input pin is not suitable return error state NOK
		u8ErrorState = STD_TYPES_NOK;
	}
	return u8ErrorState;
}

// function to assign value to pin 
uint8_t DIO_u8SetPinData(DIOPort_t u8_PortName, DIOPin_t u8_PinNum,
		DIODir_t u8_PinValue) {
	uint8_t u8ErrorState = STD_TYPES_OK;
	if (u8_PinNum < DIO_PINS_NUMBER) {
		/*Check which port */
		switch (u8_PortName) {
		case PORTA:
			switch (u8_PinValue) {
			// set or clear bit depend on PinValue
			case DIO_HIGH:
				SET_BIT(PORTA_REG, u8_PinNum);
				break;
			case DIO_LOW:
				CLR_BIT(PORTA_REG, u8_PinNum);
				break;
			default:
				// If not HIGH or LOW return error state NOK
				u8ErrorState = STD_TYPES_NOK;
			}
			break;
		case PORTB:
			switch (u8_PinValue) {
			// set or clear bit depend on PinValue
			case DIO_HIGH:
				SET_BIT(PORTB_REG, u8_PinNum);
				break;
			case DIO_LOW:
				CLR_BIT(PORTB_REG, u8_PinNum);
				break;
			default:
				// If not HIGH or LOW return error state NOK
				u8ErrorState = STD_TYPES_NOK;
			}
			break;
		case PORTC:
			switch (u8_PinValue) {
			// set or clear bit depend on PinValue
			case DIO_HIGH:
				SET_BIT(PORTC_REG, u8_PinNum);
				break;
			case DIO_LOW:
				CLR_BIT(PORTC_REG, u8_PinNum);
				break;
			default:
				// If not HIGH or LOW return error state NOK
				u8ErrorState = STD_TYPES_NOK;
			}
			break;
		case PORTD:
			switch (u8_PinValue) {
			// set or clear bit depend on PinValue
			case DIO_HIGH:
				SET_BIT(PORTD_REG, u8_PinNum);
				break;
			case DIO_LOW:
				CLR_BIT(PORTD_REG, u8_PinNum);
				break;
			default:
				// If not HIGH or LOW return error state NOK
				u8ErrorState = STD_TYPES_NOK;
			}
			break;
		}
	} else {
		// if not suitable port or pin state return error state NOK
		u8ErrorState = STD_TYPES_NOK;
	}
	return u8ErrorState;
}

// function to read value on pin 
uint8_t DIO_u8GetPinData(DIOPort_t u8_PortName, DIOPin_t u8_PinNum,
		uint8_t* pu8_ReturnVar) {
	uint8_t u8ErrorState = STD_TYPES_OK;

	if (u8_PinNum < DIO_PINS_NUMBER && pu8_ReturnVar != NULL) {
		switch (u8_PortName) {
		// get bit value in register to variable depend on port and pin 
		case PORTA:
			*pu8_ReturnVar = GET_BIT(PINA_REG, u8_PinNum);
			break;
		case PORTB:
			*pu8_ReturnVar = GET_BIT(PINB_REG, u8_PinNum);
			break;
		case PORTC:
			*pu8_ReturnVar = GET_BIT(PINC_REG, u8_PinNum);
			break;
		case PORTD:
			*pu8_ReturnVar = GET_BIT(PIND_REG, u8_PinNum);
			break;
		default:
			// if not suitable port return error state NOK
			u8ErrorState = STD_TYPES_NOK;
		}
	} else {
		// if return address not passed or not suitable pin number return error state NOK
		u8ErrorState = STD_TYPES_NOK;
	}

	return u8ErrorState;
}

// function to set direction of pin
uint8_t DIO_u8SetPortDirection(DIOPort_t u8_PortName, DIODir_t u8_Dir) {
	uint8_t u8ErrorState = STD_TYPES_OK;
	switch (u8_PortName) {
	case PORTA:
		switch (u8_Dir) {
		case DIO_INPUT:
			// for input tristate mode ({DDRx, PORTx} = {0x00,0x00})
			DDRA_REG = DIO_PORT_LOW;
			SET_BIT(SFIOR_REG, PUD_BIT);
			break;
		case DIO_INPUT_PULLUP:
			// for input PULLUP mode ( {DDRx, PORTx,PUD} =  {0b0,0x00,0xff} )
			CLR_BIT(SFIOR_REG, PUD_BIT);
			DDRA_REG = DIO_PORT_LOW;
			PORTA_REG = DIO_PORT_HIGH;
			break;
		case DIO_OUTPUT:
			// for input tristate mode ( DDRx = 0xff )
			DDRA_REG = DIO_PORT_HIGH;
			break;
		default:
			// If the input state is not one of the above cases return error state NOK
			u8ErrorState = STD_TYPES_NOK;
		}
		break;
	case PORTB:
		switch (u8_Dir) {
		case DIO_INPUT:
			// for input tristate mode ({DDRx, PORTx} = {0x00,0x00})
			DDRB_REG = DIO_PORT_LOW;
			SET_BIT(SFIOR_REG, PUD_BIT);
			break;
		case DIO_INPUT_PULLUP:
			// for input PULLUP mode ( {DDRx, PORTx,PUD} =  {0b0,0x00,0xff} )
			CLR_BIT(SFIOR_REG, PUD_BIT);
			DDRB_REG = DIO_PORT_LOW;
			PORTB_REG = DIO_PORT_HIGH;
			break;
		case DIO_OUTPUT:
			// for input tristate mode ( DDRx = 0xff )
			DDRB_REG = DIO_PORT_HIGH;
			break;
		default:
			// If the input state is not one of the above cases return error state NOK
			u8ErrorState = STD_TYPES_NOK;
		}
		break;
	case PORTC:
		switch (u8_Dir) {
		case DIO_INPUT:
			// for input tristate mode ({DDRx, PORTx} = {0x00,0x00})
			DDRC_REG = DIO_PORT_LOW;
			SET_BIT(SFIOR_REG, PUD_BIT);
			break;
		case DIO_INPUT_PULLUP:
			// for input PULLUP mode ( {DDRx, PORTx,PUD} =  {0b0,0x00,0xff} )
			CLR_BIT(SFIOR_REG, PUD_BIT);
			DDRC_REG = DIO_PORT_LOW;
			PORTC_REG = DIO_PORT_HIGH;
			break;
		case DIO_OUTPUT:
			// for input tristate mode ( DDRx = 0xff )
			DDRC_REG = DIO_PORT_HIGH;
			break;
		default:
			// If the input state is not one of the above cases return error state NOK
			u8ErrorState = STD_TYPES_NOK;
		}
		break;
	case PORTD:
		switch (u8_Dir) {
		case DIO_INPUT:
			// for input tristate mode ({DDRx, PORTx} = {0x00,0x00})
			DDRD_REG = DIO_PORT_LOW;
			SET_BIT(SFIOR_REG, PUD_BIT);
			break;
		case DIO_INPUT_PULLUP:
			// for input PULLUP mode ( {DDRx, PORTx,PUD} =  {0b0,0x00,0xff} )
			CLR_BIT(SFIOR_REG, PUD_BIT);
			DDRD_REG = DIO_PORT_LOW;
			PORTD_REG = DIO_PORT_HIGH;
			break;
		case DIO_OUTPUT:
			// for input tristate mode ( DDRx = 0xff )
			DDRD_REG = DIO_PORT_HIGH;
			break;
		default:
			// If the input state is not one of the above cases return error state NOK
			u8ErrorState = STD_TYPES_NOK;
		}
		break;
	default:
		// If the input port is not one of the above cases return error state NOK
		u8ErrorState = STD_TYPES_NOK;
	}

	return u8ErrorState;
}

// function to assign value to port
uint8_t DIO_u8SetPortData(DIOPort_t u8_PortName, DIODir_t u8_Value) {
	uint8_t u8ErrorState = STD_TYPES_OK;
	if (u8_Value == DIO_PORT_HIGH || u8_Value == DIO_PORT_LOW) {
		// check if value of port HIGH or LOW and assign it to the port 
		switch (u8_PortName) {
		case PORTA:
			PORTA_REG = u8_Value;
			break;
		case PORTB:
			PORTB_REG = u8_Value;
			break;
		case PORTC:
			PORTC_REG = u8_Value;
			break;
		case PORTD:
			PORTD_REG = u8_Value;
			break;
		default:
			// if input port is not one of the above cases return error state NOK
			u8ErrorState = STD_TYPES_NOK;
		}
	} else {
		// if Value not HIGH or LOW return error state NOK
		u8ErrorState = STD_TYPES_NOK;
	}

	return u8ErrorState;
}

// function to read value on port
uint8_t DIO_u8GetPortData(DIOPort_t u8_PortName, uint8_t* pu8_ReturnVar) {
	uint8_t u8ErrorState = STD_TYPES_OK;
	if (pu8_ReturnVar != NULL) {
		// get port value in register to variable depend on port and pin 
		switch (u8_PortName) {
		case PORTA:
			*pu8_ReturnVar = PORTA_REG;
			break;
		case PORTB:
			*pu8_ReturnVar = PORTB_REG;
			break;
		case PORTC:
			*pu8_ReturnVar = PORTC_REG;
			break;
		case PORTD:
			*pu8_ReturnVar = PORTD_REG;
			break;
		default:
			// if not suitable port return error state NOK
			u8ErrorState = STD_TYPES_NOK;
		}
	} else {
		// if no address passed to function return error state NOK 
		u8ErrorState = STD_TYPES_NOK;
	}

	return u8ErrorState;
}

// function to toggle pin state
uint8_t DIO_u8TogglePinData(DIOPort_t u8_PortName, DIOPin_t u8_PinNum) {

	uint8_t u8ErrorState = STD_TYPES_OK;
	switch (u8_PortName) {
	// toogle bit value depend on port and pin 
	case PORTA:
		Toggle_BIT(PORTA_REG, u8_PinNum);
		break;
	case PORTB:
		Toggle_BIT(PORTB_REG, u8_PinNum);
		break;
	case PORTC:
		Toggle_BIT(PORTC_REG, u8_PinNum);
		break;
	case PORTD:
		Toggle_BIT(PORTD_REG, u8_PinNum);
		break;
	default:
		// if input port is not one of the above cases return error state NOK
		u8ErrorState = STD_TYPES_NOK;
	}

	return u8ErrorState;
}
