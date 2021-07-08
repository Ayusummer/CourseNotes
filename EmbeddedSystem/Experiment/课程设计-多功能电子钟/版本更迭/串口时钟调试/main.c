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

u8 set;
int sign;
int choice=0;
int th,tm,ts;
int dy,dm,dd;
int w;
int aw,ah,am,as;
int clocks[2];
int clockm[2];
int clockh[2];
int clockw[2];
int clock[2];
int x;
int main(void){ 
	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;
	char ch;
  	u8 lenth;
	long ic;
	int rth,rtm,sa;
	int drawh,drawm,draws;
	int p=0;	
	int ttt;
	int timing;
	int tttt;
	short temp; 
	u8 tbuf[40];
	u8 t=0;
	set=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
 	LCD_Init();					  //初始化LCD
	My_RTC_Init();		 		//初始化RTC
  	EXTIX_Init();       //初始化外部中断输入 
	BEEP_Init();
	Adc_Init();         //内部温度传感器ADC初始化
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		//配置WAKE UP中断,1秒钟中断一次
	BEEP=0;
	POINT_COLOR=BLACK;
	LCD_ShowString(30,740,600,16,16, "  Tips:    a--Set AlarmClock");	
	LCD_ShowString(30,760,600,16,16, "           h--Reset hour        m--Reset minute");	
	LCD_ShowString(30,780,600,16,16, "           t--Count down        c--Reset");
	POINT_COLOR=RED;
	LCD_ShowString(30,50,200,24,24,"LCD Clock");	
	LCD_ShowString(30,220,200,16,16,"TEMPERATE: 00.00C");//先在固定位置显示小数点	
	LCD_ShowString(280,120,100,16,24,"Timer");	
	LCD_ShowxNum(300,160,0,3,16,0);
  	while(1){		
		t++;
		//每100ms更新一次显示数据
		if((t%10)==0){
			RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);			
			sprintf((char*)tbuf,"Time:%02d:%02d:%02d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds); 
			LCD_ShowString(30,160,210,16,16,tbuf);													
			RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);			
			sprintf((char*)tbuf,"Date:20%02d-%02d-%02d",RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date); 
			LCD_ShowString(30,140,210,16,16,tbuf);	
			sprintf((char*)tbuf,"Week:%d",RTC_DateStruct.RTC_WeekDay); 
			LCD_ShowString(30,180,210,16,16,tbuf);		
			
			th=RTC_TimeStruct.RTC_Hours;
			tm=RTC_TimeStruct.RTC_Minutes;
			ts=RTC_TimeStruct.RTC_Seconds;
			dy=RTC_DateStruct.RTC_Year;
			dm=RTC_DateStruct.RTC_Month;
			dd=RTC_DateStruct.RTC_Date;
			w=RTC_DateStruct.RTC_WeekDay;		
			
			if(RTC_TimeStruct.RTC_Minutes==0&&RTC_TimeStruct.RTC_Seconds==0){sign=1;}
			if(RTC_TimeStruct.RTC_Minutes==0&&RTC_TimeStruct.RTC_Seconds==10){sign=10;}
			if(sign==1){BEEP=!BEEP;delay_ms(20);BEEP=!BEEP;}//整点报时	
		} 
						
		LCD_Fill(0,80,239,120,WHITE);//清除半屏    
		switch(choice){
			case 1:LCD_ShowString(30,100,210,16,16,"Time-Hour");break;
			case 2:LCD_ShowString(30,100,210,16,16,"Time-Minute");break;
			case 3:LCD_ShowString(30,100,210,16,16,"Date-Year");break;
			case 4:LCD_ShowString(30,100,210,16,16,"Date-Mounth");break;
			case 5:LCD_ShowString(30,100,210,16,16,"Date-Day");break;
			case 6:LCD_ShowString(30,100,210,16,16,"Week");break;
		}				
		if ((t % 18) == 0){
			LCD_Fill(140, 500, 340, 700, WHITE);
			LCD_Draw_Circle(240, 600, 100);
			LCD_Draw_Circle(240, 600, 1);
			LCD_DrawLine(240, 500, 240, 520);//12...
			LCD_ShowString(240,520,10,16,16,"12");
			LCD_DrawLine(240, 700, 240, 680);
			LCD_ShowString(240,680,5,16,16,"6");
			LCD_DrawLine(140, 600, 160, 600);
			LCD_ShowString(160,600,5,16,16,"9");
			LCD_DrawLine(340, 600, 320, 600);
			LCD_ShowString(320,600,5,16,16,"3");

			LCD_DrawLine(290, 687, 285, 678);//5...
			LCD_ShowString(275,670,5,16,16,"5");
			LCD_DrawLine(290, 513, 285, 522);//1...
			LCD_ShowString(285,522,5,16,16,"1");
			LCD_DrawLine(190, 687, 195, 678);//7...
			LCD_ShowString(190,670,5,16,16,"7");
			LCD_DrawLine(190, 513, 195, 522);//11..
			LCD_ShowString(195,522,10,16,16,"11");
			LCD_DrawLine(327, 650, 318, 645);//4...
			LCD_ShowString(310,640,5,16,16,"4");
			LCD_DrawLine(153, 550, 162, 555);//10..
			LCD_ShowString(162,555,10,16,16,"10");
			LCD_DrawLine(327, 550, 318, 555);//2...
			LCD_ShowString(318,555,5,16,16,"2");
			LCD_DrawLine(153, 650, 162, 645);//8...
			LCD_ShowString(162,640,5,16,16,"8");
			drawh = th;
			drawm=tm;
			draws=ts;
			if (drawh>11)drawh -= 12;
			switch (drawh){
			case 0:LCD_DrawLine(240, 600, 240, 560); break;
			case 1:LCD_DrawLine(240, 600, 260, 565); break;
			case 2:LCD_DrawLine(240, 600, 275, 580); break;
			case 3:LCD_DrawLine(240, 600, 280, 600); break;
			case 4:LCD_DrawLine(240, 600, 275, 620); break;
			case 5:LCD_DrawLine(240, 600, 260, 635); break;
			case 6:LCD_DrawLine(240, 600, 240, 640); break;
			case 7:LCD_DrawLine(240, 600, 220, 635); break;
			case 8:LCD_DrawLine(240, 600, 205, 620); break;
			case 9:LCD_DrawLine(240, 600, 200, 600); break;
			case 10:LCD_DrawLine(240, 600, 205, 580); break;
			case 11:LCD_DrawLine(240, 600, 220, 565); break;
			}
			
			switch (drawm){
			case 0:LCD_DrawLine(240, 600, 240, 540); break;
			case 1:LCD_DrawLine(240, 600, 246, 540); break;
			case 2:LCD_DrawLine(240, 600, 252, 541); break;
			case 3:LCD_DrawLine(240, 600, 258, 543); break;
			case 4:LCD_DrawLine(240, 600, 264, 545); break;
			case 5:LCD_DrawLine(240, 600, 270, 548); break;
			case 6:LCD_DrawLine(240, 600, 275, 551); break;
			case 7:LCD_DrawLine(240, 600, 280, 555); break;
			case 8:LCD_DrawLine(240, 600, 284, 560); break;
			case 9:LCD_DrawLine(240, 600, 288, 565); break;
			case 10:LCD_DrawLine(240, 600, 291, 570); break;
			case 11:LCD_DrawLine(240, 600, 294, 576); break;
			case 12:LCD_DrawLine(240, 600, 297, 581); break;
			case 13:LCD_DrawLine(240, 600, 298, 588); break;
			case 14:LCD_DrawLine(240, 600, 299, 594); break;
			case 15:LCD_DrawLine(240, 600, 300, 600); break;
			case 16:LCD_DrawLine(240, 600, 299, 606); break;
			case 17:LCD_DrawLine(240, 600, 298, 612); break;
			case 18:LCD_DrawLine(240, 600, 297, 619); break;
			case 19:LCD_DrawLine(240, 600, 294, 624); break;
			case 20:LCD_DrawLine(240, 600, 291, 630); break;
			case 21:LCD_DrawLine(240, 600, 288, 635); break;
			case 22:LCD_DrawLine(240, 600, 284, 640); break;
			case 23:LCD_DrawLine(240, 600, 280, 645); break;
			case 24:LCD_DrawLine(240, 600, 275, 649); break;
			case 25:LCD_DrawLine(240, 600, 270, 652); break;
			case 26:LCD_DrawLine(240, 600, 264, 655); break;
			case 27:LCD_DrawLine(240, 600, 258, 657); break;
			case 28:LCD_DrawLine(240, 600, 252, 659); break;
			case 29:LCD_DrawLine(240, 600, 246, 660); break;
			case 30:LCD_DrawLine(240, 600, 240, 660); break;
			case 31:LCD_DrawLine(240, 600, 234, 660); break;
			case 32:LCD_DrawLine(240, 600, 228, 659); break;
			case 33:LCD_DrawLine(240, 600, 222, 657); break;
			case 34:LCD_DrawLine(240, 600, 216, 655); break;
			case 35:LCD_DrawLine(240, 600, 210, 652); break;
			case 36:LCD_DrawLine(240, 600, 205, 649); break;
			case 37:LCD_DrawLine(240, 600, 200, 645); break;
			case 38:LCD_DrawLine(240, 600, 196, 640); break;
			case 39:LCD_DrawLine(240, 600, 192, 635); break;
			case 40:LCD_DrawLine(240, 600, 189, 630); break;
			case 41:LCD_DrawLine(240, 600, 186, 624); break;
			case 42:LCD_DrawLine(240, 600, 183, 619); break;
			case 43:LCD_DrawLine(240, 600, 182, 612); break;
			case 44:LCD_DrawLine(240, 600, 181, 606); break;
			case 45:LCD_DrawLine(240, 600, 180, 600); break;
			case 46:LCD_DrawLine(240, 600, 181, 594); break;
			case 47:LCD_DrawLine(240, 600, 182, 588); break;
			case 48:LCD_DrawLine(240, 600, 183, 581); break;
			case 49:LCD_DrawLine(240, 600, 186, 576); break;
			case 50:LCD_DrawLine(240, 600, 189, 570); break;
			case 51:LCD_DrawLine(240, 600, 192, 565); break;
			case 52:LCD_DrawLine(240, 600, 196, 560); break;
			case 53:LCD_DrawLine(240, 600, 200, 555); break;
			case 54:LCD_DrawLine(240, 600, 205, 551); break;
			case 55:LCD_DrawLine(240, 600, 210, 548); break;
			case 56:LCD_DrawLine(240, 600, 216, 545); break;
			case 57:LCD_DrawLine(240, 600, 222, 543); break;
			case 58:LCD_DrawLine(240, 600, 228, 541); break;
			case 59:LCD_DrawLine(240, 600, 234, 540); break;
			}			
			switch (draws){
			case 0:LCD_DrawLine(240, 600, 240, 540); break;
			case 1:LCD_DrawLine(240, 600, 246, 540); break;
			case 2:LCD_DrawLine(240, 600, 252, 541); break;
			case 3:LCD_DrawLine(240, 600, 258, 543); break;
			case 4:LCD_DrawLine(240, 600, 264, 545); break;
			case 5:LCD_DrawLine(240, 600, 270, 548); break;
			case 6:LCD_DrawLine(240, 600, 275, 551); break;
			case 7:LCD_DrawLine(240, 600, 280, 555); break;
			case 8:LCD_DrawLine(240, 600, 284, 560); break;
			case 9:LCD_DrawLine(240, 600, 288, 565); break;
			case 10:LCD_DrawLine(240, 600, 291, 570); break;
			case 11:LCD_DrawLine(240, 600, 294, 576); break;
			case 12:LCD_DrawLine(240, 600, 297, 581); break;
			case 13:LCD_DrawLine(240, 600, 298, 588); break;
			case 14:LCD_DrawLine(240, 600, 299, 594); break;
			case 15:LCD_DrawLine(240, 600, 300, 600); break;
			case 16:LCD_DrawLine(240, 600, 299, 606); break;
			case 17:LCD_DrawLine(240, 600, 298, 612); break;
			case 18:LCD_DrawLine(240, 600, 297, 619); break;
			case 19:LCD_DrawLine(240, 600, 294, 624); break;
			case 20:LCD_DrawLine(240, 600, 291, 630); break;
			case 21:LCD_DrawLine(240, 600, 288, 635); break;
			case 22:LCD_DrawLine(240, 600, 284, 640); break;
			case 23:LCD_DrawLine(240, 600, 280, 645); break;
			case 24:LCD_DrawLine(240, 600, 275, 649); break;
			case 25:LCD_DrawLine(240, 600, 270, 652); break;
			case 26:LCD_DrawLine(240, 600, 264, 655); break;
			case 27:LCD_DrawLine(240, 600, 258, 657); break;
			case 28:LCD_DrawLine(240, 600, 252, 659); break;
			case 29:LCD_DrawLine(240, 600, 246, 660); break;
			case 30:LCD_DrawLine(240, 600, 240, 660); break;
			case 31:LCD_DrawLine(240, 600, 234, 660); break;
			case 32:LCD_DrawLine(240, 600, 228, 659); break;
			case 33:LCD_DrawLine(240, 600, 222, 657); break;
			case 34:LCD_DrawLine(240, 600, 216, 655); break;
			case 35:LCD_DrawLine(240, 600, 210, 652); break;
			case 36:LCD_DrawLine(240, 600, 205, 649); break;
			case 37:LCD_DrawLine(240, 600, 200, 645); break;
			case 38:LCD_DrawLine(240, 600, 196, 640); break;
			case 39:LCD_DrawLine(240, 600, 192, 635); break;
			case 40:LCD_DrawLine(240, 600, 189, 630); break;
			case 41:LCD_DrawLine(240, 600, 186, 624); break;
			case 42:LCD_DrawLine(240, 600, 183, 619); break;
			case 43:LCD_DrawLine(240, 600, 182, 612); break;
			case 44:LCD_DrawLine(240, 600, 181, 606); break;
			case 45:LCD_DrawLine(240, 600, 180, 600); break;
			case 46:LCD_DrawLine(240, 600, 181, 594); break;
			case 47:LCD_DrawLine(240, 600, 182, 588); break;
			case 48:LCD_DrawLine(240, 600, 183, 581); break;
			case 49:LCD_DrawLine(240, 600, 186, 576); break;
			case 50:LCD_DrawLine(240, 600, 189, 570); break;
			case 51:LCD_DrawLine(240, 600, 192, 565); break;
			case 52:LCD_DrawLine(240, 600, 196, 560); break;
			case 53:LCD_DrawLine(240, 600, 200, 555); break;
			case 54:LCD_DrawLine(240, 600, 205, 551); break;
			case 55:LCD_DrawLine(240, 600, 210, 548); break;
			case 56:LCD_DrawLine(240, 600, 216, 545); break;
			case 57:LCD_DrawLine(240, 600, 222, 543); break;
			case 58:LCD_DrawLine(240, 600, 228, 541); break;
			case 59:LCD_DrawLine(240, 600, 234, 540); break;
			}			
		}	
		if(USART_RX_STA&0x8000)
		{
			lenth=USART_RX_STA&0x3fff;
			ch=USART_RX_BUF[lenth-1];
			USART_SendData(USART1,USART_RX_BUF[lenth-1]);				
			switch(ch){
				case 'h':rth=3;printf("\r\nAdjustment hour:");break;
				case 'm':rtm=3;printf("\r\nAdjustment minute:");break;
				case 'a':sa=8;printf("\r\nSet AlarmClock:");break;
				case 't':ttt=3;tttt=0;timing=0;printf("\r\nSet Timing:");break;
			}			
			ic=(int)(ch-'0');
			if(rth==3){th=-56;}
			if(rth==2){th+=ic*10;}
			if(rth==1){th+=ic;printf("\r\n");}
			if(rtm==3){tm=-96;}
			if(rtm==2){tm+=ic*10;}
			if(rtm==1){tm+=ic;printf("\r\n");}
			RTC_Set_Time(th,tm,ts,RTC_H12_AM);		
			switch(sa){
				case 8://LCD_Fill(0,240,239,800,WHITE);
				LCD_ShowString(30,260+p*20,100,16,16,"Alarm:");
				break;
				case 7:aw=ic-96;ah=0;am=-96;as=-96;
				LCD_ShowxNum(82,260+p*20,aw,2,16,0);
				LCD_ShowString(98,260+p*20,16,16,16,"-");
				break;				
				case 6:ah+=ic*10;break;
				case 5:ah+=ic;
				LCD_ShowxNum(106,260+p*20,ah,2,16,0);
				LCD_ShowString(122,260+p*20,16,16,16,"-");
				break;
				case 4:am+=ic*10;break;
				case 3:am+=ic;
				LCD_ShowxNum(130,260+p*20,am,2,16,0);
				LCD_ShowString(146,260+p*20,16,16,16,"-");
				break;
				case 2:as+=ic*10;break;
				case 1:as+=ic;printf("\r\n");
				LCD_ShowxNum(154,260+p*20,as,2,16,0);
				clockw[p]=aw;
				clockh[p]=ah;
				clockm[p]=am;
				clocks[p]=as;
				clock[p]=as+am*100+ah*10000+aw*100000;
				p++;
				if(p>1)p--;
				RTC_Set_AlarmA(clockw[0],clockh[0],clockm[0],clocks[0]);
				break;
			}			
				if(clock[0]>clock[1])
				{
					x=clockw[0];
					clockw[0]=clockw[1];
					clockw[1]=x;
					x=clockh[0];
					clockh[0]=clockh[1];
					clockh[1]=x;
					x=clockm[0];
					clockm[0]=clockm[1];
					clockm[1]=x;
					x=clocks[0];
					clocks[0]=clocks[1];
					clocks[1]=x;
					x=clock[0];
					clock[0]=clock[1];
					clock[1]=x;
					RTC_Set_AlarmA(clockw[0],clockh[0],clockm[0],clocks[0]);
				}	
			switch(ttt){
				case 3:timing=0;LCD_Fill(280,150,360,200,WHITE);break;
				case 2:timing+=ic*100;LCD_ShowxNum(300,160,timing,3,16,0);break;
				case 1:timing+=ic*10;LCD_ShowxNum(300,160,timing,3,16,0);break;
				case 0:timing+=ic;LCD_ShowxNum(300,160,timing,3,16,0);printf("\r\n");tttt=1;break;
			}		
			rth--;rtm--;sa--;ttt--;
		}USART_RX_STA=0;
		if(tttt==1&&(t%18)==0){
			timing--;
			LCD_ShowxNum(300,160,timing,3,16,0);
			if(timing==0){sign=1;tttt=0;}
		}	
		temp=Get_Temprate();	//得到温度值 
		if(temp<0)
		{
			temp=-temp;
			LCD_ShowString(30+10*8,220,16,16,16,"-");	    //显示负号
		}else LCD_ShowString(30+10*8,220,16,16,16," ");	//无符号
		
		LCD_ShowxNum(30+11*8,220,temp/100,2,16,0);		//显示整数部分
		LCD_ShowxNum(30+14*8,220,temp%100,2,16,0);		//显示小数部分 
		delay_ms(10);
	}	
}