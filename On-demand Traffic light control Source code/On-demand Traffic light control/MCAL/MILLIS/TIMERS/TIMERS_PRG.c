/**
 * @file TIMERS_PRG.c
 * @author Youssef Abdelmajeed (youssefabdelmajeed77@gmail.com)
 * @brief  TIMERS [Timer0 ,Timer2] Implementation file 
 * @version 0.1
 * @date 2022-11-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../../../LIB/BIT_MATH.h"
#include "../../../LIB/STD_TYPES.h"
#include "TIMERS_INT.h"
#include "TIMERS_REG.h"

/*place holder for timers overflow callback */
void (*TIMERS_NORMAL_ISR[2])(void) = {((void *)0),((void *)0)} ;
/*place holder for timers compare match callback */
void (*TIMERS_CTC_ISR[2])(void) = {((void *)0),((void *)0)} ;

void Timer_SetPrescaller(EN_Timers_t timer , EN_prescalerModes_t Pmode)
{
    /* set the clock mode to the corresponding Timer  */
    switch (timer)
    {
    case TIMER0: 
        /* clear Timer0 clock selection bits */
        TCCR0 &= 0XF8 ;
        /* set Timer0 new clock mode  */
        TCCR0 |= Pmode ;
        break;
    case TIMER2:
        /* clear Timer2 clock selection bits */
        TCCR2 &= 0xF8 ;
         /* set Timer2 new clock mode  */
        TCCR2 |= Pmode ;
        break;
    default:
        /*do nothing*/
        break;
    }
}
void Timer_SetWaveMode(EN_Timers_t timer , EN_waveModes_t Wmode)
{
    /* set the wave mode to the corresponding Timer  */
    switch (timer)
    {
    case TIMER0:
        /* clear Timer0 Wave mode selection bits */
        TCCR0 &= 0XB7 ;
        /* set Timer0 new wave mode  */
        TCCR0 |= (getBit(Wmode,0)<<TCCR0_WGM00) | (getBit(Wmode,1)<<TCCR0_WGM01)  ; 
        break;
    case TIMER2 : 
         /* clear Timer2 Wave mode selection bits */
        TCCR2 &= 0XB7 ;
        /* set Timer2 new wave mode  */
        TCCR2 |= (getBit(Wmode,0)<<TCCR2_WGM00) | (getBit(Wmode,1)<<TCCR2_WGM01)  ; 
        break;

    default:
        /* do nothing */
        break;
    }
}

inline void Timer_Init(EN_Timers_t timer , EN_prescalerModes_t Pmode ,  EN_waveModes_t Wmode)
{
    /* set timer clock mode */
    Timer_SetPrescaller(timer,Pmode) ; 
    /* set timer wave mode */
    Timer_SetWaveMode(timer,Wmode) ;
}
inline void Timer_SetOVF_Callback(EN_Timers_t timer , void(*callback)(void)) 
{
    /*if callback isn't NULL */
    if(callback!=((void *)0))
    {
        /* set callback to the corresponding Timer  */
        switch (timer)
        {
        case TIMER0:
            /* set overflow Interrupt Enable 0 */
            setBit(TIMSK,TIMSK_TOIE0) ; 
            /* clear CTC Interrupt Enable 0 */
            clearBit(TIMSK,TIMSK_OCIE0) ;
            /* set callback */
            TIMERS_NORMAL_ISR[0] = callback ; 
            break;
        case TIMER2:
            /* set overflow Interrupt Enable 2 */
            setBit(TIMSK,TIMSK_TOIE2) ; 
            /* clear CTC Interrupt Enable 2*/
            clearBit(TIMSK,TIMSK_OCIE2) ;
            /* set callback */
            TIMERS_NORMAL_ISR[1] = callback ; 
            break;
        default:
            /*do nothing*/
            break;
        }
    }
    else
    {
        /* do nothing */
    }
}
inline void Timer_SetCTC_Callback(EN_Timers_t timer , void(*callback)(void)) 
{
    /*if callback isn't NULL */
    if(callback!=((void *)0))
    {
        /* set callback to the corresponding Timer  */
        switch (timer)
        {
        case TIMER0:
            /* set CTC Interrupt Enable 0 */
            setBit(TIMSK,TIMSK_OCIE0) ; 
            /* clear overflow Interrupt Enable 0 */
            clearBit(TIMSK,TIMSK_TOIE0) ;
            /* set callback */
            TIMERS_CTC_ISR[0] = callback ; 
            break;
        case TIMER2:
            /* set CTC Interrupt Enable 2 */
            setBit(TIMSK,TIMSK_OCIE2) ;
            /* clear overflow Interrupt Enable 2 */
            clearBit(TIMSK,TIMSK_TOIE2) ;
            /* set callback */
            TIMERS_CTC_ISR[1] = callback ;
			break;
        default:
            /*do nothing*/
            break;
        }
    }
    else
    {
        /* do nothing */
    }
}
void Timer_SetOVFRegister(EN_Timers_t timer,uint8_t value)
{
    /* set value to the corresponding Timer overflow register  */
     switch (timer)
        {
        case TIMER0:
            TCNT0= value ; 
            break;
        case TIMER2:
            TCNT2= value ; 
			break;
        default:
            /*do nothing*/
            break;
        }
}
void Timer_SetCTCRegister(EN_Timers_t timer,uint8_t value)
{
     /* set value to the corresponding Timer CTC register  */
     switch (timer)
        {
        case TIMER0:
            OCR0= value ; 
            break;

        case TIMER2:
            OCR2= value ; 
			break;
		default:
            /*do nothing*/
            break;
        }
}

