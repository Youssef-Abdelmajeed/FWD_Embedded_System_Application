/**
 * @file main.c
 * @author Youssef Abdelmajeed (youssefabdelmajeed77@gmail.com)
 * @version 0.1
 * @date 2022-11-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "APP/APP.h"

int main(void)
{
	/*init all modules used in app*/
	init_APP() ;
	
    while (1) 
    {
		/* run the app */
		startApp();
	}

}


