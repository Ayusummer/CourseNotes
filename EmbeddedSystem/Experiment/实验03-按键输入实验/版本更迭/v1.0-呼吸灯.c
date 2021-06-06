/*
 * @Author: your name
 * @Date: 2021-04-10 17:22:07
 * @LastEditTime: 2021-04-11 11:42:52
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\Experiment\实验3-按键输入实验\v1.0-呼吸灯.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"

/* LED灯闪烁 */
void led_blink(u32 t,u32 bright){
    LED0=0;             // 亮
    delay_ms(bright);   // 保持亮
    LED0=1;             // 暗
    delay_ms(t-bright); // 保持暗
}

int main(void)
{ 
 
    u8 key;               // 保存键值
    delay_init(168);      // 初始化延时函数
    LED_Init();            // 初始化LED端口 
    BEEP_Init();          // 初始化蜂鸣器端口
    KEY_Init();           // 初始化与按键连接的硬件接口
    LED0=0;                // 先点亮红灯
    
    while(1){
        key=KEY_Scan(0);                // 扫描按键
        if(key){                        // 若有按键
            switch(key){
                case WKUP_PRES:
                    break;
                case KEY2_PRES:
                    break;
                case KEY1_PRES:            // 按下KEY1
                    LED0=1;                // 熄灭LED0
                    break;
                case KEY0_PRES:
                    while(1){
                        int flag=0;
                        int i;
                        int breath_time_total=2000;                        // 整个周期，1500ms->1.5s->模拟呼吸,吸气呼气各1.5s
                        int breath_single_time=20;                        // 人眼可见最短的图像滞留周期即每个周期的时间，20ms
                        int breath_times=breath_time_total/breath_single_time;    // 周期数75

                        for(i=breath_times;i>=20;i-=1){                // 周期总数递减->从亮到暗
                            if(KEY_Scan(1)==KEY1_PRES){                // 若按下KEY1
                                flag=1;                                // Key1按下立flag
                                LED0=1;
                                break;                                // 跳出for循环
                            }
                            led_blink(breath_single_time,breath_single_time*i/breath_times);    //呼吸灯闪烁
                        }
                        
                        for(i=20;i<=breath_times;i++){                // 周期总数自增->75,从暗到亮
                            if(KEY_Scan(1)==KEY1_PRES){                // 若按下KEY1
                                flag=1;                                // 灭灯立flag
                                LED0=1;
                                break;                                // 跳出for循环
                            }
                            led_blink(breath_single_time,breath_single_time*i/breath_times);    //呼吸灯闪烁
                        }
                        
                        if(KEY_Scan(1)==KEY1_PRES || flag == 1){            // 若按下KEY1或flag已立下
                            LED0=1;                                    // 灭灯
                            break;                                    // 跳出wile循环
                        }
                        
                    }
                    break;
            }
        }
    }
}
