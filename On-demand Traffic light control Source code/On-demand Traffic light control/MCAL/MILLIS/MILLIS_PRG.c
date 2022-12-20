
/**
 * @file MILLIS_PRG.h
 * @author Youssef Abdelmajeed (youssefabdelmajeed77@gmail.com)
 * @brief  millisecond timer tracking Implementation file 
 * @version 0.1
 * @date 2022-12-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../../LIB/STD_TYPES.h" 
#include "TIMERS/TIMERS_INT.h"
#include "../../MCAL/GIE/GIE_INT.h"
#include "MILLIS_INT.h"

/* number of milliseconds passed */
millis_t millis  = 0 ;

/* each timer overflow(timer ISR) */ 
static void Millis_INC(void)
{
	/* set timer preload again */
	Timer_SetOVFRegister(Selected_Timer,131);
	/*increment the number of milliseconds passed */
	millis++ ; 	
}

void Millis_Init(void) 
{
	/* global interrupts enable*/
	GIE_Enable() ; 
	/* set timer overflow callback (what happen when timer overflows */
	Timer_SetOVF_Callback(Selected_Timer,&Millis_INC) ; 
	
	/* set timer overflow register to  131 to achieve 1 ms in the next overflow*/
	Timer_SetOVFRegister(Selected_Timer,131) ;
	
	/* set timer prescaller and wave mode to be normal */
	Timer_Init(Selected_Timer,prescaler8,Normal) ;
}

millis_t Millis_get(void) 
{
	/*disable all interrupts */ 
	GIE_Disable() ; 
	millis_t m = millis ; 
	/* global interrupts enable */
	GIE_Enable() ;
	return m ;
}