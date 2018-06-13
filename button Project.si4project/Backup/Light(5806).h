#ifndef __Light_H
#define __Light_H
#include "stm32f10x.h"

typedef enum LED_Status_Type_
{
	LED_Error_Status,
	LED_Idle,
	LED_SendRQS,
	LED_RecvRSP,
}LED_Status_Type;

typedef struct Lora_Data_
{
  uint8_t dev_num;
  uint8_t cmd;
  uint16_t param;
}Lora_Data;

#define  LED_GREEN PCout(1)
#define  LED_RED   PCout(2)
#define LED_RED_ON  LED_RED = 1
#define LED_RED_OFF LED_RED = 0
#define LED_GREEN_ON LED_GREEN = 1
#define LED_GREEN_OFF  LED_GREEN = 0


#endif

