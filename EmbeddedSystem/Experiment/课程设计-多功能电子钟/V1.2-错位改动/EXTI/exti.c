#include "exti.h"
#include "delay.h" 
#include "key.h"
#include "beep.h"
#include "rtc.h"
#include "led.h"

//是否整点、闹钟的标志
int flag;

//当前时间、日期信息
int hour,minute,second;
int year,month,day,week;

//一个打杂的变量
int temp;


//外部中断0服务程序(上键)
//校时间、校日期的功能
//主要是对各个参数进行增加
//特别注意,日期改变需要重新获取一下星期
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(WK_UP==1){
		switch(choice){
			//关闭闹钟、整点报时
			case 0:flag=0;BEEP=0;LED0=1;break;
			case 1:if(hour==23){hour=0;}else{hour++;}break;
			case 2:if(minute==59){minute=0;}else{minute++;}break;
			case 3:if(second==59){second=0;}else{second++;}break;
			case 4:if(year<99) year++;
			         else year=1;
			       week=RTC_Get_Week(year,month,day);break;
			case 5:if(month==12) month=1;
               else month++;
						 week=RTC_Get_Week(year,month,day);break;
			case 6:temp=year+2000;
				     if(   (day==28 && month==2 && !(((temp%4==0) && (temp%100!=0)) || temp%400==0))//二月平年
				         ||(day==29 && month==2 &&  (((temp%4==0) && (temp%100!=0)) || temp%400==0))//二月闰年
			           ||(day==30 && (month==4 || month==6 || month==9 || month==11))//小月
						     || day==31)//大月
				          day=1;
             else  day++;
						 week=RTC_Get_Week(year,month,day);break;
		}
		RTC_Set_Time(hour,minute,second,RTC_H12_AM);	//设置时间
	  RTC_Set_Date(year,month,day,week);		//设置日期
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
}

//外部中断2服务程序(左)
//改变当前功能序号,减小
void EXTI2_IRQHandler(void)
{	
	delay_ms(10);	//消抖
	if(KEY2==0){
		if(choice>0) choice--;
	}
	//清除LINE2上的中断标志位
	EXTI_ClearITPendingBit(EXTI_Line2);
}

//外部中断3服务程序(下)
//校时间、校日期的功能
//主要是对各个参数进行减小
//特别注意,日期改变需要重新获取一下星期
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY1==0){
		switch(choice){
			case 1:if(hour==0){hour=23;}else{hour--;}break;
			case 2:if(minute==0){minute=59;}else{minute--;}break;
			case 3:if(second==0){second=59;}else{second--;}break;
			case 4:if(year>1)
				       year--;
			       else year=99;
			       week=RTC_Get_Week(year,month,day);break;
			case 5:if(month==1)
               month=12;
             else month--;
			       week=RTC_Get_Week(year,month,day);break;
			case 6:temp=year+2000;
				     if(day==1)
							   if(month==2 && !(((temp%4==0) && (temp%100!=0)) || temp%400==0))//二月平年
									   day=28;
				         else if(month==2 && (((temp%4==0) && (temp%100!=0)) || temp%400==0))//二月闰年
									   day=29;
			           else if(month==4 || month==6 || month==9 || month==11)//小月
									   day=30;
						     else day=31;//大月
             else day--;
						 week=RTC_Get_Week(year,month,day);break;
		}
		//更新时间、日期
		RTC_Set_Time(hour,minute,second,RTC_H12_PM);
	  RTC_Set_Date(year,month,day,week);
	}
	//清除LINE3上的中断标志位  
	EXTI_ClearITPendingBit(EXTI_Line3);
}

//外部中断4服务程序(右)
//改变当前功能序号,增加
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY0==0){	 
		if(choice<6) choice++;
	}
	//清除LINE4上的中断标志位
	EXTI_ClearITPendingBit(EXTI_Line4);
}

//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	KEY_Init(); //按键对应的IO口初始化 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 连接到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 连接到中断线3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 连接到中断线4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 连接到中断线0
	
  /* 配置EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置
	
	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
		
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置	   
}
