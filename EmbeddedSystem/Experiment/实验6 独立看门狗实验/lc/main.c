/*
 * @Author: your name
 * @Date: 2021-04-16 09:22:26
 * @LastEditTime: 2021-04-16 09:25:04
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\Experiment\??6 ?立看?狗??\lc\main.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "iwdg.h"
#include "exti.h"




extern int flag;
void led_breath(u32 t,u32 bright);
void led_breath(u32 t,u32 bright){
	delay_ms(bright);
	LED1=1;
	delay_ms(t-bright);
	LED1=0;
}
int main(void)
{ 
	u16 prer=4;					
	u16 rlr=500*5;				
	u16 count=0;		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);  //3?那??‘?車那㊣o‘那y
	LED_Init();				
	KEY_Init();		  	
 BEEP_Init();				
	EXTIX_Init();				
	//delay_ms(200);	  
	IWDG_Init(prer,rlr); 
	LED1=0;					
	while(1){
		
						int i;
						int totaltime=1000;
						int shorttime=20;
						int circle=totaltime/shorttime;
						for(i=circle;i>=5;i-=1){
							led_breath(shorttime,shorttime*i/circle);
						}
						for(;i<=circle;i+=1){
							led_breath(shorttime,shorttime*i/circle);
						}
		count++;
		if(!flag){				
			if(count>=2)
				{	
				int alarm=20;
				while(alarm--)
				{
					if(flag==1)
					{
						BEEP=0;
		        LED0=1;
						count=0;			
			      flag=0;	
						break;
					}

					LED0=!LED0;
					BEEP=!BEEP;
					delay_ms(100);
					
				}
				
	
			}
		}
		else{					
			count=0;			
			flag=0;				
		}
		delay_ms(10);			
	};

}
