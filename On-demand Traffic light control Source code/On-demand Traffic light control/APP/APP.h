/**
 * @file APP.C
 * @author Youssef Abdelmajeed (youssefabdelmajeed77@gmail.com)
 * @brief  On-demand Traffic light control Application Interface file 
 * @version 0.1
 * @date 2022-11-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef APP_H_
#define APP_H_

/*  On-demand Traffic light System Modes */
typedef enum EN_modes {normal , ped} EN_modes_t;

/**
 * @brief initialize all modules used in the application 
 * 
 */
void init_APP(void) ;

/**
 * @brief start the application 
 * 
 */
void startApp(void) ;

/**
 * @brief Traffic light System normal mode  
 * 
 */
void APP_normal_mode(void) ; 

/**
 * @brief  Traffic light System pedestrian mode 
 * 
 */
void APP_pedestrian_mode(void) ; 

#endif /* APP_H_ */