inline uint8_t Timer_GetOVFflag(EN_Timers_t timer)
{
	uint8_t flag = 0 ;
	switch (timer)
	{
	case TIMER0:
		flag = getBit(TIFR,TIFR_TOV0) ; 
		break;

	case TIMER2:
		flag = getBit(TIFR,TIFR_TOV2) ;  
		break;
	default:
		/*do nothing*/
		break;
	}
	return flag ;
}

inline uint8_t Timer_GetCTCflag(EN_Timers_t timer)
{
	uint8_t flag = 0 ;
	switch (timer)
	{
	case TIMER0:
		flag = getBit(TIFR,TIFR_OCF0) ;
		break;
	case TIMER2:
		flag = getBit(TIFR,TIFR_OCF2) ;
		break;
	default:
		/*do nothing*/
		break;
	}
	return flag ;
}

inline void Timer_clearOVFflag(EN_Timers_t timer)
{
	
	switch (timer)
	{
	case TIMER0:
		setBit(TIFR,TIFR_TOV0) ;
		break;
	case TIMER2:
		setBit(TIFR,TIFR_TOV2) ;
		break;
	default:
		/*do nothing*/
		break;
	}
}
inline void Timer_clearCTCflag(EN_Timers_t timer)
{
	switch (timer)
	{
	case TIMER0:
		setBit(TIFR,TIFR_OCF0) ;
		break;
	case TIMER2:
		 setBit(TIFR,TIFR_OCF2) ;
		 break;
	default:
		/*do nothing*/
		break;
	}
}

/* Timer0 Overflow ISR */
void __vector_11 (void) __attribute__ ((signal,used)) ; 
void __vector_11 (void) 
{
    if(TIMERS_NORMAL_ISR[0] != ((void *)0))
    {
        TIMERS_NORMAL_ISR[0]() ;
    }
    else
    {
        /* do nothing */
    }
}

/* Timer0 CompareMatch ISR */
void __vector_10 (void) __attribute__ ((signal,used)) ; 
void __vector_10 (void) 
{
    if(TIMERS_CTC_ISR[0] != ((void *)0))
    {
        TIMERS_CTC_ISR[0]() ;
    }
    else
    {
        /* do nothing */
    }
}

/* Timer2 Overflow ISR */
void __vector_5 (void) __attribute__ ((signal,used)) ; 
void __vector_5 (void) 
{
    if(TIMERS_NORMAL_ISR[1] != ((void *)0))
    {
        TIMERS_NORMAL_ISR[1]() ;
    }
    else
    {
        /* do nothing */
    }
}

/* Timer2 CompareMatch ISR */
void __vector_4 (void) __attribute__ ((signal,used)) ; 
void __vector_4 (void) 
{
    if(TIMERS_CTC_ISR[1] != ((void *)0))
    {
        TIMERS_CTC_ISR[1]() ;
    }
    else
    {
        /* do nothing */
    }
}


