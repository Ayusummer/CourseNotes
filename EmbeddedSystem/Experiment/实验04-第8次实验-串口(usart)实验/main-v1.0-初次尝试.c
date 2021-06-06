/*
 * @Author: your name
 * @Date: 2021-05-13 18:57:37
 * @LastEditTime: 2021-05-13 19:02:13
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\实验4-第8次实验-串口(usart)实验\main-v1.0-初次尝试.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"


//ALIENTEK 探索者STM32F407开发板 实验4
//串口通信实验 -库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK


int main(void){ 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     // 设置系统中断优先级分组2
    delay_init(168);        // 延时初始化 
    uart_init(115200);        // 串口初始化波特率为115200
    LED_Init();                  // 初始化与LED连接的硬件接口  
    while(1){
        // do nothing
    }
}

