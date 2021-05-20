/*
 * @Author: your name
 * @Date: 2021-04-15 22:16:21
 * @LastEditTime: 2021-04-17 19:07:50
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
typedef enum {FALSE = 0，TRUE = 1} bool；// bool宏定义

/*声光报警*/
void mywarning(void){
    LED0=!LED0;
    //BEEP=!BEEP;
    delay_ms(100);
}

/* LED灯闪烁 */
void led_blink(u32 t,u32 bright){
    LED1=0;             // 亮
    delay_ms(bright);   // 保持亮
    LED1=1;             // 暗
    delay_ms(t-bright); // 保持暗
}

/*熄灯判断*/
bool led_off(int flag_breath){
  if(flag_breath==1){
    LED1 = 1;   // 灭灯
    return TRUE;
  }
  else return FALSE;
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
    
    /*
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
    */
while(1){
    int flag_breath=0;
    int i;
    int breath_time_total=5000;             // 整个周期，1500ms->1.5s->模拟呼吸,吸气呼气各1.5s
    int breath_single_time=20;              // 人眼可见最短的图像滞留周期即每个周期的时间，20ms
    int breath_times=breath_time_total/breath_single_time;  // 周期数75
    int breath_left_times = 20;             // 呼吸保周期次数,相应的要占满75个周期就要求周期从周期数+保留次数开始
    int breath_times_max = breath_times + breath_left_times;   // 呼吸周期最大次数
    
    
    // 周期总数递减->从亮到暗
    for(i=breath_times_max; i>=breath_left_times; i--){        
        // 若按下KEY1或者KEY1已经按下(flag_breath==1)则熄灯并跳出呼吸循环
        if(led_off(flag_breath))   break;  
        led_blink(breath_single_time, breath_single_time*i/breath_times_max);  //LED灯闪烁
    }
    // 若按下KEY1或者KEY1已经按下(flag_breath==1)则熄灯并跳出呼吸循环
    if(led_off(flag_breath))   break;  
    // 周期总数自增->breath_times_max,从暗到亮
    for(i=breath_left_times;i<=breath_times_max;i++){       
        // 若按下KEY1或者KEY1已经按下(flag_breath==1)则熄灯并跳出呼吸循环
        if(led_off(flag_breath))   break;  
        led_blink(breath_single_time,breath_single_time*i/breath_times_max);  //LED灯闪烁
    }
    // 若按下KEY1或者KEY1已经按下(flag_breath==1)则熄灯并跳出呼吸循环
    if(led_off(flag_breath))   break;  


} // 呼吸灯循环

}



