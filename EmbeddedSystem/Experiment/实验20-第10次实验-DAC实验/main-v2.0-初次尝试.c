     /*
 * @Author: your name
 * @Date: 2021-05-27 19:26:36
 * @LastEditTime: 2021-06-03 17:45:53
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\实验20-第10次实验-DAC实验\main-v2.0-初次尝试.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "dac.h"
#include "key.h"
#include <cmath>

//ALIENTEK 探索者STM32F407开发板 实验21
//DAC实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

#define Pi 3.14 
int main(void){ 
    int i2=0;
    double rad=Pi/180;
    u16 adcx;
    float temp;
    u8 t=0;     
    u16 dacval=0;
    // u8 key;    
    u16 adc[80];
    float temp1;
    float temp2;
    int i=0;
    int j;

    // 设置系统中断优先级分组2
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    delay_init(168);    // 初始化延时函数
    uart_init(115200);  // 初始化串口波特率为115200
    
    LED_Init();         // 初始化LED 
    LCD_Init();         // LCD初始化
    Adc_Init();         // adc初始化
    KEY_Init();         // 按键初始化
    Dac1_Init();        // DAC通道1初始化    
    POINT_COLOR=RED; 
    
    LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");    
    LCD_ShowString(30,70,200,16,16,"DAC TEST");    
    LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
    LCD_ShowString(30,110,200,16,16,"2014/5/6");     
    LCD_ShowString(30,130,200,16,16,"WK_UP:+  KEY1:-");     
    
    // 电压值显示
    POINT_COLOR=BLUE;       // 设置字体为蓝色             
    LCD_ShowString(30,150,200,16,16,"DAC VAL:");          
    LCD_ShowString(30,170,200,16,16,"DAC VOL:0.000V");          
    LCD_ShowString(30,190,200,16,16,"ADC VOL:0.000V");
    
    // y轴, 箭头, 标注
    LCD_DrawLine(50,320,50,500);    
    LCD_DrawLine(50,320,45,335);    
    LCD_DrawLine(50,320,55,335);
    LCD_ShowString(70,320,200,16,16,"VOL");

    // x轴, 箭头, 标注
    LCD_DrawLine(50,500,300,500);
    LCD_DrawLine(300,500,285,495);
    LCD_DrawLine(300,500,285,505);
    LCD_ShowString(305,515,200,16,16,"TIME");    
       
    while(1){
        if(i2>=360) 
            i2=0;    
        i2=i2+5;
        
        // 设置初始值
        dacval=(int)(sin(i2*rad)*500+600);    
        DAC_SetChannel1Data(DAC_Align_12b_R, dacval);

        POINT_COLOR=BLUE;
        // 读取前面设置DAC的值
        adcx=DAC_GetDataOutputValue(DAC_Channel_1);
        LCD_ShowxNum(94,150,adcx,4,16,0);   // 显示DAC寄存器值
        temp=(float)adcx*(3.3/4096);        // 得到DAC电压值
        adcx=temp;
        LCD_ShowxNum(94,170,temp,1,16,0);   // 显示电压值整数部分
        // 显示电压值的小数部分
        temp-=adcx;
        temp*=1000;
        LCD_ShowxNum(110,170,temp,3,16,0X80);        

         
        adcx=Get_Adc_Average(ADC_Channel_5,10);     // 得到ADC转换值         
        temp=(float)adcx*(3.3/4096);        // 得到ADC电压值             
        adcx=temp;
        temp1=adcx*100;
        LCD_ShowxNum(94,190,temp,1,16,0);   // 显示电压值整数部分          
        temp-=adcx;
        temp*=1000;
        temp2=temp/10;
        adcx=temp2;
        temp1=temp1+adcx;
        LCD_ShowxNum(110,190,temp,3,16,0X80);   // 显示电压值的小数部分
        

        POINT_COLOR=RED;
        
        // 待显示曲线上坐标值生成
        if(i<80){
             adc[i]=temp1;
        }else{
            for(j=0;j<79;j++){
                adc[j]=adc[j+1];
            }
            adc[79]=temp1;
        }
        
        /* 每两点绘制连线 */
        // 第1论
        if(i<80){
            if(i==0){
                ++i;
            }else{
                LCD_DrawLine(55+(i-1)*3, 495-adc[i-1] ,55+(i)*3, 495-adc[i]);
                ++i;
            }
        }
        // 一轮之后(要清屏)
        else{
            LCD_Fill(55,346,299,489,WHITE);     // 清屏
            for(j=0;j<i-1;j++){
                LCD_DrawLine(55+j*3, 495-adc[j], 55+(j+1)*3, 495-adc[j+1]);
            }
        }                    
    }
}    

