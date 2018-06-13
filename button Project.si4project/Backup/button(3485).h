#ifndef __BUTTON_H
#define __BUTTON_H
#include "stm32f10x.h"
typedef enum Run_Status_Type_
{
	Run_Error_Status,
	Run_Idle,
	Run_SendRQS,
	Run_RecvRSP,
}Run_Status_Type;


Run_Status_Type APP_Get_Status(void);


void   APP_Set_Status(Run_Status_Type status);


#endif



