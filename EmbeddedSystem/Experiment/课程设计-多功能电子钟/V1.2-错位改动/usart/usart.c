#include "sys.h"
#include "usart.h"
#include "led.h"
#include "string.h"
#include "lcd.h"
#include "rtc.h"

////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误
u8 USART_RX_str[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	

//初始化IO 串口1 
//bound:波特率
void uart_init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

#endif
	
}

//存储校准信息hxx mxx sxx
char str[20];

//存储校准信息txx:xx:xx dxx-xx-xx
char strtd[20];

//存储输入的闹钟信息axx:xx:xxwx
char stra[20];

//存储当前输入字符个数
int i=0;

//存储新星期(校准日期用)
int aweek;

//存储日期参数(校准日期用)
int tempy,tempm,tempd;

//存储当前闹钟的个数
int cnt;

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;//存储当前收到的字符
	RTC_TimeTypeDef RTC_Time;
	RTC_DateTypeDef RTC_Date;
	
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		//读取接收到的数据
		Res =USART_ReceiveData(USART1);//(USART1->DR);
		
		if(i<3) str[i]=Res;//h12 m12 s12
		if(i<9) strtd[i]=Res;//t12:12:12 d12-12-12
		if(i<11) stra[i]=Res;//a12:12:12w5
		i++;
		if(i>3){
				for(int j=1;j<3;j++){
					str[j-1]=str[j];
				}
				str[2]=Res;
		}
		if(i>9){
				for(int j=1;j<9;j++){
					strtd[j-1]=strtd[j];
				}
				strtd[8]=Res;
		}
		if(i>11){
				for(int j=1;j<11;j++){
					stra[j-1]=stra[j];
				}
				stra[10]=Res;
		}
		
		//h12 m12 s12 单独设置时分秒
		if((str[0]=='h' || str[0]=='m' || str[0]=='s') && i>=3){
			RTC_GetTime(RTC_Format_BIN,&RTC_Time);//获取时间
		  RTC_GetDate(RTC_Format_BIN,&RTC_Date);//获取日期
			if(str[0]=='h')   RTC_Time.RTC_Hours=(str[1]-'0')*10+(str[2]-'0');
			if(str[0]=='m')   RTC_Time.RTC_Minutes=(str[1]-'0')*10+(str[2]-'0');
			if(str[0]=='s')   RTC_Time.RTC_Seconds=(str[1]-'0')*10+(str[2]-'0');
			if(RTC_Time.RTC_Hours<24 && RTC_Time.RTC_Minutes<60 && RTC_Time.RTC_Seconds<60){
				RTC_Set_Time(RTC_Time.RTC_Hours,RTC_Time.RTC_Minutes,RTC_Time.RTC_Seconds,RTC_H12_AM);
				RTC_Set_Date(RTC_Date.RTC_Year,RTC_Date.RTC_Month,RTC_Date.RTC_Date,RTC_Date.RTC_WeekDay);
			}
		}
		
		//t12:12:12 设置时间
		if(strtd[0]=='t' && strtd[3]==':' && strtd[6]==':' && i>=9){
			RTC_GetTime(RTC_Format_BIN,&RTC_Time);//获取时间
		  RTC_GetDate(RTC_Format_BIN,&RTC_Date);//获取日期
			RTC_Time.RTC_Hours=(strtd[1]-'0')*10+(strtd[2]-'0');
			RTC_Time.RTC_Minutes=(strtd[4]-'0')*10+(strtd[5]-'0');
			RTC_Time.RTC_Seconds=(strtd[7]-'0')*10+(strtd[8]-'0');
			//判断时间是否合法
			if(RTC_Time.RTC_Hours<24 && RTC_Time.RTC_Minutes<60 && RTC_Time.RTC_Seconds<60){
				  //获取更新后的星期
					RTC_Date.RTC_WeekDay=RTC_Get_Week(RTC_Date.RTC_Year,RTC_Date.RTC_Month,RTC_Date.RTC_Date);
					RTC_Set_Time(RTC_Time.RTC_Hours,RTC_Time.RTC_Minutes,RTC_Time.RTC_Seconds,RTC_H12_AM);
					RTC_Set_Date(RTC_Date.RTC_Year,RTC_Date.RTC_Month,RTC_Date.RTC_Date,RTC_Date.RTC_WeekDay);
			}
		}
		
		//d12-12-12 设置日期
		if(strtd[0]=='d' && strtd[3]=='-' && strtd[6]=='-' && i>=9){
			RTC_GetTime(RTC_Format_BIN,&RTC_Time);//获取时间
		  RTC_GetDate(RTC_Format_BIN,&RTC_Date);//获取日期
			RTC_Date.RTC_Year=(strtd[1]-'0')*10+(strtd[2]-'0');
			RTC_Date.RTC_Month=(strtd[4]-'0')*10+(strtd[5]-'0');
			RTC_Date.RTC_Date=(strtd[7]-'0')*10+(strtd[8]-'0');
			//普遍判断日期是否合法
			if(RTC_Date.RTC_Year<=99 && RTC_Date.RTC_Month<=12 && RTC_Date.RTC_Date<=31){
				tempy=2000+RTC_Date.RTC_Year;
				tempm=RTC_Date.RTC_Month;
				tempd=RTC_Date.RTC_Date;
				//特殊判断日期是否合法
			  if(   (tempd<=28 && tempm==2 && !(((tempy%4==0) && (tempy%100!=0)) || tempy%400==0))//二月平年
					  ||(tempd<=29 && tempm==2 &&  (((tempy%4==0) && (tempy%100!=0)) || tempy%400==0))//二月闰年
					  ||(tempd<=30 && (tempm==4 || tempm==6 || tempm==9 || tempm==11))//小月
				    ||(tempd<=31 && (tempm==1 || tempm==3 || tempm==5 || tempm==7 || tempm==8 || tempm==10 || tempm==12)))//大月
				{
					  //获取更新后的星期
						RTC_Date.RTC_WeekDay=RTC_Get_Week(tempy%2000,tempm,tempd);
						RTC_Set_Time(RTC_Time.RTC_Hours,RTC_Time.RTC_Minutes,RTC_Time.RTC_Seconds,RTC_H12_AM);
						RTC_Set_Date(RTC_Date.RTC_Year,RTC_Date.RTC_Month,RTC_Date.RTC_Date,RTC_Date.RTC_WeekDay);
				}
			}
		}
		
		//a12:12:12w5 设置闹钟
		if(stra[0]=='a' && stra[3]==':' && stra[6]==':' && stra[9]=='w' && i>=11){
			RTC_Time.RTC_Hours=(stra[1]-'0')*10+(stra[2]-'0');
			RTC_Time.RTC_Minutes=(stra[4]-'0')*10+(stra[5]-'0');
			RTC_Time.RTC_Seconds=(stra[7]-'0')*10+(stra[8]-'0');
			aweek=stra[10]-'0';
			if(RTC_Time.RTC_Hours<24 && RTC_Time.RTC_Minutes<60 && RTC_Time.RTC_Seconds<60 && aweek>=0 && aweek<=6){
				if(!RTC_isExist_Alarm(RTC_Time,aweek)){
					//存储闹钟信息
					alarms[cnt].hour=RTC_Time.RTC_Hours;
					alarms[cnt].minute=RTC_Time.RTC_Minutes;
					alarms[cnt].second=RTC_Time.RTC_Seconds;
					alarms[cnt].week=aweek;
					cnt++;
					//当有多个闹钟时进行排序
					if(cnt>1) RTC_Sort_Alarms();
					//所有闹钟里面最早的那个闹钟
					RTC_Set_AlarmA(alarms[0].week,alarms[0].hour,alarms[0].minute,alarms[0].second);
					printf("\n设置成功,闹钟%d时间为：%02d:%02d:%02dw%d\n",cnt-1,RTC_Time.RTC_Hours,RTC_Time.RTC_Minutes,RTC_Time.RTC_Seconds,aweek);
					RTC_Print_Alarms();
				}
			}
		}
	}
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
}
#endif	

 



