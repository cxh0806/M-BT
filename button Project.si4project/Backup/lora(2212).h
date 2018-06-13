#ifndef __LORA_H
#define __LORA_H
#include "stm32f10x.h"


typedef enum Lora_Cmd_
{
	lora_cmd_none = 0,
	lora_cmd_recv = 1,
	lora_cmd_finish = 2,
	
}Lora_Cmd;

typedef enum Lora_Send_Cmd_
{
    Lora_Send_Cmd_None   = 0 ,
	Lora_Send_Cmd_Call   = 0x01 ,
	Lora_Send_Cmd_Rotate = 0x02,
}Lora_Send_Cmd;

typedef struct _Lora_Data
{
  uint32_t head;
  uint16_t cmd;  
  uint8_t  dev_num;
  uint8_t  param;
}Lora_Data;


void Dev_Lora_Init(void);
void Dev_Lora_SendQuest(Lora_Send_Cmd cmd);


#endif




