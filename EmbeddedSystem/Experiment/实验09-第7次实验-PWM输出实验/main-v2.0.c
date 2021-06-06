/*
 * @Author: your name
 * @Date: 2021-04-29 19:39:15
 * @LastEditTime: 2021-04-29 19:55:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\实验9-第7次实验-PWM输出实验\main-v2.0.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "math.h"
#include "exti.h"

//ALIENTEK 探索者STM32F407开发板 实验9
//PWM输出实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
//extern int Flag;

#define  PI 3.1415926

int main(void){ 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
    delay_init(168);      // 初始化延时函数
    uart_init(115200);    // 初始化串口波特率为115200
    EXTIX_Init();
    TIM14_PWM_Init(500-1,84-1);        // a84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.     
    
    int i=0,x=1;
    u16 led0pwmval=0; 
       
       while(1){ 
        delay_ms(100);    // 消抖     
        if(!Flag){
            printf("       ");
            if(x>=16){
                for(i=0; i<led0pwmval/5; i++)  printf("*"); 
                printf("\r\n");
            }
            else{
                for(i=0; i<led0pwmval/5;i++)    printf(" "); 
                printf("*\r\n");
            }
            
            if(x<16)    x++;
            else x=1;     // 1-16

            led0pwmval=300*sin(2*x*PI/64);
            
        TIM_SetCompare1(TIM14, led0pwmval);    // 修改比较值，修改占空比
        }
    }    
}
