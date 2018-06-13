#include "Light.h"
#include "delay.h"
#include "sys.h"


void Dev_LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	
}


void Dev_LED_SetStatus(LED_Status_Type status)
{
	switch(status)
	{
		case LED_Idle:
		{
			LED_GREEN_ON;
			LED_RED_OFF;
			
		}
			break;
		case LED_RecvRSP:
		{
			LED_GREEN_ON;
			LED_RED_ON;		
			
		}
			break;
		case LED_SendRQS:
		{
			LED_GREEN_OFF;
			LED_RED_ON;		
			
		}
			break;		
		default:
			 break;
	}
	
}




