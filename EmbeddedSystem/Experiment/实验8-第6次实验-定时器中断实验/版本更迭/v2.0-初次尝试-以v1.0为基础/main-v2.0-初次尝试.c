/*
 * @Author: your name
 * @Date: 2021-04-22 19:34:19
 * @LastEditTime: 2021-04-22 19:41:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\实验8-第6次实验-定时器中断实验\main-v2.0-初次尝试.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "timer.h"

//ALIENTEK 探索者STM32F407开发板 实验5
//外部中断实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司    
//作者：正点原子 @ALIENTEK 
void blink0(){
    LED0 = !LED0;
    delay_ms(100);
}



int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     // 设置系统中断优先级分组2
	delay_init(168);    // 初始化延时函数
	uart_init(115200); 	// 串口初始化 
	LED_Init();			// 初始化LED端口  
	EXTIX_Init();       // 初始化外部中断输入 

 	TIM3_Int_Init(5000-1, 8400-1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数5000次为500ms     
	while(1){
        if(status0 == 0){
            LED0 = 1;
        }
        else blink0();
    };

}