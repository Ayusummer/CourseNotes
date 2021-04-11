/*
 * @Author: your name
 * @Date: 2021-04-11 12:09:36
 * @LastEditTime: 2021-04-11 12:15:44
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\Experiment\实验3-按键输入实验\v1.0.2-呼吸灯-简化逻辑-只判断下键右键.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
typedef enum {FALSE = 0，TRUE = 1} bool；// bool宏定义

/* LED灯闪烁 */
void led_blink(u32 t,u32 bright){
    LED0=0;             // 亮
    delay_ms(bright);   // 保持亮
    LED0=1;             // 暗
    delay_ms(t-bright); // 保持暗
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
  u8 key;               // 保存键值
  delay_init(168);      // 初始化延时函数
  LED_Init();           // 初始化LED端口 
  BEEP_Init();          // 初始化蜂鸣器端口
  KEY_Init();           // 初始化与按键连接的硬件接口
  LED0=0;               // 先点亮红灯
  
  while(1){
    key=KEY_Scan(0);        // 扫描按键
    // KEY1熄灭LED0
    if(KEY_Scan(1) == KEY1_PRES) LED0=1;  
    // KEY0呼吸灯
    else if(KEY_Scan(1) == KEY0_PRES){
          while(1){
            int flag=0;
            int i;
            int breath_time_total=1500;             // 整个周期，1500ms->1.5s->模拟呼吸,吸气呼气各1.5s
            int breath_single_time=20;              // 人眼可见最短的图像滞留周期即每个周期的时间，20ms
            int breath_times=breath_time_total/breath_single_time;  // 周期数75
            int breath_left_times = 20;             // 呼吸保周期次数,相应的要占满75个周期就要求周期从周期数+保留次数开始
            int breath_times_max = breath_times + breath_left_times;   // 呼吸周期最大次数
            // 周期总数递减->从亮到暗
            for(i=breath_times_max; i>=breath_left_times; i--){        
              // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
              if(led_off(KEY_Scan(1),flag))   break;  
              led_blink(breath_single_time, breath_single_time*i/breath_times_max);  //LED灯闪烁
            }
            // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
            if(led_off(KEY_Scan(1),flag))   break;  
            // 周期总数自增->breath_times_max,从暗到亮
            for(i=breath_left_times;i<=breath_times_max;i++){       
              // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
              if(led_off(KEY_Scan(1),flag))   break;  
              led_blink(breath_single_time,breath_single_time*i/breath_times_max);  //LED灯闪烁
            }
            // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
            if(led_off(KEY_Scan(1),flag))   break;  
          } // 呼吸灯循环
          break;//KEY0 -> case -> break
    } // KEY0结束
  } // 整个程序循环体
} // main()函数
