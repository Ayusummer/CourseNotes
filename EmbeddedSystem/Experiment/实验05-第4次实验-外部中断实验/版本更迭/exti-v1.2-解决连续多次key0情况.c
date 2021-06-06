/*
 * @Author: your name
 * @Date: 2021-04-15 15:07:22
 * @LastEditTime: 2021-04-15 19:41:14
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\Experiment\实验5-第4次实验-外部中断实验\exti-v1.0.c
 */
#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "beep.h"

int isBling=0;    // 用于判断LED0是否到了需要改变状态的时候
int flag = 0;   // 标志位(判断顺序是否正确,只有0-1)


// 外部中断0服务程序
void EXTI0_IRQHandler(void){
    delay_ms(10);    //消抖
    if(WK_UP==1){
        if(isBling==7) flag = 1;
        else {
            isBling=0;  // 滑窗清零
            flag = 0;   // 标志位置0
        }
        if(flag){
           LED0=!LED0;
           flag = 0; 
        } 
    }        
    EXTI_ClearITPendingBit(EXTI_Line0);     // 清除LINE0上的中断标志位 
}    

// 外部中断2服务程序
void EXTI2_IRQHandler(void){
    delay_ms(10);    // 消抖
    if(KEY2==0){                 
        if(isBling == 4 || isBling == 5 || isBling == 6 ) isBling++;
        else {
            isBling=0;  // 滑窗清零
            flag = 0;   // 标志位置0
        }
    }     
    EXTI_ClearITPendingBit(EXTI_Line2); // 清除LINE2上的中断标志位 
}

// 外部中断3服务程序
void EXTI3_IRQHandler(void){
    delay_ms(10);    // 消抖
    if(KEY1==0){
        if(isBling == 2 || isBling == 3) isBling++;
        else {
            isBling=0;  // 滑窗清零
            flag = 0;   // 标志位置0
        }
    }         
    EXTI_ClearITPendingBit(EXTI_Line3);  // 清除LINE3上的中断标志位  
}

// 外部中断4服务程序
void EXTI4_IRQHandler(void){
    delay_ms(10);    //消抖
    if(KEY0==0){                 
        if(isBling<2) isBling++;   // 滑窗扩大
        else {
            isBling=0;  // 滑窗清零
            flag = 0;   // 标志位置0
        }
    }         
    EXTI_ClearITPendingBit(EXTI_Line4);    // 清除LINE4上的中断标志位  
}

       
//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX_Init(void)
{
    NVIC_InitTypeDef   NVIC_InitStructure;
    EXTI_InitTypeDef   EXTI_InitStructure;
    
    KEY_Init(); //按键对应的IO口初始化
 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
    
 
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 连接到中断线2
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 连接到中断线3
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 连接到中断线4
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 连接到中断线0
    
  /* 配置EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置
    
    /* 配置EXTI_Line2,3,4 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
 
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
    
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
    
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
       
}
