/**
 * @file traffic_light_INT.h
 * @author Youssef Abdelmajeed (youssefabdelmajeed77@gmail.com)
 * @brief traffic light Interface file
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef TRAFFIC_LIGHT_H_
#define TRAFFIC_LIGHT_H_
#include "../../LIB/STD_TYPES.h"

/* Traffic light struct */
typedef struct ST_TrafficLight
{
	uint8_t GREEN_Pin ; 
	uint8_t YELLOW_Pin;
	uint8_t RED_Pin ;
}ST_TrafficLight_t;

/* Traffic Light States */
typedef enum  EN_LightState 
{
	GREEN, YELLOW, RED, OFF
}EN_LightState_t;  

/**
 * @brief Initialize traffic light pins 
 * 
 * @param trafficLight traffic light object 
 */
void TRAFFIC_LIGHT_Init(ST_TrafficLight_t * trafficLight);

/**
 * @brief Drive a traffic light with light states
 * 
 * @param trafficLight traffic light object 
 *
 * @param state light states [GREEN, YELLOW, RED, OFF]
 */
void TRAFFIC_LIGHT_Drive(ST_TrafficLight_t * trafficLight , EN_LightState_t state) ;

#endif /* TRAFFIC_LIGHT_H_ */