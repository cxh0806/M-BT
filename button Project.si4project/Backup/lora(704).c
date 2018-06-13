#include "lora.h"
#include "button.h"
#include "sys_config.h"

uint8_t Lora_Buf[10];
void Dev_Lora_Init()
{
  	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	DMA_InitTypeDef   DMA_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
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
	USART_Init(  UART4, &USART_InitStruct);

	USART_ITConfig(UART4, USART_IT_RXNE|USART_IT_IDLE, ENABLE);

	NVIC_InitStruct.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);

	DMA_InitStruct.DMA_BufferSize   = 10;
	DMA_InitStruct.DMA_DIR          = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_M2M          = DMA_M2M_Disable;
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&Lora_Buf;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc      = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode           = DMA_Mode_Normal;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(UART4->DR)
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority           = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1, &DMA_InitStruct);
	
	USART_Cmd(UART4, ENABLE);
	
	
}


void UART4_IRQHandler(void)
{

   if(USART_GetFlagStatus(UART4, USART_FLAG_RXNE) !=RESET)
   	{

	
   	}
   else(USART_GetFlagStatus(UART4, USART_FLAG_IDLE)!RESET)
   	{

   
   
   	}




}

void Dev_Lora_Callback()
{
	
	
   Lora_Cmd cmd;
	 uint16_t ID;
	 if(lora_cmd_finish == cmd)
	 {
		 APP_Set_Status(Run_Idle);
	 }
	 else if(lora_cmd_recv == cmd)
	 {
		 APP_Set_Status(Run_RecvRSP);
	 }
   else
	 {
		 SYS_Set_Param(ID);
	 }

}






