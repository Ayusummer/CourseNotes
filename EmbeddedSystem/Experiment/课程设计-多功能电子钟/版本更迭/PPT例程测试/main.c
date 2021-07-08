/*
 * @Author: your name
 * @Date: 2021-07-07 21:11:11
 * @LastEditTime: 2021-07-08 09:34:18
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\课程设计-多功能电子钟\版本更迭\PPT例程测试\main.c
 */
#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "lcd.h"
#include "usmart.h"
#include "rtc.h"

//ALIENTEK 探索者STM32F407开发板 实验15
//RTC实时时钟 实验 -库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK


int main(void){ 

    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;

    u8 tbuf[40];
    u8 t=0;
	// 设置系统中断优先级分组 2
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);        
    delay_init(168);		// 初始化延时函数
    uart_init(115200);      // 初始化串口波特率为 115200
    
    usmart_dev.init(84);    // 初始化 USMART    
    LED_Init();             // 初始化 LED
    LCD_Init();             // 初始化 LCD
    My_RTC_Init();          // 初始化 RTC
 
	// 配置 WAKE UP中断,1 秒钟中断一次
    RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);        
    
    POINT_COLOR=RED;
    LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");    
    LCD_ShowString(30,70,200,16,16,"RTC TEST");    
    LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
    LCD_ShowString(30,110,200,16,16,"2021/7/5");    
    
	while(1){        
        t++;
		// 每 100ms 更新一次显示数据
        if((t%10)==0) {
			RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
            
            sprintf((char*)tbuf,"Time:%02d:%02d:%02d",
					RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds); 
            LCD_ShowString(30,140,210,16,16,tbuf);    
            
            RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
            
            sprintf((char*)tbuf,"Date:20%02d-%02d-%02d",
					RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date); 
            LCD_ShowString(30,160,210,16,16,tbuf);    
            sprintf((char*)tbuf,"Week:%d",RTC_DateStruct.RTC_WeekDay); 
            LCD_ShowString(30,180,210,16,16,tbuf);
        } 
        if((t%20)==0)LED0=!LED0;    // 每200ms,翻转一次LED0 
        delay_ms(10);
    }    
}
