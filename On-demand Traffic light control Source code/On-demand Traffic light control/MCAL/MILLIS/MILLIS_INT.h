
/**
 * @file MILLIS_INT.h
 * @author Youssef Abdelmajeed (youssefabdelmajeed77@gmail.com)
 * @brief  millisecond time tracking Interface file 
 * @version 0.1
 * @date 2022-12-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MILLIS_H_ 
#define MILLIS_H_ 

/* check the CPU frequency */
#ifdef F_CPU
	#if F_CPU==1000000UL
		/*do nothing*/
	#else
		# error "F_CPU for millis is has to be 1 MHZ to work"
	#endif
#else
	#define F_CPU 1000000UL
#endif

/*selected timer for millisecond time tracking*/
#define Selected_Timer (EN_Timers_t) TIMER0

/* define millis to store number of milliseconds */
typedef volatile uint32_t millis_t ;

/**
 * @brief init Milliseconds timer 
 *
 */
void Millis_Init(void) ;

/**
 * @brief get number of milliseconds passed since the tracker started  
 * 
 * @param timer TIMER0, TIMER2
 *
 * return uint8_t reading of timer flag  
 */
millis_t Millis_get(void) ;

#endif /* MILLIS_H_ */



