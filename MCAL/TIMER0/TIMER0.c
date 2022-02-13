/*
 * TIMER0.c
 *
 *  Created on: Jan 12, 2022
 *      Author: Alhassan Mohsen
 */

#include "TIMER0_interface.h"
#include "TIMER0_cfg.h"
#include "TIMER0_prv.h"
#include "../../ECUAL/LED/LED.h"
static volatile TIM0_Config_t*	gst_TIM0Config= NULL;
void (*gv_OVFCallBackFun)(void)=NULL;
void (*gv_OC0CallBackFun)(void)=NULL;


ErrorState_t TIM0_u8Init(TIM0_Config_t * pst_TIMConfig)
{
	uint8_t u8ErrorState=TIM0_OK;
	
	//check if the input pointer is not a pointer to null first
	if (pst_TIMConfig != NULL)
	{
		// Set the global timer configuration to the input configuration to be used in the other timer functions
		gst_TIM0Config = pst_TIMConfig;

		//Define the mode of the timer
		switch(pst_TIMConfig->mode)
		{
		case TIM0_NORMAL:	// if timer mode is selected to be Normal then set the WGM(0:1) bits to 0
			CLR_BIT(TCCR0_REG,WGM00_BIT);
			CLR_BIT(TCCR0_REG,WGM01_BIT);
			break;
		case TIM0_CTC:	// if timer mode is selected to be CTC then set the WGM(0:1) bits to 2
			CLR_BIT(TCCR0_REG,WGM00_BIT);
			SET_BIT(TCCR0_REG,WGM01_BIT);
			break;
		case TIM0_FPWM_INVERTING:
			// if timer mode is selected to be FAST PWM INVERTED then set the WGM(0:1) bits to 3 and COM(0:1)Bits to 3
			SET_BIT(TCCR0_REG,WGM00_BIT);
			SET_BIT(TCCR0_REG,WGM01_BIT);
			SET_BIT(TCCR0_REG,COM00_BIT);
			SET_BIT(TCCR0_REG,COM01_BIT);
			break;
		case TIM0_FPWM_NON_INVERTING:
			// if timer mode is selected to be FAST PWM NON INVERTED then set the WGM(0:1) bits to 3 and COM(0:1)Bits to 2
			SET_BIT(TCCR0_REG,WGM00_BIT);
			SET_BIT(TCCR0_REG,WGM01_BIT);
			CLR_BIT(TCCR0_REG,COM00_BIT);
			SET_BIT(TCCR0_REG,COM01_BIT);
			break;
		case TIM0_PCPWM_INVERTING:
			// if timer mode is selected to be PHASE CORRECT PWM INVERTED then set the WGM(0:1) bits to 1 and COM(0:1)Bits to 3
			SET_BIT(TCCR0_REG,WGM00_BIT);
			CLR_BIT(TCCR0_REG,WGM01_BIT);
			SET_BIT(TCCR0_REG,COM00_BIT);
			SET_BIT(TCCR0_REG,COM01_BIT);
			break;
		case TIM0_PCPWM_NON_INVERTING:
			// if timer mode is selected to be PHASE CORRECT PWM non INVERTED then set the WGM(0:1) bits to 1 and COM(0:1)Bits to 2
			SET_BIT(TCCR0_REG,WGM00_BIT);
			CLR_BIT(TCCR0_REG,WGM01_BIT);
			CLR_BIT(TCCR0_REG,COM00_BIT);
			SET_BIT(TCCR0_REG,COM01_BIT);
			break;
		default:
			// if the input mode is something else return error state TIM0_WRONG_MODE
			u8ErrorState = TIM0_WRONG_MODE;
		}

		// Set the starting of counter to initial value  defined in the configuration file
		TCNT0_REG = TIMER0_INITIAL_START;
	}
	else{
		// if the input pointer to configuration structure is pointing to null then return error TIM0_NULL_INPUT
		u8ErrorState= TIM0_NULL_INPUT;
	}
	return u8ErrorState;
}
ErrorState_t TIM0_u8SetStart(uint8_t u8StartingPoint)
{
	uint8_t u8ErrorState= TIM0_OK;

	// take the input value and initialize the counter with it
	TCNT0_REG = u8StartingPoint;

	return u8ErrorState;
}
ErrorState_t TIM0_u8GetCounts(uint8_t* pu8_ReturnedCounts)
{
	uint8_t u8ErrorState= TIM0_OK;


	if (pu8_ReturnedCounts != NULL) // check that the pointer is not wild pointer
	{
		// if not get the value of the TCNT0 register containing the number of counts
		*pu8_ReturnedCounts = TCNT0_REG;
	}
	else {
		// if it is a wild pointer return error TIM0_NULL_INPUT
		u8ErrorState = TIM0_NULL_INPUT;
	}
	return u8ErrorState;

}
ErrorState_t TIM0_u8SetCompareValue(uint8_t u8SetCompareValue)
{
	uint8_t u8ErrorState = TIM0_OK;
	/*
	if (gst_TIM0Config != NULL)
	{
		if (gst_TIM0Config->mode == TIM0_NORMAL || gst_TIM0Config->mode == TIM0_CTC )
		{
			// if the timer mode is a non pwm mode then you need to wait until the timer overflow to update the OCR to avoid any glitchs
			while (TCNT0_REG < TIMER0_MAX);
			OCR0_REG = u8SetCompareValue;
		}else
		{
			// else it is a PWM mode then you don't need to wait because the OCR is double buffered in PWM modes
			OCR0_REG = u8SetCompareValue;
		}
	}else
	{
		// if the global Timer structure is null the return error TIM0_NOT_INITILIZED
		u8ErrorState = TIM0_NOT_INITILIZED;
	}
	*/
	OCR0_REG = u8SetCompareValue;
	return u8ErrorState;
}
ErrorState_t TIM0_u8EnableOVFInterrupt(void (*vCallBackFun)(void))
{
	uint8_t u8ErrorState = TIM0_OK;

	if (vCallBackFun != NULL) // check if the pointer is wild
	{
		//if not set the call back function and enable the global interrupt then enable the OVF interrupt
		gv_OVFCallBackFun = vCallBackFun;
		SET_BIT(SREG_REG,I_BIT);
		SET_BIT(TIMSK_REG,TOIE0_BIT);
	}else
	{
		u8ErrorState = TIM0_NULL_INPUT;
	}

	return u8ErrorState;
}
ErrorState_t TIM0_u8EnableOCInterrupt (void (*vCallBackFun)(void))
{
	uint8_t u8ErrorState = TIM0_OK;

	if (vCallBackFun != NULL) // check if the pointer is wild
	{
		//if not set the call back function and enable the global interrupt then enable the OVF interrupt
		gv_OC0CallBackFun = vCallBackFun;
		SET_BIT(SREG_REG,I_BIT);
		SET_BIT(TIMSK_REG,OCIE0_BIT);
	}else
	{
		u8ErrorState = TIM0_NULL_INPUT;
	}

	return u8ErrorState;
}
ErrorState_t TIM0_u8TimerStart(void)
{
	uint8_t u8ErrorState = TIM0_OK;
	
	if (gst_TIM0Config != NULL)
	{
		//check if the timer is initialized
		// if yes then start the counter by setting the clock source to a non zero value depending on the timer configuration
		switch (gst_TIM0Config->clkSource)
		{
		case NO_CLK: // if the clock mode is chosen as NO_CLk we set the CS(0:2) BITS to 0
			CLR_BIT(TCCR0_REG, CS00_BIT);
			CLR_BIT(TCCR0_REG, CS01_BIT);
			CLR_BIT(TCCR0_REG, CS02_BIT);
			break;
		case NO_PRESCALAR:// if the clock mode is chosen as NO_PRESCALAR we set the CS(0:2) BITS to 1
			SET_BIT(TCCR0_REG, CS00_BIT);
			CLR_BIT(TCCR0_REG, CS01_BIT);
			CLR_BIT(TCCR0_REG, CS02_BIT);		
			break;
		case PRESCALAR_8:// if the clock mode is chosen as PRESCALAR_8 we set the CS(0:2) BITS to 2
			CLR_BIT(TCCR0_REG, CS00_BIT);
			SET_BIT(TCCR0_REG, CS01_BIT);
			CLR_BIT(TCCR0_REG, CS02_BIT);
			break;
		case PRESCALAR_64:// if the clock mode is chosen as PRESCALAR_64 we set the CS(0:2) BITS to 3
			SET_BIT(TCCR0_REG, CS00_BIT);
			SET_BIT(TCCR0_REG, CS01_BIT);
			CLR_BIT(TCCR0_REG, CS02_BIT);
			break;
		case PRESCALAR_256:// if the clock mode is chosen as PRESCALAR_256 we set the CS(0:2) BITS to 4
			CLR_BIT(TCCR0_REG, CS00_BIT);
			CLR_BIT(TCCR0_REG, CS01_BIT);
			SET_BIT(TCCR0_REG, CS02_BIT);
			break;
		case PRESCALAR_1024:// if the clock mode is chosen as PRESCALAR_1024 we set the CS(0:2) BITS to 5
			SET_BIT(TCCR0_REG, CS00_BIT);
			CLR_BIT(TCCR0_REG, CS01_BIT);
			SET_BIT(TCCR0_REG, CS02_BIT);
			break;
		case EXT_FALLING:// if the clock mode is chosen as EXT_FALLING we set the CS(0:2) BITS to 6
			CLR_BIT(TCCR0_REG, CS00_BIT);
			SET_BIT(TCCR0_REG, CS01_BIT);
			SET_BIT(TCCR0_REG, CS02_BIT);
			break;
		case EXT_RISING:// if the clock mode is chosen as EXT_RISING we set the CS(0:2) BITS to 7
			SET_BIT(TCCR0_REG, CS00_BIT);
			SET_BIT(TCCR0_REG, CS01_BIT);
			SET_BIT(TCCR0_REG, CS02_BIT);
			break;
		default:
			u8ErrorState = TIM0_UNDEFINED_CLK_STATE;
		}

	}else{

		u8ErrorState = TIM0_NOT_INITILIZED;
	}

	return u8ErrorState;
}
ErrorState_t TIM0_u8TimerStop(void)
{
	uint8_t u8ErrorState = TIM0_OK;

	if (gst_TIM0Config != NULL ) // check the timer is initialized
	{
		// Stop the timer without de-initialize  it by setting the clock source bits to 0 choosing no clock mode
		CLR_BIT(TCCR0_REG, CS00_BIT);
		CLR_BIT(TCCR0_REG, CS01_BIT);
		CLR_BIT(TCCR0_REG, CS02_BIT);
	}
	else{
		u8ErrorState = TIM0_NOT_INITILIZED;
	}

	return u8ErrorState;
}
ErrorState_t TIM0_u8DisableOVFInterrupt()
{
	uint8_t u8ErrorState = TIM0_OK;
	gv_OVFCallBackFun = NULL;
	CLR_BIT(TIMSK_REG,TOIE0_BIT);
	return u8ErrorState;
}
ErrorState_t TIM0_u8DisableOCInterrupt ()
{
	uint8_t u8ErrorState = TIM0_OK;
	gv_OC0CallBackFun = NULL;
	CLR_BIT(TIMSK_REG,OCIE0_BIT);
	return u8ErrorState;
}
ErrorState_t TIM0_u8Deinit(void)
{
	ErrorState_t u8ErrorState = TIM0_OK;
	if (gst_TIM0Config != NULL)
	{
		// Setting the control register of the timer to its reset value which stop the timer and deintialize it
		TCCR0_REG = 0;
		// making the TIM0 config pointing to NULL indicating that there no configuration active for this timer
		gst_TIM0Config = NULL;
	}else
	{
		u8ErrorState = TIM0_NOT_INITILIZED;
	}
	return u8ErrorState;
}

void __vector_10(void){

	if (gv_OC0CallBackFun != NULL)
	{
		gv_OC0CallBackFun();
	}
}

void __vector_11(void){

	if (gv_OVFCallBackFun != NULL)
	{
		gv_OVFCallBackFun();
	}
}


/**
 * @TODO : A function to configure PWM Duty Cycle
 */
//ErrorState_t TIM0_u8SetPWMDutyCycle(uint8_t u8DutyCycle);



