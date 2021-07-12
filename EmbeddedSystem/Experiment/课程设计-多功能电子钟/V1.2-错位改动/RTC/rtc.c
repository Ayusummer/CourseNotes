#include "rtc.h"
#include "delay.h"
#include "usart.h" 
#include "stdbool.h"

//一个存储各个闹钟信息的结构体数组
//声明参见rtc.h文件
struct Alarm alarms[100];

//比较两个闹钟谁先执行
bool RTC_Compare_Alarm(struct Alarm alarm1,struct Alarm alarm2){
	
	//预备1,假设都在当天,分别是否已经经过这个时刻了
	bool is_pass1=false,is_pass2=false;
	if((alarm1.hour<hour)
		|| (alarm1.hour==hour && alarm1.minute<minute) 
		|| (alarm1.hour==hour && alarm1.minute==minute && alarm1.second<second))
	   is_pass1=true;
	if((alarm2.hour<hour)
		|| (alarm2.hour==hour && alarm2.minute<minute) 
		|| (alarm2.hour==hour && alarm2.minute==minute && alarm2.second<second))
	   is_pass2=true;
	
	//预备2,假设在同一天,谁的时间小
	bool is_samll=false;
	if(   (alarm1.hour<alarm2.hour)
	   || (alarm1.hour==alarm2.hour && alarm1.minute<alarm2.minute) 
	   || (alarm1.hour==alarm2.hour && alarm1.minute==alarm2.minute && alarm1.second<alarm2.second))
	   is_samll=true;
	
	//分析它们与这一天相隔几天
	int Dw1=(alarm1.week-week+7)%7;
	int Dw2=(alarm2.week-week+7)%7;
	
	//通过天数判断
	//它们不在同一天的情况
	if(Dw1!=Dw2){
		
		  //都不在今天
			if(Dw1*Dw2!=0 && Dw1<Dw2) return true;
		
		  //有一个在今天
		  //如果这个时间刚过,那么它就是更晚的
		  //如果这个时间还没过,那么他就是更早的
			if(Dw1*Dw2==0){
				 if(Dw1==0){
					 if(is_pass1)  return false;
				   else if(!is_pass1)return true;
				 }
				 if(Dw2==0){
					 if(is_pass2)  return true;
				 else if(!is_pass2) return false;
				 }
			 }
	}
	
	//在同一天
	if(Dw1==Dw2){
		
		  //都在今天,直接分别判断hour, minute, second即可
		  //如果一个过了一个没过,那么没过的那个肯定更早
		  if(Dw1==0){
					if(is_pass1 && !is_pass2) return false;
					if(!is_pass1 && is_pass2) return true;
			}
			
			//都过了或者都没过,直接判断即可
			if(is_samll) return true;
			else return false;
	 }
	
	 return false;
}

//交换两个闹钟的内容
void RTC_Swap_Alarm(int i,int j){
	
	int tempw,temph,tempm,temps;
	tempw=alarms[i].week;
	alarms[i].week=alarms[j].week;
	alarms[j].week=tempw;
	
	temph=alarms[i].hour;
	alarms[i].hour=alarms[j].hour;
	alarms[j].hour=temph;
	
	tempm=alarms[i].minute;
	alarms[i].minute=alarms[j].minute;
	alarms[j].minute=tempm;
	
	temps=alarms[i].second;
	alarms[i].second=alarms[j].second;
	alarms[j].second=temps;

}

//给所有闹钟排序
void RTC_Sort_Alarms(void){
	
	for(int i=0;i<cnt-1;i++)
	   for(int j=i+1;j<cnt;j++)
	       if(!RTC_Compare_Alarm(alarms[i],alarms[j]))
	            RTC_Swap_Alarm(i,j);

}

//清除已使用的闹钟
//当最早的一个闹钟用了过后,后面的需要依次补上来
//记得个数-1
void RTC_Clear_UsedAlarm(void){
	
	for(int i=1;i<cnt;i++){
		 alarms[i-1].week=alarms[i].week;
		 alarms[i-1].hour=alarms[i].hour;
		 alarms[i-1].minute=alarms[i].minute;
		 alarms[i-1].second=alarms[i].second;
	}
  cnt--;
}

