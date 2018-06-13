#include "lora.h"
#include "button.h"
#include "sys_config.h"
#include "extern_var.h"

#define DATA_NUMBER  10
#define CMD_NUMBER    8
uint8_t Lora_Send_Cmd_Buf[8] = {0xA,0xB,0xC,0xD,0x0F,0x01,0x00,0x00};
uint8_t Lora_Buf[10];



void  Usart_Send_Data(uint8_t *buf,uint16_t cnt2send);

void Dev_Lora_Callback(void);
void Dev_Lora_Init()
{
  GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	DMA_InitTypeDef   DMA_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init( GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOC,&GPIO_InitStruct);

	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init( UART4, &USART_InitStruct);

	USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);

	NVIC_InitStruct.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);

	DMA_InitStruct.DMA_BufferSize   = DATA_NUMBER;
	DMA_InitStruct.DMA_DIR          = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_M2M          = DMA_M2M_Disable;
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&Lora_Buf;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc      = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode           = DMA_Mode_Normal;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(UART4->DR);
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority           = DMA_Priority_Medium;
	DMA_Init(DMA2_Channel3, &DMA_InitStruct);
	DMA_Cmd(DMA2_Channel3, ENABLE);
	USART_Cmd(UART4, ENABLE);
	
	
	
}

void Dev_Lora_SendQuest(Lora_Send_Cmd cmd)
{
   Lora_Send_Cmd_Buf[6] = cmd;   
   Usart_Send_Data(Lora_Send_Cmd_Buf, CMD_NUMBER);

}

void UART4_IRQHandler(void)
{
#if 0
   if(USART_GetFlagStatus(UART4, USART_FLAG_RXNE) !=RESET)
   	{

	
   	}
 #endif
   if(USART_GetFlagStatus(UART4, USART_FLAG_IDLE)!=RESET)
   	{

   	  USART_ReceiveData(UART4);
      DMA_Cmd(DMA2_Channel3,DISABLE);
      Dev_Lora_Callback();
      DMA_SetCurrDataCounter(DMA2_Channel3,DATA_NUMBER );
	    DMA_Cmd(DMA2_Channel3,ENABLE);
   	}



}

void Dev_Lora_Callback()
{	
	Lora_Data *data = (Lora_Data *)Lora_Buf;
	if(data->dev_num != Dev_Num &&Dev_Num != 0)
    {
       return;
    }
	 if(lora_cmd_finish == data->cmd)
	 {
		 APP_Set_Status(Run_Idle);
	 }
	 else if(lora_cmd_recv == data->cmd)
	 {
		 APP_Set_Status(Run_RecvRSP);
	 }
     else
	 {
		 SYS_Set_Param(data->param);
	 }

}


void Usart_Send_Byte(uint8_t data)
{
    while(USART_GetFlagStatus(UART4, USART_FLAG_TC)== RESET);
      
         USART_SendData(UART4, data);
      

}

void  Usart_Send_Data(uint8_t *buf,uint16_t cnt2send)
{

    uint16_t index =0 ;
	for(index = 0; index < cnt2send;index++)
    {
	     Usart_Send_Byte(*(buf+index));
    }
}

