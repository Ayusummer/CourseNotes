#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////     
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//外部中断 驱动代码       
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved                                      
////////////////////////////////////////////////////////////////////////////////// 

int press_key1=0;          // key1按键状态, 0->按下, 1->未按下
int press_key0=0;          // key0按键状态, 0->按下, 1->未按下
int press_key2=0;          // key2按键状态, 0->按下, 1->未按下

int L0_old=1;                // LED0原来值->用于交替闪烁保持
int L1_old=1;                // LED1原来值->用于交替闪烁保持

// 外部中断4服务程序(KEY0, 右键)
void EXTI4_IRQHandler(void){
    delay_ms(100);                      // 消抖
    if(KEY0==0 && (!press_key2)){       // 按KEY0且未按下KEY2
        press_key0 = !press_key0;       // KET0按键状态改变
    }
    EXTI_ClearITPendingBit(EXTI_Line4); // 清除LINE4上的中断标志位  
}


// 外部中断3服务程序(KEY1, 下键)
void EXTI3_IRQHandler(void){
    delay_ms(100);                    // 消抖
    if(KEY1==0&&(!press_key2)){       // 按KEY1且未按下KEY2
        press_key1=!press_key1;       // KEY1按键状态改变
    }
     EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}


// 外部中断2服务程序(KEY2, 左键)
void EXTI2_IRQHandler(void){
    delay_ms(100);                    // 消抖

    // 若KEY2按下
    if(KEY2 == 0){
        press_key2 =! press_key2;     // KEY2按下的标志位反相

        if(press_key2){     // 如果KEY2按下则给当前LED状态上锁
          // 将LED状态送给旧值
          L0_old=LED0;    
          L1_old=LED1;
          // 如果LED在闪烁则将其置为常亮, 若熄灭则不变
          if(press_key0) LED0=0;     // press_key0为1时，LED0正在闪烁，设置成常亮
          if(press_key1) LED1=0;
          
          TIM_Cmd(TIM3,DISABLE);    // 失能TIM3
        }
        // 如果KEY2松开(解锁)
        else{
          // LED状态返回旧值
          LED0=L0_old;             
          LED1=L1_old;
          TIM_Cmd(TIM3,ENABLE);     // 使能TIM3
        }    
    }         
    EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
}


//外部中断0服务程序
void EXTI0_IRQHandler(void){
    delay_ms(10);    //消抖
    if(WK_UP==1){
      // do nothing
    }         
    EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
}    

       
//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX_Init(void){
    NVIC_InitTypeDef   NVIC_InitStructure;
    EXTI_InitTypeDef   EXTI_InitStructure;
    
    KEY_Init(); //按键对应的IO口初始化
 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  // 使能SYSCFG时钟
    
 
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2); // PE2 连接到中断线2
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3); // PE3 连接到中断线3
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4); // PE4 连接到中断线4
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0); // PA0 连接到中断线0
    
    /* 配置EXTI_Line0 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;              // LINE0
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     // 中断事件
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  // 上升沿触发 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;               // 使能LINE0
    EXTI_Init(&EXTI_InitStructure);                         // 配置
      
    /* 配置EXTI_Line2,3,4 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;       // 中断事件
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                 // 中断线使能
    EXTI_Init(&EXTI_InitStructure);                           // 配置
  
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;              // 外部中断0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  // 抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;         // 子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               // 使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                               //配置
      
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;              // 外部中断2
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;  // 抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;         // 子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               // 使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                               // 配置
      
      
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;              // 外部中断3
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  // 抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;         // 子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               // 使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                               // 配置
      
      
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;              // 外部中断4
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;  // 抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;         // 子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               // 使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                               // 配置
}












