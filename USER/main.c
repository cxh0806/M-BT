#include "stm32f10x.h"
#include "Light.h"
#include "button.h"
#include "delay.h"
#include "sys_config.h"
#include "lora.h"
#include "LED.h"
#define run_period  1000


uint16_t Dev_Num;

void sys_dev_init(void);


int main(void)
{	     
	
    Run_Status_Type status; 
    uint8_t         mes_post_cnt = 0;;	
	  sys_dev_init();

		while(1)
		{
			LED_Tog();	
			status = APP_Get_Status();
//      status = Run_SendRQS;

			switch(status)
			{
				case Run_Idle:
				{				
					Dev_LED_SetStatus(LED_Idle);
					delay_ms(run_period);
					mes_post_cnt = 0;
				}
					break;
				case Run_SendRQS:
				{
				  Dev_Lora_SendQuest(Lora_Send_Cmd_Call,mes_post_cnt);
					Dev_LED_SetStatus(LED_SendRQS);	
          mes_post_cnt++;					
					delay_ms(run_period);
				}
					break;
				case Run_Rotate_SendRQS :
				{
					Dev_LED_SetStatus(LED_Rotate_SendRQS);
				  delay_ms(run_period);
				}
				break;
				case Run_Rotate_RecvRSP :
				{
					Dev_LED_SetStatus(LED_Rotate_RecvRSP);
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
    Dev_Num =  SYS_Get_Param();
   if(Dev_Num >100 || Dev_Num == 0)
   {
   	  Dev_Num = 0;
   }  
   Dev_LED_Init();
   Dev_Button_Init();
   Dev_Lora_Init();
   Dev_Run_Init();  
   APP_Set_Status(Run_Idle);

}

uint16_t sys_get_period(void)
{


  return run_period;

}





