#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "beep.h"
//////////////////////////////////////////////////////////////////////////////////	 
//?????????,??????,??????????
//ALIENTEK STM32F407???
//???? ????	   
//????@ALIENTEK
//????:www.openedv.com
//????:2014/5/4
//??:V1.0
//????,?????
//Copyright(C) ????????????? 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

int flag=0;//????


//????0????
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//??
	if(WK_UP==1)	 
	{
		BEEP=!BEEP; //????? 
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line0); //??LINE0??????? 
}	
//????2????
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	//??
	if(KEY2==0)	  
	{				 
   		LED0=!LED0; 
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line2);//??LINE2??????? 
}


//????3????
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//??
	if(KEY1==0)	 
	{
		IWDG_Feed();
		BEEP=0;     // ???????
		LED0=1;     // ??LED0??
		flag=1;
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line3);  //??LINE3???????  
}


//????4????
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//??
	if(KEY0==0)	 
	{				 
		LED0=!LED0;	
		LED1=!LED1;	
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);//??LINE4???????  
}
	   
//?????????
//???PE2~4,PA0?????.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //?????IO????
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//??SYSCFG??
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 ??????2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 ??????3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 ??????4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 ??????0
	
  /* ??EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//????
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //????? 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//??LINE0
  EXTI_Init(&EXTI_InitStructure);//??
	
	/* ??EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//????
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //?????
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//?????
  EXTI_Init(&EXTI_InitStructure);//??
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//????0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//?????0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//????2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//????????
  NVIC_Init(&NVIC_InitStructure);//??
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//????2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//?????3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//????2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//????????
  NVIC_Init(&NVIC_InitStructure);//??
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//????3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//?????2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//????2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//????????
  NVIC_Init(&NVIC_InitStructure);//??
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//????4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//?????1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//????2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//????????
  NVIC_Init(&NVIC_InitStructure);//??
	   
}












