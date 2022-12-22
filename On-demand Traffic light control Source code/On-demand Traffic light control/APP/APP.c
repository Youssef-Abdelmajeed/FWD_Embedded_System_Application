/**
 * @file APP.C
 * @author Youssef Abdelmajeed (youssefabdelmajeed77@gmail.com)
 * @brief  On-demand Traffic light control Application Implementation file 
 * @version 0.1
 * @date 2022-11-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#define F_CPU 1000000UL 
#include "../LIB/STD_TYPES.h"
#include "../MCAL/MILLIS/MILLIS_INT.h"
#include "../ECUAL/traffic_light/traffic_light_INT.h"
#include "../ECUAL/button/Button_INT.h"
#include "APP_CONFIG.h"
#include "APP.h"

/* initialize the current mode to be in normal mode */
EN_modes_t currentMode = normal ;

/* normal traffic light sequence */
EN_LightState_t normal_seq[4] = {GREEN,YELLOW,RED,YELLOW} ;

/* current traffic light state */
EN_LightState_t currentState  ;

/* pedestrian sign button */
ST_Button_t PEDs_button = {.buttonPin = PEDS_BUTTON};


/* define both traffic light and PEDS sign */
ST_TrafficLight_t Traffic_light = {T_GREEN_LED_PIN ,T_YELLOW_LED_PIN,T_RED_LED_PIN} ,Peds_sign ={PEDS_GREEN_LED_PIN,PEDS_YELLOW_LED_PIN,PEDS_RED_LED_PIN} ;

/* get only the short click of the PEDs button */
static inline void DoButton(void)
{
	/*get button state */
	Button_readState(&PEDs_button) ;

	/*if the button was pressed a short press */
	if(PEDs_button.buttonPressState == ShortPress)
	{
		/* if the button is pressed single press */
		if (currentMode==normal)
		{
			/* change the current mode to pedestrian mode */
			currentMode = ped ;
			TRAFFIC_LIGHT_Drive(&Traffic_light,OFF) ;
		}
	}
}

void init_APP(void)
{	
	/* set traffic light pins */
	TRAFFIC_LIGHT_Init(&Traffic_light) ;
	
	/* set pedestrian sign pins */
	TRAFFIC_LIGHT_Init(&Peds_sign) ;
	
	/* init button */
	Button_Init(&PEDs_button) ;
	
	/* start millis counter / tracker on timer2 */
	Millis_Init() ;
	
}

void startApp(void)
{	
	/* get the system current mode from the button */
	DoButton() ; 
	switch(currentMode)
	{
	case normal : 
		APP_normal_mode() ;
		break;
	case  ped: 
		APP_pedestrian_mode() ;
		break;
	default:
		/*do nothing */
		break;
	}
}

void APP_normal_mode(void)
{
	/* get time in ms  */
	millis_t currentTime = Millis_get() ;
	
	/* last time in ms */
	static millis_t lastTime = 0 ;
	
	/*last time in yellow blinking state */
	static millis_t lastTimeYellow = 0 ;
	
	/*current state counter */
	static uint8_t state_counter = 0;
	
	/*if traffic interval has passed */
	if (currentTime -lastTime >= TRAFFIC_INTERVAL)
	{
		/* increment state counter */
		state_counter++ ;
		
		/*turn off all LEDs */
		TRAFFIC_LIGHT_Drive(&Traffic_light,OFF) ;
		
		/*rest counter*/
		lastTime =currentTime ;
	}
	
	/* limit state counter to only 4 element */
	state_counter = (state_counter>3)? 0: state_counter ;
	
	/* get the next state */
	currentState = normal_seq[state_counter] ;
	
	/* check on current state and drive the traffic light */
	switch(currentState)
	{
		case GREEN:
		TRAFFIC_LIGHT_Drive(&Traffic_light,GREEN) ;
		break;
		case YELLOW:
		if((currentTime-lastTimeYellow)>=YELLOW_LIGHT_BLINKING_INTERVAL)
		{
			/*toggle yellow led every 0.25 sec*/
			TRAFFIC_LIGHT_Drive(&Traffic_light,YELLOW) ;
			
			/*set the old counter to be the current counter to begin counting again*/
			lastTimeYellow = currentTime ;
		}
		break;
		case RED:
		TRAFFIC_LIGHT_Drive(&Traffic_light,RED) ;
		break;
		default:
		TRAFFIC_LIGHT_Drive(&Traffic_light,RED) ;
		break;
	}
}