//对所有闹钟的一个打印输出,便于实验观察
void RTC_Print_Alarms(void){
	
	printf("当前所有闹钟如下：\n");
	for(int i=0;i<cnt;i++)
	    printf("%d-%02d:%02d:%02d\n",alarms[i].week,alarms[i].hour,alarms[i].minute,alarms[i].second);
	
}

//判断当前闹钟是否已经存在
bool RTC_isExist_Alarm(RTC_TimeTypeDef RTC_Time,u8 aweek){
	
	for(int i=0;i<cnt;i++)
	   if(  alarms[i].week==aweek && alarms[i].hour==RTC_Time.RTC_Hours 
			 && alarms[i].minute==RTC_Time.RTC_Minutes && alarms[i].second==RTC_Time.RTC_Seconds){
				 printf("\n当前闹钟已经存在!\n");
				 RTC_Print_Alarms();
		     return true;
			 }
	
	return false;

}


NVIC_InitTypeDef   NVIC_InitStructure;


//获得现在是星期几(0~6)
int RTC_Get_Week(int year,int month,int day)
{	
	year+=2000;
	//把一月和二月看成是上一年的十三月和十四月
	if(month==1||month==2) {
        month+=12;
        year--;
  }
	//基姆拉尔森计算公式
	return (day+2*month+3*(month+1)/5+year+year/4-year/100+year/400+1)%7;
}


//设置时间
ErrorStatus RTC_Set_Time(u8 hour,u8 min,u8 sec,u8 ampm)
{
	
	RTC_TimeTypeDef RTC_TimeTypeInitStructure;	
	RTC_TimeTypeInitStructure.RTC_Hours=hour;
	RTC_TimeTypeInitStructure.RTC_Minutes=min;
	RTC_TimeTypeInitStructure.RTC_Seconds=sec;
	RTC_TimeTypeInitStructure.RTC_H12=ampm;
	return RTC_SetTime(RTC_Format_BIN,&RTC_TimeTypeInitStructure);
}

//设置日期
ErrorStatus RTC_Set_Date(u8 year,u8 month,u8 date,u8 week)
{
	
	RTC_DateTypeDef RTC_DateTypeInitStructure;
	RTC_DateTypeInitStructure.RTC_Date=date;
	RTC_DateTypeInitStructure.RTC_Month=month;
	RTC_DateTypeInitStructure.RTC_WeekDay=week;
	RTC_DateTypeInitStructure.RTC_Year=year;
	return RTC_SetDate(RTC_Format_BIN,&RTC_DateTypeInitStructure);
}

