/*
 * @Author: your name
 * @Date: 2021-04-22 18:54:57
 * @LastEditTime: 2021-04-22 19:28:34
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\实验8-第6次实验-定时器中断实验\exti.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "exti.h"


int isKEY2=0;		// 反映KEY2按键状态
int isKEY1=0;		// 反映KEY1按键状态
int isKEY0=0;		// 反映KEY0按键状态

int oldLED0=1;		// 反映LED0旧值
int oldLED1=1;		// 反映LED1旧值

//外部中断4服务程序(KEY0 右键)
void EXTI4_IRQHandler(void){
	delay_ms(100);	//消抖
	if(KEY0 == 0 && (!isKEY2) ){
		isKEY0=!isKEY0;
	}
	 EXTI_ClearITPendingBit(EXTI_Line4);//清除LINE4上的中断标志位  
}




//外部中断2服务程序
void EXTI2_IRQHandler(void){
	delay_ms(100);	//消抖
	if(KEY2 == 0){
		isKEY2=!isKEY2;
		if(isKEY2){
			oldLED0=LED0;
			oldLED1=LED1;
			
			/*若想谁闪加锁后让谁常亮*/
//			if(isKEY0) LED0=0;
//			else LED0=1;
//			if(isKEY1) LED1=0;
//			else LED1=1;
			
			LED0=0;
			LED1=0;
			
//			TIM_ITConfig(TIM3,TIM_IT_Update, DISABLE); 
			TIM_Cmd(TIM3,DISABLE);
		}
		else{
//			TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE); 
			TIM_Cmd(TIM3,ENABLE);
			LED0=oldLED0;
			LED1=oldLED1;
		}
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
}

//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY1==0&&(!isKEY2)){
		isKEY1=!isKEY1;
	}
	 EXTI_ClearITPendingBit(EXTI_Line3);//清除LINE3上的中断标志位  
}



	   
//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX_Init(void)
{
    NVIC_InitTypeDef   NVIC_InitStructure;
    EXTI_InitTypeDef   EXTI_InitStructure;
    
    KEY_Init();     // 按键对应的IO口初始化
 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  // 使能SYSCFG时钟
    
 
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);   // PE2 连接到中断线2
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);   // PE3 连接到中断线3
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);   // PE4 连接到中断线4
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);   // PA0 连接到中断线0
    
    /* 配置EXTI_Line0 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;              // LINE0
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     // 中断事件
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  // 上升沿触发 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;               // 使能LINE0
    EXTI_Init(&EXTI_InitStructure);                         // 配置
        
    /* 配置EXTI_Line2,3,4 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;         // 中断事件
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     // 下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                   // 中断线使能
    EXTI_Init(&EXTI_InitStructure);                             // 配置
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;                // 外部中断0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;    // 抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;           // 子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 // 使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                                 // 配置
        
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;                // 外部中断2
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;    // 抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;           // 子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 // 使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                                 // 配置
        
        
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;                // 外部中断3
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;    // 抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;           // 子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 // 使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                                 // 配置
        
        
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;                // 外部中断4
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;    // 抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;           // 子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 // 使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                                 // 配置
       
}