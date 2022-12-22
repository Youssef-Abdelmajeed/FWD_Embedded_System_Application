/*
 * button_TEST.c
 *
 * Created: 12/22/2022 9:49:36 AM
 * Author : Youssef Abdelmajeed
 */ 

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "DIO/DIO_INT.h"
#include "MILLIS/MILLIS_INT.h"
#include "button/Button_INT.h"

int main(void)
{
	ST_Button_t button1 ={.buttonPin= PB0} ; 
	Button_Init(&button1);
	DIO_setPinDirection(PA0,OUTPUT) ;
	Millis_Init() ;
    while (1) 
    {
		Button_readState(&button1) ; /*update button press state */
		
		if(button1.buttonPressState == ShortPress)
		{
			DIO_setPinValue(PA0,HIGH) ;
		}
		else if(button1.buttonPressState == LongPress)
		{
			DIO_setPinValue(PA0,LOW) ;
		}
		
    }
}

