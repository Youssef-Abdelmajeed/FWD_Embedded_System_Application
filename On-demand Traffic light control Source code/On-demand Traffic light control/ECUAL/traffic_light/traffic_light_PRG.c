/**
 * @file traffic_light_PRG.c
 * @author Youssef Abdelmajeed (youssefabdelmajeed77@gmail.com)
 * @brief traffic light Implementation file 
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_INT.h"
#include "traffic_light_INT.h"

void TRAFFIC_LIGHT_Init(ST_TrafficLight_t *traffic_light)
{
	/* Set traffic light pins to be output */
	DIO_setPinDirection(traffic_light->GREEN_Pin,OUTPUT) ; 
	DIO_setPinDirection(traffic_light->YELLOW_Pin,OUTPUT) ;
	DIO_setPinDirection(traffic_light->RED_Pin,OUTPUT) ;
}

void TRAFFIC_LIGHT_Drive(ST_TrafficLight_t * trafficLight , EN_LightState_t state) 
{
	switch(state)
	{
	case GREEN:
		/* turn only green led */
		DIO_setPinValue(trafficLight->GREEN_Pin,HIGH) ; 
		
		break;
	case YELLOW:
		/* Toggle only yellow led */
		DIO_setPinValue(trafficLight->YELLOW_Pin,TOGGLE) ;
		break;
	case RED:
		/* turn only red led */
		DIO_setPinValue(trafficLight->RED_Pin,HIGH) ;
		break;
	
	default:
		/* turn off all  */
		DIO_setPinValue(trafficLight->GREEN_Pin,LOW) ;
		DIO_setPinValue(trafficLight->YELLOW_Pin,LOW) ;
		DIO_setPinValue(trafficLight->RED_Pin,LOW) ;
		break;
	}

}


