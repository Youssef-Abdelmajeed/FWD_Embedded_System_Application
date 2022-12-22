/*
 * TIMERS_AND_MILLIS_TEST.c
 *
 * Created: 12/22/2022 9:06:06 AM
 * Author : Youssef Abdelmajeed
 */ 


#include "DIO/DIO_INT.h"
#include "MILLIS/MILLIS_INT.h"

int main(void)
{
	DIO_setPortDirection(PA0,OUTPUT) ; 
	DIO_setPinDirection(PB0 ,OUTPUT) ; 
	Millis_Init() ;
	millis_t last_time_event1 = 0 ,last_time_event2 ;
    while (1) 
    {
		millis_t current_time = Millis_get() ; 
		if(current_time-last_time_event1 >= 500)
		{
			DIO_setPinValue(PA0,TOGGLE) ;
			last_time_event1 = current_time ; 
		}
		else if (current_time-last_time_event2>=1000)
		{
			DIO_setPinValue(PB0,TOGGLE) ;
			last_time_event2 = current_time ;
		}
    }
}

