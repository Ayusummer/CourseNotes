/*
 * @Author: your name
 * @Date: 2021-05-20 17:31:33
 * @LastEditTime: 2021-05-20 18:54:46
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\实验18-第9次实验-ADC实验\main-v1.1.1.1-滚动函数调整.c
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

#define front_axisX 30      // x轴与边界的距离(x轴起点)
#define length_axis_x  400  // x轴长度为40mm
int tail_axisX = length_axis_x + front_axisX;   // x轴尾部横坐标

#define length_axis_y  400  // y轴长度为20mm



#define num_point_per_circle 20      // 每轮周期中的点的数目
int distance_between_two_point = length_axis_x / num_point_per_circle;  // 两点间距

#define distance_plumb_arrow 5          // 箭头与坐标轴的铅垂线距离
#define distance_horizontal_arrow 15    // 箭头与坐标轴端点水平距离


#define minus 30    // 
#define time_zoom_in 5                  // 电压差异放大倍数
#define Make_up_the_difference_vol -100 // y轴电压补差

#define x_begin_point 30                // 起始点横坐标
#define y_begin_point lcddev.height/2   // 起始点纵坐标

u16 buffer[num_point_per_circle];   // 电压缓冲数组
static int index=0;   // 电压缓冲数组下标(循环自增的数组下标)
u16 x1,x2,y1,y2;    // 定义横纵坐标

/*滚动，双标记位实现循环数组*/
void draw_roll(u16 buffer[], u16 temp){
    index = index%num_point_per_circle; 
    buffer[index]=temp;     // 赋值给当前索引值
    int tail_index_draw = index;    // 绘制结束索引
    index++;
    int index_draw = index;     // 绘制索引(起始)

    
    // 起绘点定义
    x1=30;
    y1=buffer[index_draw];
    
    while(1){ 
        // 绘制索引循环自增
        index_draw = (index_draw+1)%num_point_per_circle;

        /* 绘制 */
        x2 = x1+distance_between_two_point;
        y2 = buffer[index_draw];
        LCD_DrawLine(x1,y1,x2,y2);
        
        /* 下条绘制线迭代 */
        x1=x2;
        y1=y2;

        if(index_draw == tail_index_draw) break;
    }
    delay_ms(500);
}


/* 局部清屏，避免抖动
   //在指定区域内填充单个颜色
  LCD_Fill(填充矩形对角坐标, 要填充的颜色);*/
void clean_lcd(void){
    LCD_Fill(31, lcddev.height/2-150, 435, lcddev.height/2+95, WHITE);    
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

    int up_axisY =  lcddev.height/2 - length_axis_y/2;  // y轴上端
    int down_axisY = lcddev.height/2 + length_axis_y/2;  // y轴下端
    /* x，y轴显示
       LCD_DrawLine(x1, y1, x2, y2)   // 画线(起点坐标,终点坐标) */
    LCD_DrawLine( front_axisX,  down_axisY, front_axisX, up_axisY);      // y轴
    LCD_DrawLine( front_axisX,  down_axisY, tail_axisX,  down_axisY);    // x轴
    // y轴箭头左半(y轴顶点->箭头尾)
    LCD_DrawLine( front_axisX,  up_axisY, 
                  front_axisX - distance_plumb_arrow, up_axisY + distance_horizontal_arrow);    
    // y轴箭头右半(y轴顶点->箭头尾)
    LCD_DrawLine( front_axisX,  up_axisY, 
                  front_axisX + distance_plumb_arrow, up_axisY + distance_horizontal_arrow);     
    // x轴箭头上半(x轴顶点->箭头尾)
    LCD_DrawLine( tail_axisX, down_axisY, 
                  tail_axisX - distance_horizontal_arrow, down_axisY - distance_plumb_arrow);   
    // x轴箭头下半(x轴顶点->箭头尾)   
    LCD_DrawLine( tail_axisX, down_axisY, 
                  tail_axisX - distance_horizontal_arrow, down_axisY + distance_plumb_arrow);      
    LCD_ShowString(0,          up_axisY,     200,16, 16, "VOL");     // y轴标注 VOL   
    LCD_ShowString(tail_axisX, down_axisY+5, 200,16, 16, "TIME");    // x轴标注 TIME
    
    /*初始化第一个点*/
    x1 = x_begin_point;
    y1 = y_begin_point;
    
    while(1){
        adcx=Get_Adc_Average(ADC_Channel_5,20);     // 获取通道5的转换值，20次取平均 about 3835~3837
        temp=(float)adcx*(3.3/4096);                // 获取计算后的带小数的实际电压值，比如3.1111
        
        /*显示整数 LCD_ShowxNum(起点坐标, 数值, 长度也即要显示的位数, 字体大小, mode)*/
        adcx=temp;      // 赋值整数部分给adcx变量，因为adcx为u16整形
        LCD_ShowxNum(32+lcddev.width*2/5, lcddev.height*9/10, adcx, 1,16, 0);
        
        /*显示小数*/
        temp -= adcx;       // 去整
        temp = temp*1000;   // 小数部分转整数
        // 显示小数部分
        LCD_ShowxNum(47+lcddev.width*2/5, lcddev.height*9/10,temp, 3, 16, 0x80);    
        
        // 第一轮
        if(count<num_point_per_circle){                            
            x2 = x1 + distance_between_two_point;       // 每隔 distance_between_two_point 画一个像素点
            y2= temp*time_zoom_in + Make_up_the_difference_vol;       // 放大电压差异
            buffer[index]=y2;                          // 电压缓冲区
            index++;
            count++;
            LCD_DrawLine(x1,y1,x2,y2);
            x1=x2;
            y1=y2;
        }
        
        if(count==num_point_per_circle){                            //不是第一轮
            clean_lcd();                          //清屏
            temp= temp*time_zoom_in + Make_up_the_difference_vol;  //放大电压差异
            draw_roll(buffer,temp);               //滚动
        }
    }//while(1)
}
