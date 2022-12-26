/**
 * @file BUTTON_INT.c
 * @author Youssef Abdelmajeed (youssefabdelmajeed77@gmail.com)
 * @brief Button Interface file 
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BUTTON_INT_H_
#define BUTTON_INT_H_
#include "../../MCAL/MILLIS/MILLIS_INT.h"

/* button general info */
#define successiveReadingInterval  50                      // Time between two successive readings of a button
#define isLongPressInterval 1000						  // Time to indicate if the pressed button is long pressed
  
/*button states */
typedef enum En_ButtonPressState
{
	NoAction, Pressing ,Released, ShortPress , LongPress
}En_ButtonPressState_t ;

/* button object */
typedef struct ST_Button
{
	uint8_t buttonPin ;							// button pin
	En_ButtonPressState_t buttonPressState;
	uint8_t lastButtonState  ;
	uint8_t isLongPress ;							// True if the button was pressed for a long time
	millis_t buttonPressTime;					// The time when the button was in pressing state
	millis_t lastReadingTime;					// Time of the last button press
	millis_t buttonPressedTime;                 // how long the button was pressed
}ST_Button_t;

/**
 * @brief initialize a button object 
 * 
 * @param button a ST_Button object 
 *
 */
void Button_Init(ST_Button_t * button) ;

/**
 * @brief read button object state 
 * 
 * @param button a ST_Button object 
 *
 */
void Button_readState(ST_Button_t * button) ;


#endif /* BUTTON_INT_H_ */