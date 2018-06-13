#ifndef __LED_H
#define __LED_H


#include "sys.h"

#define LED_Tog()  	GPIOC->ODR^=(0x01<<12)

void Dev_Run_Init(void);

#endif


