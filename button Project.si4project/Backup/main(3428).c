#include "stm32f10x.h"
#include "Light.h"
#include "button.h"
#include "delay.h"
#include "sys_config.h"
#include "lora.h"
#include "LED.h"
#define run_period  300


uint16_t Dev_Num;

void sys_dev_init(void);


int main(void)
{	     
	
   Run_Status_Type status; 	   
	 sys_dev_init();	
//	  LED2 =1;
//	  LED3 = 0;
	  GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		while(1)
		{
			status = APP_Get_Status();
//      status = Run_SendRQS;
			switch(status)
			{
				case Run_Idle:
				{				
					Dev_LED_SetStatus(LED_Idle);
					delay_ms(run_period);
				}
					break;
				case Run_SendRQS:
				{
				  Dev_Lora_SendQuest();
					Dev_LED_SetStatus(LED_SendRQS);
					delay_ms(run_period);
				}
					break;
				case Run_RecvRSP:
				{
					
					Dev_LED_SetStatus(LED_RecvRSP);
					delay_ms(run_period);
				}
					break;
				default :
				{
					
					delay_ms(run_period);
				}
					 break;
					
			}		
			
		}
}




void sys_dev_init()
{
   delay_init();
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   Dev_LED_Init();
   Dev_Button_Init();
   Dev_Lora_Init();
   Dev_Run_Init();
   Dev_Num =  SYS_Get_Param();
	 APP_Set_Status(Run_Idle);
   if(Dev_Num >100 || Dev_Num == 0)
   {
   	  Dev_Num = 0;
   }
}

