/**
 * @file BUTTON_INT.c
 * @author Youssef Abdelmajeed (youssefabdelmajeed77@gmail.com)
 * @brief Button Implementation file 
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../../MCAL/DIO/DIO_INT.h"
#include "Button_INT.h"

void Button_Init(ST_Button_t * button)
{
	DIO_setPinDirection(button->buttonPin,INPUT) ;
	button->buttonPressState =NoAction ;
	button->lastButtonState = LOW ;
	button-> isLongPress = 0 ;
}

void Button_readState(ST_Button_t * button) 
{
	/* Time since the millis timer started */
	millis_t currentMillis = Millis_get() ;
	
	button->buttonPressState =NoAction ;
	/* Check for debouncing  */
	if(currentMillis - button->lastReadingTime > successiveReadingInterval) {
		
		/*get the current button reading */
		uint8_t buttonState = DIO_getPinValue(button->buttonPin);

		/*if the button was pressed for the first time and the button wasn't pressed for a long time */
		if (buttonState == HIGH && button->lastButtonState  == LOW && !button->isLongPress) {
			button->buttonPressTime = currentMillis;
			button->lastButtonState  = HIGH;
			button->buttonPressState = Pressing ;
		}

		// get how long the button has been pressed
		button->buttonPressedTime = currentMillis - button->buttonPressTime;

		/* if the button is pressed and button pressed time >= the long press interval (1 s) */
		if (buttonState == HIGH && !button->isLongPress && button->buttonPressedTime >= isLongPressInterval) {
			/* set the button long press flag */
			button->isLongPress = 1;
			/* set button pressed state to be a long press*/
			button->buttonPressState = LongPress;
		}
		
		/* if the button current state was low and last was high the button is released */
		if (buttonState == LOW && button->lastButtonState  == HIGH) {
			
			/*rest last button state */
			button->lastButtonState  = LOW;
			
			/*rest long press flag */
			button->isLongPress = 0;
			
			/* set button pressed state to be released */
			button->buttonPressState = Released;
			/*if the button is released before the long press interval then the button press is a short press */
			if (button->buttonPressedTime < isLongPressInterval) {
				button->buttonPressState = ShortPress;
			}
		}
		
		/*set the last time to the current time to get to the next iteration */
		button->lastReadingTime = currentMillis;
	}

}


