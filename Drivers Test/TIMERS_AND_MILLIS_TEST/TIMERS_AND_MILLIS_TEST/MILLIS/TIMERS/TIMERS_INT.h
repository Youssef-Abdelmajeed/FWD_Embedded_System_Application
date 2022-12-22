/**
 * @file TIMERS_INT.h
 * @author Youssef Abdelmajeed (youssefabdelmajeed77@gmail.com)
 * @brief  TIMERS [Timer0 ,Timer2] Interface file 
 * @version 0.1
 * @date 2022-11-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TIMERS_INT_H_
#define TIMERS_INT_H_

/*Timer 0 ,2 modes  */
typedef enum EN_prescalerModes 
{
   CounterMode, Noprescaler,prescaler8, prescaler64, prescaler256, prescaler1024, ExFalling, ExRising 
} EN_prescalerModes_t ; 
/*  timers wave modes */
typedef enum EN_waveModes 
{
    Normal, PWM_PhaseCorrect, CTC, Fast_PWM 
}EN_waveModes_t ; 

/* 8 bit timers in AVR ATMEGA32 */
typedef  enum EN_Timers
{
    TIMER0, TIMER2 
}EN_Timers_t ; 

/**
 * @brief set timer prescaller mode 
 * 
 * @param timer TIMER0, TIMER2 
 * @param Pmode CounterMode, Noprescaler,prescaler8, prescaler64, prescaler256, prescaler1024, ExFalling, ExRising 
 */
void Timer_SetPrescaller(EN_Timers_t timer , EN_prescalerModes_t Pmode) ;

/**
 * @brief set timer wave mode 
 * 
 * @param timer TIMER0, TIMER2
 * @param Wmode Normal, PWM_PhaseCorrect, CTC, Fast_PWM
 */
void Timer_SetWaveMode(EN_Timers_t timer , EN_waveModes_t Wmode) ;

/**
 * @brief 
 * 
 * @param timer set timer wave mode and prescaller 
 * @param Pmode CounterMode, Noprescaler,prescaler8, prescaler64, prescaler256, prescaler1024, ExFalling, ExRising 
 * @param Wmode Normal, PWM_PhaseCorrect, CTC, Fast_PWM
 */
void Timer_Init(EN_Timers_t timer , EN_prescalerModes_t Pmode ,  EN_waveModes_t Wmode) ; 

/**
 * @brief set timer in normal mode (overflow mode) and set callback to it 
 * 
 * @param timer TIMER0, TIMER2
 * @param isr callback function (called when timer overflow happen)
 */
void Timer_SetOVF_Callback(EN_Timers_t timer , void(*isr)(void)) ;

/**
 * @brief set timer in CTC mode (Compare match mode) and set callback to it 
 * 
 * @param timer TIMER0, TIMER2
 * @param isr callback function (called when timer compare match happen)
 */
void Timer_SetCTC_Callback(EN_Timers_t timer , void(*isr)(void)) ; 

/**
 * @brief preload timer register in normal mode 
 * 
 * @param timer TIMER0, TIMER2
 * @param value  8 bit value 
 */
void Timer_SetOVFRegister(EN_Timers_t timer,uint8_t value) ;

/**
 * @brief set compare match value in CTC mode 
 * 
 * @param timer TIMER0, TIMER2
 * @param value  8 bit value 
 */
void Timer_SetCTCRegister(EN_Timers_t timer,uint8_t value) ;

/**
 * @brief read timer overflow flag 
 * 
 * @param timer TIMER0, TIMER2
 *
 * return uint8_t reading of timer flag  
 */
uint8_t Timer_GetOVFflag(EN_Timers_t timer);

/**
 * @brief read timer Compare match flag 
 * 
 * @param timer TIMER0, TIMER2
 *
 * return uint8_t reading of timer flag  
 */
uint8_t Timer_GetCTCflag(EN_Timers_t timer) ;

/**
 * @brief clear /reset timer overflow flag 
 * 
 * @param timer TIMER0, TIMER2
 *
 */
void Timer_clearOVFflag(EN_Timers_t timer) ;
/**
 * @brief clear /reset timer  Compare match flag 
 * 
 * @param timer TIMER0, TIMER2
 *
 */
void Timer_clearCTCflag(EN_Timers_t timer) ;


#endif /* TIMERS_INT_H_ */