#ifndef __Light_H
#define __Light_H
#include "stm32f10x.h"

typedef enum LED_Status_Type_
{
	LED_Error_Status,
	LED_Idle,
	LED_SendRQS,
	LED_RecvRSP,
	LED_Rotate_SendRQS,
	LED_Rotate_RecvRSP,
}LED_Status_Type;



#define  LED_GREEN PCout(1)
#define  LED_RED   PCout(2)
#define LED_RED_ON  LED_RED = 1
#define LED_RED_OFF LED_RED = 0
#define LED_GREEN_ON LED_GREEN = 1
#define LED_GREEN_OFF  LED_GREEN = 0

void Dev_LED_Init(void);


void Dev_LED_SetStatus(LED_Status_Type status);



#endif

