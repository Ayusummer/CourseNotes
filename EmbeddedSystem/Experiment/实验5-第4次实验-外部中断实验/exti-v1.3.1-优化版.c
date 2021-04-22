/*
 * @Author: your name
 * @Date: 2021-04-22 09:33:45
 * @LastEditTime: 2021-04-22 10:19:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\实验5-第4次实验-外部中断实验\exti-v1.3.1-优化版.c
 */
#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "beep.h"

int width=0;    // 滑动窗口宽度,用于判断LED0是否到了需要改变状态的时候

// 外部中断4服务程序(KEY0,右键)
void EXTI4_IRQHandler(void){
    delay_ms(100);      // 消抖
    if(KEY0==0){
        LED1 = !LED1;    // 测试语句,KEY0按下后LED1反相,用于实测时判断是否检测到了KEY0按下
                     
        if(width == 0 || width == 1) width++;   // 滑窗扩大1格,进入下个状态
        else {                          // width > 1
            if(width == 2);             // width == 2 时再按KEY0滑窗宽度不在增加
            else width=1;               // width > 2  时再按KEY0则滑窗宽度置1
        }
    }         
    EXTI_ClearITPendingBit(EXTI_Line4);    // 清除LINE4上的中断标志位  
}


// 外部中断3服务程序(KEY1,下键)
void EXTI3_IRQHandler(void){
    delay_ms(100);        // 消抖
    if(KEY1==0){
        LED1 = !LED1;   // 测试语句,KEY1按下后LED1反相,用于实测时判断是否检测到了KEY1按下

        if(width == 2 || width == 3) width++;   // 只有2,3两种状态(滑窗宽度)下按下KEY1(下键)才会使滑窗宽度增加
        else width=0;   // 其他情况下按下KEY1(下键)滑窗清零
    }         
    EXTI_ClearITPendingBit(EXTI_Line3);         // 清除LINE3上的中断标志位  
}


// 外部中断2服务程序(KEY2,左键)
void EXTI2_IRQHandler(void){
    delay_ms(100);        // 消抖
    if(KEY2==0){    
        LED1 = !LED1;   // 测试语句,KEY2(左键)按下后LED1反相,用于实测时判断是否检测到了KEY2(左键)按下
        // 当滑窗宽度为4,5,6时按下左键(KEY2)才会使滑窗宽度增加
        if(width == 4 || width == 5 || width == 6 ) width++;    
        else width=0;  // 否则滑窗清零
    }     
    EXTI_ClearITPendingBit(EXTI_Line2); // 清除LINE2上的中断标志位 
}


// 外部中断0服务程序(WK_UP, 上键)
void EXTI0_IRQHandler(void){
    delay_ms(100);        // 消抖
    if(WK_UP==1){       
        LED1 = !LED1;   // 测试语句,WK_UP(上键)按下后LED1反相,用于实测时判断是否检测到了WK_UP(上键)按下
        // 只有当滑窗宽度为7时按下上键(WK_UP)才能滑窗宽度增加,状态达到终态,LED0反相
        if(width==7){
            width++;
            LED0=!LED0;
        }
        // 其它状态下按下上键只会导致滑窗清零
        else width=0; 
    }        
    EXTI_ClearITPendingBit(EXTI_Line0);     // 清除LINE0上的中断标志位 
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