void APP_pedestrian_mode(void)
{

	/* get time in ms  */
	millis_t currentTime = Millis_get() ;
	
	/* last time in ms */
	static millis_t lastTime = 0 ;
	
	/*last time in yellow blinking state */
	static millis_t lastTimeYellow = 0 ;
	
	/*current state counter */
	static uint8_t state_counter = 0;
	
	/* flag to indicate end of pedestrian mode request */
	static uint8_t turnoff_ped_mode = 0 ;
	/* flag to indicate if the mode is terminated */
	uint8_t done = 0 ;
	
	/* if traffic interval has passed */
	if(currentTime-lastTime>=TRAFFIC_INTERVAL)
	{
		
		/* increment state counter */
		state_counter++ ;
		
		/* rest config and switch mode */
		if (turnoff_ped_mode)
		{
			/* set the current mode to normal */
			currentMode = normal ;
			/*reset */
			turnoff_ped_mode = 0 ;
			lastTime = 0 ;
			lastTimeYellow =  0 ;
			state_counter = 0 ;
			done = 1 ;
		}
		TRAFFIC_LIGHT_Drive(&Peds_sign,OFF) ;
		TRAFFIC_LIGHT_Drive(&Traffic_light,OFF) ;
		
		/* reset overflow counter */
		lastTime = currentTime ;
	}
	if(!done)
	{
		/* if the cars traffic light was red */
		if (currentState == RED)
		{
			/* set pedestrian sign green led */
			TRAFFIC_LIGHT_Drive(&Peds_sign,GREEN) ;
			TRAFFIC_LIGHT_Drive(&Traffic_light,RED) ;

			/* wait 5s and turn off pedestrian mode */
			turnoff_ped_mode = 1 ;
		}
		/* if the traffic light was green or yellow */
		if (currentState == GREEN || currentState ==YELLOW)
		{
			
			/* limit state counter to be only 6 states */
			state_counter = (state_counter>5) ? 0 : state_counter ;
			
			switch(state_counter)
			{
				case 0 :
					TRAFFIC_LIGHT_Drive(&Peds_sign,RED) ;
					if (currentState == YELLOW)
					{
						if((currentTime-lastTimeYellow)>=YELLOW_LIGHT_BLINKING_INTERVAL)
						{
							/*toggle yellow led every 0.25 sec*/
							TRAFFIC_LIGHT_Drive(&Traffic_light,YELLOW) ;
							TRAFFIC_LIGHT_Drive(&Peds_sign,RED) ;

							/*set the old counter to be the current counter to begin counting again*/
							lastTimeYellow = currentTime ;

						}
					}
					else
					{
						TRAFFIC_LIGHT_Drive(&Traffic_light,GREEN) ;
					}
					break;
				case 1 :
					if((currentTime-lastTimeYellow)>=YELLOW_LIGHT_BLINKING_INTERVAL)
					{
						/*toggle yellow led every 0.25 sec*/
						TRAFFIC_LIGHT_Drive(&Traffic_light,YELLOW) ;
						TRAFFIC_LIGHT_Drive(&Peds_sign,YELLOW) ;
						/*set the old counter to be the current counter to begin counting again*/
						lastTimeYellow = currentTime ;
					}
					break;
				case 2 :
					TRAFFIC_LIGHT_Drive(&Traffic_light,RED) ;
					TRAFFIC_LIGHT_Drive(&Peds_sign,GREEN) ;
					break ;
				case 3 :
					if((currentTime-lastTimeYellow)>=YELLOW_LIGHT_BLINKING_INTERVAL)
					{
						/* toggle yellow led every 0.25 sec */
						TRAFFIC_LIGHT_Drive(&Traffic_light,YELLOW) ;
						TRAFFIC_LIGHT_Drive(&Peds_sign,YELLOW) ;
						/* set the old counter to be the current counter to begin counting again */
						lastTimeYellow = currentTime ;
					}
					TRAFFIC_LIGHT_Drive(&Peds_sign,GREEN) ;
					break;
				case 4 :
					TRAFFIC_LIGHT_Drive(&Peds_sign,RED) ;
					TRAFFIC_LIGHT_Drive(&Traffic_light,GREEN) ;
				case 5 :
					turnoff_ped_mode = 1 ;
					break;
			}
		}
	}
}