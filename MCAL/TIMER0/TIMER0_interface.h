/*
 * TIMER0_interface.h
 *
 *  Created on: Jan 15, 2022
 *      Author: vip
 */

#ifndef MCAL_TIMER0_TIMER0_INTERFACE_H_
#define MCAL_TIMER0_TIMER0_INTERFACE_H_

#include "../../LIB/Typedef.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/Atmega32.h"

/**
 * Defines the Possible Error States of the Timer0 Driver
 *
 */
typedef enum{
	TIM0_OK = 1,            //!< No error happened
	TIM0_NULL_INPUT=252,    //!< Input a null pointer to the function
	TIM0_WRONG_MODE,        //!< Entered a mode that timer0 doesn't support review TIM0_Mode_t enum for the supported modes
	TIM0_NOT_INITILIZED,    //!< The function require to intialize the timer first
	TIM0_UNDEFINED_CLK_STATE//!< Entered a clock mode that timer0 doesn't support review ClkSource_t enum for the supported modes
}ErrorState_t;

/**
 * @enum
 * Defines the possibles modes of TIMER0
 */
typedef enum{
	TIM0_NORMAL,             //!< Normal Mode
	TIM0_CTC,                //!< Clear Timer on Compare Mode
	TIM0_FPWM_NON_INVERTING, //!< Fast Non inverting PWM
	TIM0_FPWM_INVERTING,     //!< Fast  inverting PWM
	TIM0_PCPWM_NON_INVERTING,//!< Phase Correct Non inverting PWM
	TIM0_PCPWM_INVERTING,    //!< Phase Correct inverting PWM
}TIM0_Mode_t;

/**
 * @enum
 * Defines the Possible CLk Sources of TIMER0
 */
typedef enum{
	NO_CLK,        //!< No clock source meaning that the timer is inactive
	NO_PRESCALAR,  //!< System Clock with no pre-scalar    applied
	PRESCALAR_8,   //!< System Clock with  pre-scalar 8    applied
	PRESCALAR_64,  //!< System Clock with  pre-scalar 64   applied
	PRESCALAR_256, //!< System Clock with  pre-scalar 256  applied
	PRESCALAR_1024,//!< System Clock with  pre-scalar 1024 applied
	EXT_FALLING,   //!< External Falling Edge Trigger on T0 Pin
	EXT_RISING     //!< External Rising Edge Trigger on T0 Pin
}ClkSource_t;

/**
 * @struct
 * Structure contains the configuration of Timer0
 *
 */
typedef struct{
	TIM0_Mode_t mode;
	uint8_t clkSource;
}TIM0_Config_t;


/**
 * @fn ErrorState_t TIM0_u8Init(TIM0_Config_t * pst_TIMConfig);
 * @brief this function is used to initialize timer0
 * @param pst_TIMConfig : a pointer to a structure contain the configuration information need to initialize the timer
 * @return return a number from 1 - 255 represent the error state of the system and can be
 * 1  : TIM0_OK
 * 253: TIM0_WRONG_MODE
 * 252: TIM0_NULL_INPUT
 *
 */
ErrorState_t TIM0_u8Init(TIM0_Config_t * pst_TIMConfig);

/**
 * @fn ErrorState_t TIM0_u8SetStart(uint8_t u8StartingPoint);
 * @brief this function is used to change the beginning of the counting which is initialized to TIMER0_INITIAL_START in the configuration file
 * @param u8StartingPoint : a number between 0 - 255 represent the number you want to start counting from
 * @return return a number from 1 - 255 represent the error state of the system and can be
 * 1  : TIM0_OK
 */
ErrorState_t TIM0_u8SetStart(uint8_t u8StartingPoint);

/**
 * @fn ErrorState_t TIM0_u8GetCounts(uint8_t* pu8_ReturnedCounts);
 * @brief this function is used to read the number of counts in the counter/timer right now
 * @param pu8_ReturnedCounts : a pointer to a uint8_t number that will hold the number of counts
 * @return return a number from 1 - 255 represent the error state of the system and can be
 * 1  : TIM0_OK
 * 252: TIM0_NULL_INPUT
 */
ErrorState_t TIM0_u8GetCounts(uint8_t* pu8_ReturnedCounts);

/**
 * @fn ErrorState_t TIM0_u8SetCompareValue(uint8_t u8SetCompareValue);
 * @brief this function is used to set a value to compare the number of counts with
 * @param u8SetCompareValue : a number between 0 - 255
  * @return return a number from 1 - 255 represent the error state of the system and can be
 * 1  : TIM0_OK
 * 254: TIM0_NOT_INITILIZED
 */
ErrorState_t TIM0_u8SetCompareValue(uint8_t u8SetCompareValue);

/**
 * @fn ErrorState_t TIM0_u8EnableOVFInterrupt(void (*vCallBackFun)(void))
 * @brief this function is used to enable and configure the over flow interrupt of timer 0
 * @param vCallBackFun : a pointer to function that contain the logic wanted to be performed on the interrupt ISR
  * @return return a number from 1 - 255 represent the error state of the system and can be
 * 1  : TIM0_OK
 * 252: TIM0_NULL_INPUT
 */
ErrorState_t TIM0_u8EnableOVFInterrupt(void (*vCallBackFun)(void));

/**
 * @fn ErrorState_t TIM0_u8EnableOCInterrupt(void (*vCallBackFun)(void))
 * @brief this function is used to enable and configure the Compare match interrupt of timer 0
 * @param vCallBackFun : a pointer to function that contain the logic wanted to be performed on the interrupt ISR
  * @return return a number from 1 - 255 represent the error state of the system and can be
 * 1  : TIM0_OK
 * 252: TIM0_NULL_INPUT
 */
ErrorState_t TIM0_u8EnableOCInterrupt (void (*vCallBackFun)(void));
/**
 * @fn ErrorState_t TIM0_u8DisableOVFInterrupt(void (*vCallBackFun)(void))
 * @brief this function is used to disable and configure the overflow interrupt of timer 0
 */
ErrorState_t TIM0_u8DisableOVFInterrupt(void);
/**
 * @fn ErrorState_t TIM0_u8DisableOCInterrupt(void (*vCallBackFun)(void))
 * @brief this function is used to disable and configure the compare match interrupt of timer 0
 */
ErrorState_t TIM0_u8DisableOCInterrupt (void);

/**
 * @fn ErrorState_t TIM0_u8TimerStart(void)
 * @brief This function is used to start the timer counting process with previously initialized configurations
  * @return return a number from 1 - 255 represent the error state of the system and can be
 * 1  : TIM0_OK
 * 254: TIM0_NOT_INITILIZED
 * 255: TIM0_UNDEFINED_CLK_STATE
 */
ErrorState_t TIM0_u8TimerStart(void);

/**
 * @fn ErrorState_t TIM0_u8TimerStop(void)
 * @brief This function is used to start the timer counting process with previously initialized configurations
  * @return return a number from 1 - 255 represent the error state of the system and can be
 * 1  : TIM0_OK
 * 254: TIM0_NOT_INITILIZED
 */
ErrorState_t TIM0_u8TimerStop(void);

/**
 * @fn
 * @brief This function is used to deinitialize timer0
 * @return a number from 1 - 255 represent the error state of the function and can be
 *  1 : TIM0_OK
 *  254: TIM0_NOT_INITILIZED
 */
ErrorState_t TIM0_u8Deinit(void);

/**
 * @TODO : A function to configure PWM Duty Cycle
 */
ErrorState_t TIM0_u8SetPWMDutyCycle(uint8_t u8DutyCycle);




#endif /* MCAL_TIMER0_TIMER0_INTERFACE_H_ */
