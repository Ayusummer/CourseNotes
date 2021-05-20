/*
 * @Author: nosteglic
 * @Date: 2021-05-19 22:18:23
 * @LastEditTime: 2021-05-20 14:18:00
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\实验18-第9次实验-ADC实验\main-v1-初次尝试.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"


//ALIENTEK 探索者STM32F407开发板 实验18
//ADC模数转换实验-库函数版本  
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

#define len 20
#define minus 30

u16 buffer[len];
static int pos=0;
u16 x1,x2,y1,y2;

/*滚动，双标记位实现循环数组*/
void draw_roll(u16 buffer[],u16 temp){
    int i;
    int flag=0,round=0;
    pos=pos%len;
    buffer[pos]=temp;
    pos++;
    x1=30;
    y1=buffer[0];
    if(pos==len){
        i=0;
        round=1;
    }
    else
        i=pos;
    while(!flag||!round){//其实只要!flag就行
        x2=x1+400/len;
        y2=buffer[i];
        LCD_DrawLine(x1,y1,x2,y2);
        x1=x2;
        y1=y2;
        if(i==len-1){
            round=1;
            i=0;
        }
        else
            i++;
        if(round&&(i==pos%len))
            flag=1;
    }//while(!flag||!round)
}

/*局部清屏，避免抖动*/
void clean_lcd(void){
    LCD_Fill(31,lcddev.height/2-80, 430,lcddev.height/2+80,WHITE);    
}


int main(void){ 
    u16 adcx;       // 存放adc值 
    float temp;     // 暂存adc值
    int count=0;    // 用于判断是否是第一轮画线
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     // 设置系统中断优先级分组2
    delay_init(168);        // 初始化延时函数
    uart_init(115200);      // 初始化串口波特率为115200
    LED_Init();             // 初始化LED 
    LCD_Init();             // 初始化LCD
    Adc_Init();             // 初始化ADC
    
    POINT_COLOR=RED;        // 画笔设为红色

    /*在屏幕正中偏下方显示电压值*/
    LCD_ShowString(lcddev.width*2/5, lcddev.height*9/10, 200,16,16,"ADC=0.000V");
    
    /*x，y轴显示*/
    LCD_DrawLine(30,lcddev.height/2+100,30,lcddev.height/2-100);
    LCD_DrawLine(30,lcddev.height/2+100,430,lcddev.height/2+100);
    LCD_DrawLine(30,lcddev.height/2-100,30-5,lcddev.height/2-100+15);
    LCD_DrawLine(30,lcddev.height/2-100,30+5,lcddev.height/2-100+15);
    LCD_DrawLine(430,lcddev.height/2+100,430-15,lcddev.height/2+100-5);
    LCD_DrawLine(430,lcddev.height/2+100,430-15,lcddev.height/2+100+5);
    LCD_ShowString(30+5+5,lcddev.height/2-100,200,16,16,"VOL");
    LCD_ShowString(430,lcddev.height/2+100+5,200,16,16,"TIME");
    
    /*初始化第一个点*/
    x1=30;
    y1=lcddev.height/2;
    delay_ms(500);
    
    while(1){
        adcx=Get_Adc_Average(ADC_Channel_5,20);    //获取通道5的转换值，20次取平均 about 3835~3837
        temp=(float)adcx*(3.3/4096);            //转换的电压值
        
        /*显示整数*/
        adcx=temp;
        LCD_ShowxNum(32+lcddev.width*2/5,lcddev.height*9/10,adcx,1,16,0);
        
        /*显示小数*/
        temp-=adcx;
        temp=temp*1000;
        LCD_ShowxNum(47+lcddev.width*2/5,lcddev.height*9/10,temp,3,16,0x80);
        
        if(count<len){                            //第一轮
            x2=x1+400/len;                        //每隔400/len画一个像素点
            y2=(minus-temp)*5+lcddev.height/2;    //放大电压差异
            buffer[pos]=y2;                        //电压缓冲区
            pos++;
            count++;
            LCD_DrawLine(x1,y1,x2,y2);
            x1=x2;
            y1=y2;
        }
        
        if(count==len){                            //不是第一轮
            clean_lcd();                        //清屏
            temp=(minus-temp)*5+lcddev.height/2;//放大电压差异
            draw_roll(buffer,temp);                //滚动
        }
    }//while(1)
}



