/*
 * DIO_TEST.c
 *
 * Created: 12/22/2022 7:41:54 AM
 * Author : Youssef Abdelmajeed 
 */ 


#define F_CPU 1000000UL

#include "DIO_INT.h"
#include <util/delay.h>

#define debug 1 // 0 to test input , 1 to test output

void DIO_setPinDirection_test(EN_Directions_t direction)
{
	for (uint8_t i = 0 ; i<32 ; i++)
	{
		DIO_setPinDirection(i,direction) ;
	}
}

void DIO_setPinValue_test(EN_Values_t value)
{
	for (uint8_t i = 0 ; i<32 ; i++)
	{
		DIO_setPinValue(i,value) ;
		_delay_ms(100) ;
	}
}
void DIO_setPortDirection_test(EN_Directions_t direction)
{
	DIO_setPortDirection(PORTA,direction) ;
	DIO_setPortDirection(PORTB,direction) ;
	DIO_setPortDirection(PORTC,direction) ;
	DIO_setPortDirection(PORTD,direction) ;
}


int main(void)
{
	#if debug == 1 
	//DIO_setPortDirection_test(OUTPUT) ; 
	DIO_setPinDirection_test(OUTPUT) ;
    while (1) 
    {
		DIO_setPinValue_test(TOGGLE) ;
		//DIO_setPinValue_test(HIGH) ;
		//DIO_setPinValue_test(LOW) ;
    }
	#endif /* debug 1*/
	
	#if debug == 0 
	DIO_setPinDirection(PB0,INPUT);
	DIO_setPinDirection(PA0,OUTPUT);
	uint8_t switchRead  = 0 ;
	while(1)
	{
		switchRead = DIO_getPinValue(PB0) ; 
		DIO_setPinValue(PA0,switchRead);
	}
	#endif /* debug 0*/
}
