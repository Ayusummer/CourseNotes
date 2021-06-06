/*
 * @Author: your name
 * @Date: 2021-04-22 19:36:46
 * @LastEditTime: 2021-04-22 19:37:52
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\实验8-第6次实验-定时器中断实验\exti-v2.0-初次尝试.h
 */
#ifndef __EXTI_H
#define __EXIT_H     
#include "sys.h"      
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

extern int status0;    // LED0的状态: 0->熄灭, 1->闪烁
extern int status1;    // LED1的状态: 0->熄灭, 1->闪烁

void EXTIX_Init(void);    //外部中断初始化                                 
#endif