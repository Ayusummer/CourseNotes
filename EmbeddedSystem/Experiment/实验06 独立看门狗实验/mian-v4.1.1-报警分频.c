/*
 * @Author: your name
 * @Date: 2021-04-17 18:35:06
 * @LastEditTime: 2021-04-28 21:58:44
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\Experiment\实验6 独立看门狗实验\main\main-v4.1.c
 */
/*
 * @Author: your name
 * @Date: 2021-04-16 09:22:26
 * @LastEditTime: 2021-04-16 10:00:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\Experiment\??6 ???????\lc\main.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "iwdg.h"
#include "exti.h"

// LED闪烁函数
void led_blink(u32 t, u32 bright){
    LED1=0; delay_ms(bright);       // 亮 bright ms
    LED1=1; delay_ms(t-bright);     // 灭 t-bright ms
   
}

// 循环自增函数 : x->循环自增变量, limit->循环自增上限
int add_circle(int x, int limit){
    return (x+1) % limit;
}


int main(void){ 
    u16 prer=4;           // 分频系数，预分频系数:4*2^prer=64         
    u16 rlr=500*5;        // 计数重载值       
    u16 count=0;          // 计数变量-用于计算喂狗超时
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);         // 设置系统中断优先级分组2
    delay_init(168);      // 初始化延时函数
    LED_Init();           // 初始化LED端口     
    KEY_Init();           // 初始化按键  
    BEEP_Init();          // 初始化蜂鸣器      
    EXTIX_Init();         // 初始化外部中断输入       

    IWDG_Init(prer,rlr);    // 分频系数为64,重载值为500时,溢出时间为1s
                            // 此实验设计溢出时间为1*5=5s
    LED1=1; delay_ms(100);  // 绿灯(呼吸灯用灯)熄灭100ms-用于指示新一轮看门狗计时开始         

    while(1){           
        int i;                  // 计数器
        int div_alarm = 0;      // 定义报警分频变量
        int totaltime=1000; 
        int shorttime=20;
        int circle=totaltime/shorttime;
        
        // 亮->暗
        for(i=circle; i>=5; i--){  
            // 报警分频变量循环, 第二个参数为自增上限
            div_alarm = add_circle(div_alarm, 5);
            // 如果没喂狗,并且"分频成立",那么超时则红灯反相,蜂鸣器反相(用后面的绿灯闪烁来延时)
            if(!flag){
                if(count>=2 && div_alarm == 4){    
                    LED0=!LED0;
                    BEEP=!BEEP;
                }
            }
            // 如果喂狗了那么喂狗超时计数器置零,喂狗标志位清零
            else{
                count = 0;
                flag = 0;
            }
            led_blink(shorttime,shorttime*i/circle);
        }
        
        // 暗->亮
        for( ; i<=circle; i++){
            // 报警分频变量循环, 第二个参数为自增上限
            div_alarm = add_circle(div_alarm, 5);
            // 如果没喂狗,,并且"分频成立",那么超时则红灯反相,蜂鸣器反相(用后面的绿灯闪烁来延时)
            if(!flag){
                if(count>=2 && div_alarm == 4){      
                    LED0=!LED0;
                    BEEP=!BEEP;
                }
            }
            // 如果喂狗了那么喂狗超时计数器置零,喂狗标志位清零
            else{
                flag = 0;
                count = 0;
            }
            led_blink(shorttime,shorttime*i/circle);
        }
        
        // 一轮呼吸之后喂狗超时计数器+1
        count++;
    };

}
