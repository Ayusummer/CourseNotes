/*
 * @Author: your name
 * @Date: 2021-04-10 19:11:19
 * @LastEditTime: 2021-04-11 12:06:27
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\Experiment\实验3-按键输入实验\V1.1-呼吸灯.c
 */
/*
 * @Author: your name
 * @Date: 2021-04-10 17:22:07
 * @LastEditTime: 2021-04-10 19:10:08
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
typedef enum {FALSE = 0，TRUE = 1} bool；// bool宏定义

/*LED灯闪烁*/
void led_blink(u32 t,u32 bright){
    LED0=0;                  // 亮
    delay_us(bright);        // 保持亮,注意是us微秒
    LED0=1;                  // 暗
    delay_us(t-bright);      // 保持暗,注意是us微秒
}

/*熄灯判断*/
bool led_off(u8 key, int flag){
    if(key == KEY1_PRES || flag==1){
        flag = 1;   // KEY1按下flag置1补齐逻辑
        LED0 = 1;   // 灭灯
        return TRUE;
    }
    else return FALSE;
}

int main(void){ 
    u8 key;            // 保存键值
    delay_init(168);   // 初始化延时函数
    LED_Init();        // 初始化LED端口 
    BEEP_Init();       // 初始化蜂鸣器端口
    KEY_Init();        // 初始化与按键连接的硬件接口
    LED0=0;            // 先点亮红灯
 
    while(1){
        key=KEY_Scan(0);    // 得到键值
        if(key){            // 如果键值不为空->若有按键
            switch(key){    
                case WKUP_PRES:     // 上键不操作
                    break;
                case KEY2_PRES:     // 左键不操作
                    break;
                case KEY1_PRES:     // KEY1(下键)灭红灯
                    LED0=1;         // 熄灭LED0(红灯)
                    break;
                case KEY0_PRES:     // KEY0(右键)呼吸灯
                    while(1){       // 循环执行呼吸灯,直至按下下键跳出循环
                        int breath_time_total = 1500;  // 整个周期，1500ms->1.5s->模拟呼吸,吸气呼气各1.5s
                        int breath_time_left = 100;
                        int i;          // 计数器
                        int flag=0;     // 灭灯标记
                        
                        // 亮->暗
                        for(i=breath_time_total; i>breath_time_left; i--){
                            // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
                            if(led_off(KEY_Scan(1),flag))   break;  
                            // 亮i us灭breath_time_total+breath_time_left-i ms
                            led_blink(breath_time_total+breath_time_left,i);         
                        }
                        
                        // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
                        if(led_off(KEY_Scan(1),flag))   break;  

                        for(i=breath_time_left;i<breath_time_total;i++){
                            // 若按下KEY1则熄灯并跳出暗->亮循环
                            if(led_off(KEY_Scan(1),flag))   break;  
                             // 亮i us灭breath_time_total+breath_time_left-i us
                            led_blink(breath_time_total,i);        
                        }
                        
                        // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
                        if(led_off(KEY_Scan(1),flag))   break;  

                    }   // 呼吸灯循环
                    break;  //KEY0 -> case -> break
            }   // 按键判断
        }   // 若有按键
    }   // 整个程序循环体
}   // main()函数
