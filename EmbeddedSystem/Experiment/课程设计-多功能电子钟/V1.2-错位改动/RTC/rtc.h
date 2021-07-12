#ifndef __RTC_H
#define __RTC_H	 
#include "sys.h" 
#include "stdbool.h"

 //////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//RTC 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/5
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
//********************************************************************************
//修改说明
//V1.1 20140726
//新增:RTC_Get_Week函数,用于根据年月日信息,得到星期信息.
////////////////////////////////////////////////////////////////////////////////// 

extern int flag;
extern int cnt;
extern int hour,minute,second;
extern int year,month,day,week;

//闹钟信息存储结构体数组
extern struct Alarm
{
    int hour, minute, second, week;
}alarms[100];

	
u8 My_RTC_Init(void);						//RTC初始化
ErrorStatus RTC_Set_Time(u8 hour,u8 min,u8 sec,u8 ampm);			//RTC时间设置
ErrorStatus RTC_Set_Date(u8 year,u8 month,u8 date,u8 week); 		//RTC日期设置
void RTC_Set_AlarmA(u8 week,u8 hour,u8 min,u8 sec);		//设置闹钟时间(按星期闹铃,24小时制)
void RTC_Set_WakeUp(u32 wksel,u16 cnt);					//周期性唤醒定时器设置
int RTC_Get_Week(int year,int month,int day);   ////获得现在是星期几
bool RTC_Compare_Alarm(struct Alarm clock1,struct Alarm clock2);//比较两个闹钟的先后
void RTC_Swap_Alarm(int i,int j);//交换两个闹钟的内容
void RTC_Sort_Alarms(void);//给所有闹钟排序
void RTC_Clear_UsedAlarm(void);//清除已使用的闹钟
void RTC_Print_Alarms(void);//输出当前所有闹钟
bool RTC_isExist_Alarm(RTC_TimeTypeDef RTC_Time,u8 aweek);//判断当前闹钟是否已存在

#endif
