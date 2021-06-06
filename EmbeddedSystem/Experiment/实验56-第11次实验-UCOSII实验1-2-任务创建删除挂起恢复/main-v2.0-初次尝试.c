#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "includes.h"
#include "key.h"
#include "beep.h"
#include "lcd.h"
#include "adc.h"
#include <cmath>
//ALIENTEK 探索者STM32F407开发板 实验56
//UCOSII实验1-2 任务创建，删除，挂起，恢复  -库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK


/////////////////////////UCOSII任务堆栈设置///////////////////////////////////
//START 任务
//设置任务优先级
#define START_TASK_PRIO                  10 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE                  64
//创建任务堆栈空间    
__align(8) OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数接口
void start_task(void *pdata);    

#define ADC_TASK_PRIO                   8
#define ADC_STK_SIZE                      128
__align(8) OS_STK ADC_TASK_STK[ADC_STK_SIZE];
void adc_task(void *pdata);

//LED任务
//设置任务优先级
#define LED_TASK_PRIO                   7 
//设置任务堆栈大小
#define LED_STK_SIZE                      64
//创建任务堆栈空间    
__align(8) OS_STK LED_TASK_STK[LED_STK_SIZE];
//任务函数接口
void led_task(void *pdata);


//蜂鸣器任务
//设置任务优先级
#define BEEP_TASK_PRIO                   5 
//设置任务堆栈大小
#define BEEP_STK_SIZE                      64
//创建任务堆栈空间    
__align(8) OS_STK BEEP_TASK_STK[BEEP_STK_SIZE];
//任务函数接口
void beep_task(void *pdata);


//按键扫描任务
//设置任务优先级
#define KEY_TASK_PRIO                   3 
//设置任务堆栈大小
#define KEY_STK_SIZE                      64
//创建任务堆栈空间    
__align(8) OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//任务函数接口
void key_task(void *pdata);
#define PI 3.1415

int main(void)
{ 
  
    delay_init(168);          //初始化延时函数
    uart_init(115200);
    LED_Init();                  //初始化与LED连接的硬件接口
    BEEP_Init();            //蜂鸣器初始化    
    KEY_Init();                //按键初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
    OSInit();                   //初始化UCOSII
    LCD_Init();         //初始化LCD接口
  Adc_Init();         //初始化ADC    
     OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
    OSStart();    
}

//开始任务
void start_task(void *pdata)
{
  OS_CPU_SR cpu_sr=0;
    pdata = pdata;                                  
    OSStatInit();                    //初始化统计任务.这里会延时1秒钟左右    
     OS_ENTER_CRITICAL();            //进入临界区(无法被中断打断)    
     OSTaskCreate(led_task,(void *)0,(OS_STK*)&LED_TASK_STK[LED_STK_SIZE-1],LED_TASK_PRIO);                                               
     OSTaskCreate(beep_task,(void *)0,(OS_STK*)&BEEP_TASK_STK[BEEP_STK_SIZE-1],BEEP_TASK_PRIO);                                           
     OSTaskCreate(key_task,(void *)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);    
    OSTaskCreate(adc_task,(void *)0,(OS_STK*)&ADC_TASK_STK[KEY_STK_SIZE-1],ADC_TASK_PRIO);
     OSTaskSuspend(START_TASK_PRIO);    //挂起起始任务.
    OS_EXIT_CRITICAL();                //退出临界区(可以被中断打断)
}    