//RTC初始化
//返回值:0,初始化成功;
//       1,LSE开启失败;
//       2,进入初始化模式失败;
u8 My_RTC_Init(void)
{

	RTC_InitTypeDef RTC_InitStructure;
	u16 retry=0X1FFF;
	
	//配置流程结合一般步骤和原理图
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//1、使能PWR时钟
	PWR_BackupAccessCmd(ENABLE);	//2、使能后备寄存器访问
	
	if(RTC_ReadBackupRegister(RTC_BKP_DR0)!=0x1003)		//是否第一次配置?
	{
		RCC_LSEConfig(RCC_LSE_ON);//3、LSE 开启
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)	//检查指定的RCC标志位设置与否,等待低速晶振就绪(等待稳定)
		{
			retry++;
			delay_ms(10);
		}
		if(retry==0) return 1;		//LSE 开启失败. 
			
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//3、设置RTC时钟(RTCCLK),选择LSE作为RTC时钟
		RCC_RTCCLKCmd(ENABLE);	//3、使能RTC时钟

		//使用LSE,经过异步、同步默认分频,得到1HZ,周期是1s
    RTC_InitStructure.RTC_AsynchPrediv = 0x7F;//RTC异步分频系数(1~0X7F),这里默认0x7F,即为127+1
    RTC_InitStructure.RTC_SynchPrediv  = 0xFF;//RTC同步分频系数(0~7FFF),这里默认0xFF,即为255+1
    RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;//RTC设置为,24小时格式
    RTC_Init(&RTC_InitStructure);//4、RTC初始化

		
		//5、6分别设置时间和日期
		//注意年份只能两位,参见日期寄存器
		RTC_Set_Time(19,42,0,RTC_H12_AM);
		RTC_Set_Date(21,7,1,4);
	 
		//标记已经初始化过了
		RTC_WriteBackupRegister(RTC_BKP_DR0,0x1003);
	} 
	return 0;
}
//设置闹钟时间(按星期闹铃,24小时制)
//week:星期几(0~6) @ref  RTC_Alarm_Definitions
//hour,min,sec:小时,分钟,秒钟
void RTC_Set_AlarmA(u8 week,u8 hour,u8 min,u8 sec)
{ 
	EXTI_InitTypeDef   EXTI_InitStructure;
	RTC_AlarmTypeDef RTC_AlarmTypeInitStructure;
	RTC_TimeTypeDef RTC_TimeTypeInitStructure;
	
	RTC_AlarmCmd(RTC_Alarm_A,DISABLE);//关闭闹钟A 
	
  RTC_TimeTypeInitStructure.RTC_Hours=hour;//小时
	RTC_TimeTypeInitStructure.RTC_Minutes=min;//分钟
	RTC_TimeTypeInitStructure.RTC_Seconds=sec;//秒
	RTC_TimeTypeInitStructure.RTC_H12=RTC_H12_AM;
  
	RTC_AlarmTypeInitStructure.RTC_AlarmDateWeekDay=week;//星期
	RTC_AlarmTypeInitStructure.RTC_AlarmDateWeekDaySel=RTC_AlarmDateWeekDaySel_WeekDay;//按星期闹
	RTC_AlarmTypeInitStructure.RTC_AlarmMask=RTC_AlarmMask_None;//精确匹配星期，时分秒
	RTC_AlarmTypeInitStructure.RTC_AlarmTime=RTC_TimeTypeInitStructure;
  RTC_SetAlarm(RTC_Format_BIN,RTC_Alarm_A,&RTC_AlarmTypeInitStructure);//闹钟初始化
 
	RTC_ClearITPendingBit(RTC_IT_ALRA);//清除RTC闹钟A的标志
  EXTI_ClearITPendingBit(EXTI_Line17);//清除LINE17上的中断标志位 
	
	RTC_ITConfig(RTC_IT_ALRA,ENABLE);//开启闹钟A中断
	RTC_AlarmCmd(RTC_Alarm_A,ENABLE);//开启闹钟A
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line17;//LINE17
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE17
  EXTI_Init(&EXTI_InitStructure);//配置

	NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
}
//cnt:自动重装载值.减到0,产生中断.
void RTC_Set_WakeUp(u32 wksel,u16 cnt)
{ 
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	RTC_WakeUpCmd(DISABLE);//关闭WAKE UP
	
	RTC_WakeUpClockConfig(wksel);//唤醒时钟选择
	
	RTC_SetWakeUpCounter(cnt);//设置WAKE UP自动重装载寄存器
	
	
	RTC_ClearITPendingBit(RTC_IT_WUT); //清除RTC WAKE UP的标志
  EXTI_ClearITPendingBit(EXTI_Line22);//清除LINE22上的中断标志位 
	 
	RTC_ITConfig(RTC_IT_WUT,ENABLE);//开启WAKE UP 定时器中断
	RTC_WakeUpCmd( ENABLE);//开启WAKE UP 定时器　
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line22;//LINE22
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE22
  EXTI_Init(&EXTI_InitStructure);//配置
 
 
	NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
}
//RTC闹钟中断服务函数
void RTC_Alarm_IRQHandler(void)
{
	if(RTC_GetFlagStatus(RTC_FLAG_ALRAF)==SET)//ALARM中断
	{
		//清除中断标志
		RTC_ClearFlag(RTC_FLAG_ALRAF);
		//更改闹钟标志
		flag=1;
		//输出提示信息
		printf("\nALARM!\r\n");
		//清除当前闹钟
		RTC_Clear_UsedAlarm();
		//设置下一个闹钟
		RTC_Set_AlarmA(alarms[0].week,alarms[0].hour,alarms[0].minute,alarms[0].second);
		//打印输出后面所有闹钟的信息
		RTC_Print_Alarms();
		
	}   
	EXTI_ClearITPendingBit(EXTI_Line17);	//清除中断线17的中断标志 											 
}
//RTC WAKE UP中断服务函数
void RTC_WKUP_IRQHandler(void)
{    
	if(RTC_GetFlagStatus(RTC_FLAG_WUTF)==SET)//WK_UP中断
	{ 
		RTC_ClearFlag(RTC_FLAG_WUTF);	//清除中断标志

	}   
	EXTI_ClearITPendingBit(EXTI_Line22);//清除中断线22的中断标志 								
}
