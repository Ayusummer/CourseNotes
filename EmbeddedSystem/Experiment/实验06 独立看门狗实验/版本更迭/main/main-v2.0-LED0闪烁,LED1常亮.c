/*
 * @Author: your name
 * @Date: 2021-04-15 22:16:21
 * @LastEditTime: 2021-04-16 07:26:23
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\Experiment\实验6 独立看门狗实验\main-v1.0.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "iwdg.h"
#include "exti.h"

//ALIENTEK 探索者STM32F407开发板 实验6
//独立看门狗实验 -库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司   
//作者：正点原子 @ALIENTEK

/*声光报警*/
void mywarning(void){
    LED0=!LED0;
    BEEP=!BEEP;
    delay_ms(100);
}

int main(void)
{ 
    u16 prer=4;                    // 分频系数，预分频系数:4*2^prer=64
    u16 rlr=500*5;                // 计数重载值
    u16 count=0;                // 计数变量
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    // 设置系统中断优先级分组2
    delay_init(168);            // 初始化延时函数
    LED_Init();                    // 初始化LED端口
    KEY_Init();                    // 初始化按键
    BEEP_Init();                // 初始化蜂鸣器
    EXTIX_Init();                // 初始化外部中断输入

    delay_ms(200);                // 延时200ms 
    IWDG_Init(prer,rlr);        // 分频系数为64,重载值为500时,溢出时间为1s
                                // 此实验设计溢出时间为1*5=5s
                                
    LED1=0;                        // 先点亮绿灯
    
    while(1){
        count++;
        if(!flag){                //当没有喂狗
            if(count>=380){        //程序大约还剩2s运行结束
                mywarning();    //喂狗报警提示
            }
        }
        else{                    //当喂狗了
            count=0;            //重新计数
            flag=0;                //清除喂狗标志
        }
        delay_ms(10);            //小延时
    };

}