//adc任务
void adc_task(void *pdata)
{
    u16 i=0,j=0,n,m;
     u16 adcx;
    u16 num[60];
    float temp;

    POINT_COLOR=RED; 
    LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");    
    LCD_ShowString(30,70,200,16,16,"ADC TEST");    
    LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
    LCD_ShowString(30,110,200,16,16,"2014/5/6");      
    POINT_COLOR=BLUE;//???????
    LCD_ShowString(30,130,200,16,16,"ADC1_CH5_VAL:");          
    LCD_ShowString(30,150,200,16,16,"ADC1_CH5_VOL:0.000V");    //???????????   
        LCD_ShowString(30,200,10,16,16,"VOL");   
        LCD_DrawLine(50,550,50,250);//??
        LCD_DrawLine(50,250,55,255);
    LCD_DrawLine(50,250,45,255);
    LCD_ShowString(450,555,10,16,16,"TIME");
    LCD_DrawLine(50,550,450,550);//??
    LCD_DrawLine(450,550,445,545);
    LCD_DrawLine(450,550,445,555);    
    while(1)
    { 
        adcx=Get_Adc_Average(ADC_Channel_5,20);//????5????,20????
        LCD_ShowxNum(134,130,adcx,4,16,0);    //??ADCC???????
        temp=(float)adcx*(3.3/4096);          //???????????????,??3.1111
        adcx=temp;                            //???????adcx??,??adcx?u16??
        LCD_ShowxNum(134,150,adcx,1,16,0);    //??????????,3.1111??,??????3
        temp-=adcx;                           //????????????,??????,??3.1111-3=0.1111
        temp=temp*1000;                           //??????1000,??:0.1111????111.1,??????????
        LCD_ShowxNum(150,150,temp,3,16,0X80); //??????(??????????),???????111.

        if(i<60)
        {
            num[i]=temp;
            i++;
            if(j>0)
                LCD_DrawLine(45+j*5,num[j-1]+250,50+j*5,num[j]+250);
            j++;
        }
        if(i>=60)
        {
      i++;
            LCD_Fill(51,200,494,544,WHITE);//??????
            for(m=0;m<59;m++){
                num[m]=num[m+1];
            }
            num[59]=temp;
            for(n=1;n<60;n++)
            {
                LCD_DrawLine(45+n*5,num[n-1]+250,50+n*5,num[n]+250);
            }
        }
        delay_ms(100);    
    }

}    
//LED任务
void led_task(void *pdata)
{   
    while(1)
    {  
        if(OSTaskDelReq(OS_PRIO_SELF)==OS_ERR_TASK_DEL_REQ) //判断是否有删除请求
         {
         OSTaskDel(OS_PRIO_SELF);                           //删除任务本身TaskLed
         }
       LED0=!LED0;
         LED1=!LED1;
       delay_ms(500);
    }                                     
}       

//蜂鸣器任务
void beep_task(void *pdata)
{
    while(1)
    {      
       if(OSTaskDelReq(OS_PRIO_SELF)==OS_ERR_TASK_DEL_REQ) //判断是否有删除请求
         {
            OSTaskDel(OS_PRIO_SELF);                           //删除任务本身TaskLed
         }
         BEEP=1;
       delay_ms(50);
        BEEP=0;
         delay_ms(950);
    }                                     
}

//按键扫描任务
void key_task(void *pdata)
{    
    u8 key;                                     
    while(1)
    {
        key=KEY_Scan(0);
        if(key==KEY0_PRES)
        {
          OSTaskSuspend(ADC_TASK_PRIO);//挂起ADC任务
        }
        else if (key==KEY2_PRES)
        {
          OSTaskResume(ADC_TASK_PRIO);    //恢复ADC任务
        }
        else if (key==WKUP_PRES)
        {
            OSTaskDelReq(BEEP_TASK_PRIO);    //发送删除BEEP任务请求，任务睡眠，无法恢复
            OSTaskDelReq(LED_TASK_PRIO);        
        }
        else if(key==KEY1_PRES)
        {
         OSTaskCreate(beep_task,(void *)0,(OS_STK*)&BEEP_TASK_STK[BEEP_STK_SIZE-1],BEEP_TASK_PRIO);//重新创建任务beep
     OSTaskCreate(led_task,(void *)0,(OS_STK*)&LED_TASK_STK[LED_STK_SIZE-1],LED_TASK_PRIO);//重新创建任务beep
        }   
         delay_ms(10);
    }
}
