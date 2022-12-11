/**
 * @file APP_CONFIG.h
 * @author Youssef Abdelmajeed (youssefabdelmajeed77@gmail.com)
 * @brief APP Pins configuration file 
 * @version 0.1
 * @date 2022-11-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

	/*traffic light */
#define T_GREEN_LED_PIN			0				//PA0

#define T_YELLOW_LED_PIN		1				//PA1

#define T_RED_LED_PIN			2				//PA2

	/*pedestrian*/
#define PEDS_GREEN_LED_PIN		8				//PB0

#define PEDS_YELLOW_LED_PIN		9				//PB1

#define PEDS_RED_LED_PIN		10				//PB2

#define PEDS_BUTTON				26				//INT0 
	
	/* Intervals */
#define TRAFFIC_INTERVAL 5000					// interval to switch between light states in ms

#define YELLOW_LIGHT_BLINKING_INTERVAL 250		// interval between Yellow led toggle in ms 

#endif /* APP_CONFIG_H_ */