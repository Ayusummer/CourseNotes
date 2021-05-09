/*
 * @Author: your name
 * @Date: 2021-04-29 19:00:56
 * @LastEditTime: 2021-04-29 19:15:08
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\实验9-第7次实验-PWM输出实验\main-v1.0-初次尝试.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "led.h"
#include "exti.h"
#include "key.h"


//ALIENTEK 探索者STM32F407开发板 实验9
//PWM输出实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

#define pi 3.14

int main(void){ 
	u16 xval=360;
	int i;
	double rad = pi / 180;
	double sinval;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);			//初始化延时函数
	uart_init(115200);			//初始化串口波特率为115200
	LED_Init();
 	TIM14_PWM_Init(500-1,84-1);	//84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.
	EXTIX_Init();				//初始化外部中断输入 
	
    while(1){					//实现比较值从0-300递增，到300后从300-0递减，循环
	   delay_ms(20);
	   
	   if(isKEY0){				//若为启动
		   xval-=4;
		   if(xval<=0)xval=360;
		   sinval = (sin(rad * xval)+1)*100;
		   TIM_SetCompare1(TIM14,sinval);	//修改比较值，修改占空比
		   
		   /*串口调试助手显示输出波形*/
		   if(xval%3==0){
			   for(i=0;i<sinval/3;i++)
					printf(" ");
			   printf("*\n");
		   }
	   }//if(isKEY0)
   }// while(1)
}
