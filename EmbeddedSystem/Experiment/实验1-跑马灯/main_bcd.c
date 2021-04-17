/*
 * @Author: your name
 * @Date: 2021-04-08 20:02:11
 * @LastEditTime: 2021-04-08 20:16:27
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\Experiment\ʵ��1-������\main_bcd.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

// led������,�ұߵ���,Ȼ���ұߵ����ʱ����ߵ���,ѭ����������ڲ�������
void led_left(int x)		// x->ѭ������
{
	while (x)				// ����ѭ����ִ�д���Ϊx
	{
		LED1 = 0;			//  �ұߵ���
		LED0 = 1;			// ��ߵ���
		delay_ms(300);		// ��ʱ300ms
		LED0 = 0;			// ��ߵ���
		LED1 = 1;			// �ұߵ���
		delay_ms(300);		// ��ʱ300ms
		LED0 = LED1 = 1;	// ���ҵ���
		delay_ms(300);		// ��ʱ300ms
		x -= 1;				// ѭ������-1
	}
}

// ������ķ���������,led����
void led_right(int x)
{
	while (x)
	{
		LED0 = 0;
		LED1 = 1;
		delay_ms(300);
		LED0 = 1;
		LED1 = 0;
		delay_ms(300);
		LED0 = LED1 = 1;
		delay_ms(300);
		x -= 1;
	}
}

int max(int a, int b){
    if(a>b) return a;
    else return b;
}

int min(int a, int b){
    if(a<b) return a;
    else return b;
}


int max_i(int a, int b){
    if(a>b) return 0;
    else return 1;
}

int min_i(int a, int b){
    if(a<b) return 0;
    else return 1;
}

// led��˸(��ԭʼ����ı�����ʽһ��)
void led_blink(int bcd_en, int left_times, int right_times)
{
    // ����
    if(bcd_en==0){
        if(min_i(left_times,right_times) == 0){
            while(left_times){
                LED0 = 0;
                LED1 = 0;
                delay_ms(300);
                LED0 = 1;
                LED0 = 1;
                left_times -= 1;   
                right_times -= 1;         
            }
            LED0 = 1;
            while (right_times)
            {
                LED1 = 0;
                delay_ms(300);
                LED1 = 1;
                delay_ms(300);
                right_times -= 1;
            }
            LED1 = 1;
        }
        else{
            while(right_times){
                LED0 = 0;
                LED1 = 0;
                delay_ms(300);
                LED0 = 1;
                LED0 = 1;
                left_times -= 1;   
                right_times -= 1;         
            }
            LED1 = 1;
            while (left_times)
            {
                LED0 = 0;
                delay_ms(300);
                LED0 = 1;
                delay_ms(300);
                left_times -= 1;
            }
            LED0 = 1;
        }
        
    }

    // ��ߵ���
    if(bcd_en==1){
		while(left_times){
			LED0 = 0;
			delay_ms(300);
			LED0 = 1;
			left_times -= 1;
		}
		LED0 = 1;
    }

    // �ұߵ���
    if(bcd_en==2){
        while (right_times)
		{
			LED1 = 0;
			delay_ms(300);
			LED1 = 1;
			delay_ms(300);
			right_times -= 1;
		}
		LED1 = 1;
    }


    // ������
	if(bcd_en==3){
        LED0 = LED1 = 1;
	}
	

}

// 0-3����ֵ����ʾ
void led_gcd(int x){
	if (x == 0) LED0 = LED1 = 0;
	else if (x == 1) LED0 = 0, LED1 = 1;
	else if (x == 2) LED0 = 1, LED1 = 0;
	else LED0 = LED1 = 1;
}



int main(void)
{ 
 
	delay_init(168);		  	// ��ʼ����ʱ����
	LED_Init();		        	// ��ʼ��LED�˿�
	
	led_left(3);

	led_right(3);
	
	led_blink(0,1,3);			// ��1��3
	led_blink(1,2,0);			// ��1��3
	led_blink(2,0,3);			// ��1��3
	led_blink(3,0,0);			// ��1��3
    
	led_gcd(0);
	delay_ms(1000);
	
	led_gcd(1);
	delay_ms(1000);
	
	led_gcd(2);
	delay_ms(1000);
	
	led_gcd(3);
	delay_ms(1000);
  /**??????????????????????????IO????**/	
	
	while (1);
	 
	 
}

/**
*******************?????????????????? ??????????? ??????IO?????**************************************
int main(void)
{ 
 
	delay_init(168);		  //????????????
	LED_Init();		        //?????LED???
	while(1)
	{
     GPIOF->BSRRH=GPIO_Pin_9;//LED0??
	   GPIOF->BSRRL=GPIO_Pin_10;//LED1??
		 delay_ms(300);
     GPIOF->BSRRL=GPIO_Pin_9;//LED0??
	   GPIOF->BSRRH=GPIO_Pin_10;//LED1??
		 delay_ms(300);

	 }
 }	 
**************************************************************************************************
**/	
 



