/*
 * @Author: your name
 * @Date: 2021-04-17 18:35:06
 * @LastEditTime: 2021-04-17 18:44:46
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\Experiment\实验6 独立看门狗实验\main\mian-v4.1.c
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




extern int flag;
void led_breath(u32 t,u32 bright);
void led_breath(u32 t,u32 bright){
    delay_ms(bright);
    LED1=1;
    delay_ms(t-bright);
    LED1=0;
}


int main(void)
{ 
    u16 prer=4;                    
    u16 rlr=500*5;                
    u16 count=0;        
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    delay_init(168);                // 初始化延时函数
    LED_Init();                
    KEY_Init();              
    BEEP_Init();                
    EXTIX_Init();                
    //delay_ms(200);      
    IWDG_Init(prer,rlr); 
    LED1=1;
    delay_ms(100);        
    flag = 0;    

    while(1){        
        int i;
        int totaltime=1000;
        int shorttime=20;
        int circle=totaltime/shorttime;
        for(i=circle;i>=5;i-=1){    
            if(!flag){
                if(count>=2){    
                    LED0=!LED0;
                    BEEP=!BEEP;
                }
            }
            else{
                flag = 0;
                count = 0;
            }
            led_breath(shorttime,shorttime*i/circle);
        }
        for(;i<=circle;i+=1){
            if(!flag){
                if(count>=2){    
                    LED0=!LED0;
                    BEEP=!BEEP;
                }
            }
            else{
                flag = 0;
                count = 0;
            }
            led_breath(shorttime,shorttime*i/circle);
        }
        count++;
    };

}
