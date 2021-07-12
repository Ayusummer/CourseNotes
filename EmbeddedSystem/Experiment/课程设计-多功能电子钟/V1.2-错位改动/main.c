#include "sys.h"
#include "delay.h"	
#include "usart.h"
#include "lcd.h"
#include "rtc.h"
#include "exti.h"
#include "key.h"
#include "beep.h"
#include "adc.h"
#include "math.h"
#include "led.h"

// 钟表表盘相关参数
int X_cicle=240,Y_cicle=300,Radius=150;

// 星期数组
char *weeks[]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// 存储提示信息的序号
// 避免不必要的更新
int choice=0;
int oldchoice=0;

// 存储这一次各个指针针尖的位置, 方便下一次清除
int hourx, houry;
int minutex, minutey;
int secondx, secondy;

//存储上一次秒钟、星期, 避免不必要的更新
int oldsecond=60;
int oldweek=7;

/* 屏幕尺寸 800*480
	屏幕尺寸 800*480
	在表盘的中心画出一个实心圆 */
void LCD_Draw_ALLCircle(u16 x0,u16 y0,u8 radius,u16 color){
	int a,b;
	int di;
	a=0;b=radius;
	di=3-(radius<<1);
	while(a<=b)	{
		int i = a,p = b;
		while(i>0){
			LCD_Fast_DrawPoint(x0+b,y0-i,color);
			LCD_Fast_DrawPoint(x0-i,y0+b,color);
			i--;
	  }
		while(p>0){		
			LCD_Fast_DrawPoint(x0-a,y0-p,color);
			LCD_Fast_DrawPoint(x0-p,y0-a,color);
			LCD_Fast_DrawPoint(x0+a,y0-p,color);
			LCD_Fast_DrawPoint(x0-p,y0+a,color);
			LCD_Fast_DrawPoint(x0+a,y0+p,color);
			LCD_Fast_DrawPoint(x0+p,y0+a,color);
			p--;
	  }
		a++;
		//Bresenham算法画圆
		if(di<0) di+=4*a+6;
		else{
			di+=10+4*(a-b);
			b--;
		} 								
	}
	
	LCD_Fast_DrawPoint(x0,y0,color);
}




//画出钟表的各个刻度
void Display_Scale(u16 X_cicle,u16 Y_cicle, u8 radius){
		//画出外圆
	  POINT_COLOR=CYAN;
		LCD_Draw_Circle(X_cicle, Y_cicle, radius);
		//画指针中心圆点
		LCD_Draw_ALLCircle(X_cicle, Y_cicle, 2, 0xF800);
		//画出刻度
	  POINT_COLOR=BLACK;
		static int x1=0, x2=0, y1=0, y2=0, angle=0;
		float scale;
		for(int i=0;i<60;i++)	{
				angle = i*6;//角度
				scale = angle/180.0*3.1415926;//弧度

			  	//指针外圆
				x1 = 150*sin(scale) + X_cicle;
				y1 = -150*cos(scale) + Y_cicle;
			  
			  	//特殊刻度
				if(i%5==0){
					//指针内圆
					x2 = 135*sin(scale) + X_cicle;
					y2 = -135*cos(scale) + Y_cicle;
					
					//作出刻度线
					POINT_COLOR=BLACK;
					if(i==15 || i==45){
						LCD_DrawLine(x1,y1-1,x2,y2-1);
						LCD_DrawLine(x1,y1,x2,y2);
						LCD_DrawLine(x1,y1+1,x2,y2+1);
					}
					else{
						LCD_DrawLine(x1-1,y1,x2-1,y2);
						LCD_DrawLine(x1,y1,x2,y2);
						LCD_DrawLine(x1+1,y1,x2+1,y2);
					}
				}
				else {
					 //指针内圆
					 x2 = 142*sin(scale) + X_cicle;
					 y2 = -142*cos(scale) + Y_cicle;
					
					 //作出刻度线
					 POINT_COLOR=GRAY;
					 LCD_DrawLine(x1,y1,x2,y2);
				}			 
		}
}

