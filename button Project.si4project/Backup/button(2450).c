#include "button.h"
#include "sys.h"

Run_Status_Type run_status;

void Dev_Button_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
}

void Dev_Button_Callback()
{
	
	
}

Run_Status_Type APP_Get_Status(void)
{
	
	
	return run_status;
}

void   APP_Set_Status(Run_Status_Type status)
{
	
	  run_status = status;
	
	
}






