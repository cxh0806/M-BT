#include "stm32f10x.h"
#include "Light.h"
#include "button.h"
#include "delay.h"

int main(void)
{	

		Run_Status_Type status;
	 
		while(1)
		{
			status = APP_Get_Status();

			switch(status)
			{
				case Run_Idle:
				{
					
					delay_ms(100);
				}
					break;
				case Run_SendRQS:
				{
					
					
				}
					break;
				case Run_RecvRSP:
				{
					
					
				}
					break;
				default :
				{
					
					delay_ms(100);
				}
					 break;
					
			}		
			
		}
}