//画出、更新各个指针的位置
void DrawPointers(int hour,int minute,int second){
		POINT_COLOR=GRAY;
	  	//每个指针当前的针尖位置坐标
		int hx,hy,mx,my,sx,sy;

	  	//每个指针的角度、弧度
		float angleh, anglem, angles;
		float radian;
	  
	  	if(oldsecond==second) return;

		angleh = ( hour%12 )*30 + minute*0.5;
		radian = (angleh/180.0)*3.1415926;
		hx = 60*sin(radian) + X_cicle;
		hy = -60*cos(radian) + Y_cicle;
		POINT_COLOR=WHITE;
		LCD_DrawLine(X_cicle,Y_cicle,hourx,houry);
		hourx=hx;houry=hy;
		POINT_COLOR=BLUE;
		LCD_DrawLine(X_cicle,Y_cicle,hx,hy);

		anglem = minute*6 + second*0.1;
		radian = (anglem/180.0)*3.1415926;
		mx = 90*sin(radian) + X_cicle;
		my = -90*cos(radian) + Y_cicle; 
		POINT_COLOR=WHITE;
		LCD_DrawLine(X_cicle,Y_cicle,minutex,minutey);
		minutex=mx;minutey=my;
		POINT_COLOR=BLACK;
		LCD_DrawLine(X_cicle,Y_cicle,mx,my);

		angles = second*6;
		radian = (angles/180.0)*3.1415926;
		sx = 120*sin(radian) + X_cicle;
		sy = -120*cos(radian) + Y_cicle; 
		POINT_COLOR=WHITE;
		LCD_DrawLine(X_cicle,Y_cicle,secondx,secondy);
		secondx=sx;secondy=sy;
		POINT_COLOR=RED;
		LCD_DrawLine(X_cicle,Y_cicle,sx,sy);
		
		//避免秒针重合而漂白
		if(angles >= angleh) {
			POINT_COLOR=BLUE;
			LCD_DrawLine(X_cicle,Y_cicle,hourx,houry);
		}
		
		if(angles >= anglem) {
			POINT_COLOR=BLACK;
			LCD_DrawLine(X_cicle,Y_cicle,minutex,minutey);
		}
		
		//画指针中心圆点
		LCD_Draw_ALLCircle(X_cicle, Y_cicle, 2, 0xF800);
		
		//更新秒钟
		oldsecond=second;
}

//显示温度
void temperatureShow(){
		int temp=Get_Temprate();	//得到温度值
		if(temp<0){
			temp=-temp;
			//LCD_ShowString(140+10*12,565,16,24,24,"-");			//显示负号
			LCD_ShowString(250+10*12,510,16,24,24,"-");			//显示负号
		}
		else LCD_ShowString(250+10*12,510,16,24,24," ");	//无符号
		
		LCD_ShowxNum(250+11*12,510,temp/100,2,24,0);		//显示整数部分
		LCD_ShowxNum(250+14*12,510,temp%100,2,24,0);		//显示小数部分
}

//主界面显示
void mainInterfaceInit(){
	
	//画出电子钟盘
	Display_Scale(X_cicle, Y_cicle, Radius);

	//取个标题
	POINT_COLOR=RED;
	LCD_ShowString(210,50,100,24,24,"CLOCK");

	
	//固定温度显示的位置
	POINT_COLOR=RED;
	LCD_ShowString(250,510,250,24,24,"TEMPERATE: 00.00C");

  //加上提示信息
	POINT_COLOR=BLUE;
	LCD_ShowString(20,540,600,16,24, "Tips: Set AlarmClock :axx:xx:xxwx");
	LCD_ShowString(20,570,600,16,24, "      Set hour :hxx");
	LCD_ShowString(20,600,600,16,24, "      Set minute :mxx");
	LCD_ShowString(20,630,600,16,24, "      Set second :sxx");
	LCD_ShowString(20,660,600,16,24, "      Set time :txx:xx:xx");
	LCD_ShowString(20,690,600,16,24, "      Set date :dxx-xx-xx");
}

