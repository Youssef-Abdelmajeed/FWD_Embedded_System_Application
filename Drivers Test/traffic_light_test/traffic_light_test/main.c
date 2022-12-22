/*
 * traffic_light_test.c
 *
 * Created: 12/22/2022 10:31:49 AM
 * Author : Youssef Abdelmajeed
 */ 
#include "DIO/DIO_INT.h"
#include "MILLIS/MILLIS_INT.h"
#include "Traffic_light/traffic_light_INT.h"

int main(void)
{
	ST_TrafficLight_t traffic_light1 = {.GREEN_Pin=PA0, .YELLOW_Pin=PA1,.RED_Pin=PA2};
	TRAFFIC_LIGHT_Init(&traffic_light1) ;
	Millis_Init();
    millis_t last_time = 0 ; 
	uint8_t state = 0 ;
	while (1) 
    {
		millis_t current_time = Millis_get() ; 
		state = (state>2)? 0 : state ;
		if(current_time-last_time>=1000)	
		{
			TRAFFIC_LIGHT_Drive(&traffic_light1,OFF) ;
			TRAFFIC_LIGHT_Drive(&traffic_light1,state++) ;
			last_time = current_time ;
		}
	}
}