int main(void){ 
	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;
	
	u8 tbuf[40];
	u8 t=0;
	// 设置系统中断优先级分组2
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
	delay_init(168);	// 初始化延时函数
	uart_init(115200);	// 初始化串口波特率为 115200
 	LCD_Init();			// 初始化 LCD
	My_RTC_Init();		// 初始化 RTC
	EXTIX_Init();		// 初始化外部中断输入 
	LED_Init();         // 初始化 LED
	BEEP_Init();        // 初始化蜂鸣器
	Adc_Init();			// 内部温度传感器 ADC 初始化

	// 配置WAKE UP中断,1秒钟中断一次
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		
	
	// 显示主页面(即不需要更新的内容)
	mainInterfaceInit();
	
	// 下面电子钟进行循环不断地运转
	POINT_COLOR=BLACK;
	while(1) {
		t++;
		//每25ms更新一次显示数据
		if( t%5==0 ) {
			//分别获取时间和日期
			RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
			RTC_GetDate(RTC_Format_BIN,&RTC_DateStruct);
			
			//更新时间
			POINT_COLOR=BLUE;
			sprintf((char*)tbuf,"TIME: %02d:%02d:%02d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds); 
			LCD_ShowString(30,480,210,24,24,tbuf);
			
			//更新日期
			POINT_COLOR=RED;
			sprintf((char*)tbuf,"DATE: 20%02d-%02d-%02d",RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date); 
			LCD_ShowString(250,480,210,24,24,tbuf);
			
			POINT_COLOR=CYAN;
			hour=RTC_TimeStruct.RTC_Hours;
			minute=RTC_TimeStruct.RTC_Minutes;
			second=RTC_TimeStruct.RTC_Seconds;
			year=RTC_DateStruct.RTC_Year;
			month=RTC_DateStruct.RTC_Month;
			day=RTC_DateStruct.RTC_Date;
			week=RTC_DateStruct.RTC_WeekDay;
			
			// 整点报时,持续10秒
			if(minute==0&&second==0) flag=1;
				else if(minute==0&&second==5) flag=0;
			if(flag && (t%20==0)) {
					BEEP=!BEEP;
					LED0=!LED0;
			}
		
			/* 对于按键校时间、校日期的提示信息, 且避免不必要的更新 */
			if(oldchoice!=choice){
					switch(choice){
						case 0:LCD_Fill(30,460,230,479,WHITE);LCD_ShowString(30,460,200,16,16,"Close alarm clock");break;
						case 1:LCD_Fill(30,460,230,479,WHITE);LCD_ShowString(30,460,200,16,16,"Correct hours");break;
						case 2:LCD_Fill(30,460,230,479,WHITE);LCD_ShowString(30,460,200,16,16,"Correct minute");break;
						case 3:LCD_Fill(30,460,230,479,WHITE);LCD_ShowString(30,460,200,16,16,"Correct second");break;
						case 4:LCD_Fill(30,460,230,479,WHITE);LCD_ShowString(30,460,200,16,16,"Correct year");break;
						case 5:LCD_Fill(30,460,230,479,WHITE);LCD_ShowString(30,460,200,16,16,"Correct month");break;
						case 6:LCD_Fill(30,460,230,479,WHITE);LCD_ShowString(30,460,200,16,16,"Correct day");break;
				}
				oldchoice=choice;
		  }
		
			// 显示星期几
			// 且避免不必要的更新
			if(week!=oldweek){
					POINT_COLOR=BLUE;
				  	// 首先先清除原本显示区域
					// LCD_Fill(210,535,410,560,WHITE);
					// LCD_ShowString(210,535,200,24,24,weeks[week]);
					LCD_Fill(100,510,250,540,WHITE);
					LCD_ShowString(100,510,150,24,24,weeks[week]);
					oldweek=week;
			}
	  }

	  //更新表盘的指针
	  DrawPointers(hour, minute, second);
	 
	  //更新温度显示
		POINT_COLOR=RED;
	    temperatureShow();
		
		delay_ms(5);
	}	
}
