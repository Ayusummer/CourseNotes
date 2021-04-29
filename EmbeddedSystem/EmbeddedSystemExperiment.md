# 实验2-跑马灯
- [参考链接](https://nosteglic.blog.csdn.net/article/details/108703814)

---
## 实验要求
- 实现如下函数
  - `led_left()` : 实现led灯左移,右边灯亮，然后右边灯灭的同时左边灯亮。循环次数由函数入口参数决定。(`测试时左移3次`)
  - `led_ right()` : 实现led灯右移，左边灯亮，然后左边灯灭的同时右边灯亮。循环次数由函数入口参数决定。(`测试时右移3次`)
  - `led_ blink()` : 实现led灯闪烁，哪一个灯闪，闪的次数，都由函数入口参数决定。(`测试时0、 1、0&1各闪2次`)
  - `led_bcd()` : 实现0-3的数值的显示，比如0-00,1-01,2-10,3-11,显示的数值由函数入口参数决定。
- 函数写好后，在main()中分别进行调用演示。


----
# 实验3-按键输入实验
- [参考链接](https://nosteglic.blog.csdn.net/article/details/108704149)

----
## 实验要求
- 按下KEY0后,LED0亮度由量变暗(呼吸灯效果),LED0亮的过程中无全灭无停顿感
- 按下KEY1后,LED0立刻熄灭

---
## 实验源码

---
### 多循环版
- `呼吸灯原理`:将呼/吸时间段划分成若干个周期,每个周期时间里灯泡亮的时间占比越来越低则越来越暗,越来越高则越来越亮
```C
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
typedef enum {FALSE = 0，TRUE = 1} bool；// bool宏定义

/*LED灯闪烁*/
void led_blink(u32 t,u32 bright){
    LED0=0;                  // 亮
    delay_us(bright);        // 保持亮,注意是us微秒
    LED0=1;                  // 暗
    delay_us(t-bright);      // 保持暗,注意是us微秒
}

/*熄灯判断*/
bool led_off(u8 key, int flag){
    if(key == KEY1_PRES || flag==1){
        flag = 1;   // KEY1按下flag置1补齐逻辑
        LED0 = 1;   // 灭灯
        return TRUE;
    }
    else return FALSE;
}

int main(void){ 
    u8 key;            // 保存键值
    delay_init(168);   // 初始化延时函数
    LED_Init();        // 初始化LED端口 
    BEEP_Init();       // 初始化蜂鸣器端口
    KEY_Init();        // 初始化与按键连接的硬件接口
    LED0=0;            // 先点亮红灯
 
    while(1){
        key=KEY_Scan(0);    // 得到键值
        if(key){            // 如果键值不为空->若有按键
            switch(key){    
                case WKUP_PRES:     // 上键不操作
                    break;
                case KEY2_PRES:     // 左键不操作
                    break;
                case KEY1_PRES:     // KEY1(下键)灭红灯
                    LED0=1;         // 熄灭LED0(红灯)
                    break;
                case KEY0_PRES:     // KEY0(右键)呼吸灯
                    while(1){       // 循环执行呼吸灯,直至按下下键跳出循环
                        int breath_time_total = 1500;  // 整个周期，1500ms->1.5s->模拟呼吸,吸气呼气各1.5s
                        int breath_time_left = 100;
                        int i;          // 计数器
                        int flag=0;     // 灭灯标记
                        
                        // 亮->暗
                        for(i=breath_time_total; i>breath_time_left; i--){
                            // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
                            if(led_off(KEY_Scan(1),flag))   break;  
                            // 亮i us灭breath_time_total+breath_time_left-i ms
                            led_blink(breath_time_total+breath_time_left,i);         
                        }
                        
                        // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
                        if(led_off(KEY_Scan(1),flag))   break;  

                        for(i=breath_time_left;i<breath_time_total;i++){
                            // 若按下KEY1则熄灯并跳出暗->亮循环
                            if(led_off(KEY_Scan(1),flag))   break;  
                             // 亮i us灭breath_time_total+breath_time_left-i us
                            led_blink(breath_time_total,i);        
                        }
                        
                        // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
                        if(led_off(KEY_Scan(1),flag))   break;  

                    }   // 呼吸灯循环
                    break;  //KEY0 -> case -> break
            }   // 按键判断
        }   // 若有按键
    }   // 整个程序循环体
}   // main()函数
```



----
### 少循环版
- 原理  
  ![20210417193651](http:cdn.ayusummer233.top/img/20210417193651.png)
```C
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
typedef enum {FALSE = 0，TRUE = 1} bool；// bool宏定义

/* LED灯闪烁 */
void led_blink(u32 t,u32 bright){
    LED0=0;             // 亮
    delay_ms(bright);   // 保持亮
    LED0=1;             // 暗
    delay_ms(t-bright); // 保持暗
}

/*熄灯判断*/
bool led_off(u8 key, int flag){
  if(key == KEY1_PRES || flag==1){
    flag = 1;   // KEY1按下flag置1补齐逻辑
    LED0 = 1;   // 灭灯
    return TRUE;
  }
  else return FALSE;
}


int main(void){ 
  u8 key;               // 保存键值
  delay_init(168);      // 初始化延时函数
  LED_Init();           // 初始化LED端口 
  BEEP_Init();          // 初始化蜂鸣器端口
  KEY_Init();           // 初始化与按键连接的硬件接口
  LED0=0;               // 先点亮红灯
  
  while(1){
    key=KEY_Scan(0);        // 扫描按键
    // KEY1熄灭LED0
    if(KEY_Scan(1) == KEY1_PRES) LED0=1;  
    // KEY0呼吸灯
    else if(KEY_Scan(1) == KEY0_PRES){
          while(1){
            int flag=0;
            int i;
            int breath_time_total=1500;             // 整个周期，1500ms->1.5s->模拟呼吸,吸气呼气各1.5s
            int breath_single_time=20;              // 人眼可见最短的图像滞留周期即每个周期的时间，20ms
            int breath_times=breath_time_total/breath_single_time;  // 周期数75
            int breath_left_times = 20;             // 呼吸保周期次数,相应的要占满75个周期就要求周期从周期数+保留次数开始
            int breath_times_max = breath_times + breath_left_times;   // 呼吸周期最大次数
            // 周期总数递减->从亮到暗
            for(i=breath_times_max; i>=breath_left_times; i--){        
              // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
              if(led_off(KEY_Scan(1),flag))   break;  
              led_blink(breath_single_time, breath_single_time*i/breath_times_max);  //LED灯闪烁
            }
            // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
            if(led_off(KEY_Scan(1),flag))   break;  
            // 周期总数自增->breath_times_max,从暗到亮
            for(i=breath_left_times;i<=breath_times_max;i++){       
              // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
              if(led_off(KEY_Scan(1),flag))   break;  
              led_blink(breath_single_time,breath_single_time*i/breath_times_max);  //LED灯闪烁
            }
            // 若按下KEY1或者KEY1已经按下(flag==1)则熄灯并跳出呼吸循环
            if(led_off(KEY_Scan(1),flag))   break;  
          } // 呼吸灯循环
    } // KEY0结束
  } // 整个程序循环体
} // main()函数
```
- 实际上flag可以"优化掉;原因在于程序执行速度比较快,那么实际操作过程中按下KEY1键这个动作完全可以覆盖仅仅两个判断的执行时间这样也可以实现KEY1灭灯效果,只不过代码逻辑上不完善
- 比上一版的循环要少许多,性能也要好,不过由于循环次数有限,没有上一版呼吸灯显得那么流畅


----
# 实验4-外部中断实验
- [参考链接](https://nosteglic.blog.csdn.net/article/details/108704493)

----
## 实验要求
- 不断按下任意按键将产生一个按键序列(不限个数)，当出现KEY0-> KEY0->KEY1->KEY1->KEY2->KEY2-KEY2->KEY_ UP序列时，LED0状态改变。如果没有按这个顺序，则LED0的状态不发生改。
- 011222U (不变)，00011222U (变),00110011222U (变), 001011222U (不变)

---
## 常见问题 & 建议
- ![20210417194411](http:cdn.ayusummer233.top/img/20210417194411.png)
- 原程序中消抖使用的了`delay_ms(10)`,实际效果不好,可以改成`delay_ms(100)`
- 有时候按键按下去可能并没有检测到,可以在中断服务程序中设计按键按下去之后亮个灯或者蜂鸣器响一下之类以便操作时判断按键是否生效


---
## 设计思路
- 状态转换图
  ![20210422103117](http:cdn.ayusummer233.top/img/20210422103117.png)
---
## 实验程序
- 中断服务程序
```C
int width=0;	// 滑动窗口宽度,用于判断LED0是否到了需要改变状态的时候

// 外部中断4服务程序(KEY0,右键)
void EXTI4_IRQHandler(void){
	delay_ms(100);      // 消抖
	if(KEY0==0){
        LED1 = !LED1;	// 测试语句,KEY0按下后LED1反相,用于实测时判断是否检测到了KEY0按下
        			 
		if(width == 0 || width == 1) width++;   // 滑窗扩大1格,进入下个状态
		else {                          // width > 1
            if(width == 2);             // width == 2 时再按KEY0滑窗宽度不在增加
            else width=1;               // width > 2  时再按KEY0则滑窗宽度置1
        }
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);	// 清除LINE4上的中断标志位  
}


// 外部中断3服务程序(KEY1,下键)
void EXTI3_IRQHandler(void){
	delay_ms(100);	    // 消抖
	if(KEY1==0){
        LED1 = !LED1;   // 测试语句,KEY1按下后LED1反相,用于实测时判断是否检测到了KEY1按下

		if(width == 2 || width == 3) width++;   // 只有2,3两种状态(滑窗宽度)下按下KEY1(下键)才会使滑窗宽度增加
		else width=0;   // 其他情况下按下KEY1(下键)滑窗清零
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);         // 清除LINE3上的中断标志位  
}


// 外部中断2服务程序(KEY2,左键)
void EXTI2_IRQHandler(void){
	delay_ms(100);	    // 消抖
	if(KEY2==0){	
        LED1 = !LED1;   // 测试语句,KEY2(左键)按下后LED1反相,用于实测时判断是否检测到了KEY2(左键)按下
        // 当滑窗宽度为4,5,6时按下左键(KEY2)才会使滑窗宽度增加
		if(width == 4 || width == 5 || width == 6 ) width++;    
		else width=0;  // 否则滑窗清零
	}	 
	EXTI_ClearITPendingBit(EXTI_Line2); // 清除LINE2上的中断标志位 
}


// 外部中断0服务程序(WK_UP, 上键)
void EXTI0_IRQHandler(void){
	delay_ms(100);	    // 消抖
    if(WK_UP==1){       
        LED1 = !LED1;   // 测试语句,WK_UP(上键)按下后LED1反相,用于实测时判断是否检测到了WK_UP(上键)按下
        // 只有当滑窗宽度为7时按下上键(WK_UP)才能滑窗宽度增加,状态达到终态,LED0反相
		if(width==7){
            width++;
            LED0=!LED0;
        }
        // 其它状态下按下上键只会导致滑窗清零
		else width=0; 
	}		
	EXTI_ClearITPendingBit(EXTI_Line0); 	// 清除LINE0上的中断标志位 
}	
```


---
# 实验5-独立看门狗实验
- [参考链接](https://nosteglic.blog.csdn.net/article/details/108704695)

---
## 实验要求
- 1、LED1以呼吸灯指示系统正在运行，如果未及时喂狗，则看门狗发出复位信号，LED1会熄灭(跳闪)
- 2、按键KEY1工作于外部中断方式喂狗;
- 3、在看门狗复位信号产生前进行高频声光报警，即复位前1.5秒左右LED0开始闪烁，同时蜂鸣器间断鸣叫，提示喂狗;报警时呼吸灯不能停止:
- 4、按KEY1喂狗后，报警信息立即全部解除。

----
## 设计思路
- 独立看门狗相关知识
  - ![20210417194840](http:cdn.ayusummer233.top/img/20210417194840.png)
  - ![20210417194858](http:cdn.ayusummer233.top/img/20210417194858.png)

---
### 注意点
- 1.**呼吸灯与看门狗"并行"**
  - `问题阐述` : 由于呼吸灯以及看门狗的实现中都有循环参与(呼吸灯的呼吸循环以及看门狗的报警循环),如果把两处循环分开写,先执行一个循环后执行另一个循环,则看门狗报警时会卡死呼吸灯,导致看门狗报警时呼吸灯状态停止变动
  - `解决方案` : 拆掉一个循环,将其中一个循环的循环体写在其他循环的循环体中;
  - `例如` : 将看门狗的报警判断分别放在呼吸灯的呼吸循环中,循环的每次执行除了闪烁LED1外都会对看门狗报警条件进行判断,若条件成立则相应状态反向一次,然后在执行闪烁函数,利用闪烁函数中的延迟函数实现状态反向后的保持;                                                         

  -----
- 2.**看门狗报警两灯频率以及蜂鸣器频率的调整**
  - `问题阐述` : 如果将一个循环的循环体嵌套在另一个循环的循环体中,那么会导致拆掉的循环体跟着依附循环体的步调走,如果宿主步调太快则会导致从者频率比原本循环快(比如看门狗报警时蜂鸣器和LED0变化频率过高)   
  - `解决方案` : 宿主步调快的话,从者在宿主中可以选择执行,不是宿主每次循环执行从者都执行;  
    - 可以在宿主里的从者代码使用分频,在外部定义一个循环变量,宿主循环每次执行时循环变量都+1,当循环变量等于某个特定值时才执行从者代码;
    - 由于循环变量是循环变化的,因此循环变量的"变化宽度"是几就可以理解成是几分频


---
## 常见问题

---
### 1.变量未定义(如:flag 未定义):
- 有的同学在头文件的对应源文件中做了变量定义,然后在main.c里调用会出现变量未定义
- [解决方案参考链接](https://blog.csdn.net/qq_42681507/article/details/103283506)
- 可以在`exti.h`中声明全局变量flag
  ```C
  extern int flag;
  ```
- 然后在`exti.c`中定义该全局变量
  ```C
  int flag=0;     // 喂狗标志
  ```
- 这样其它导入`exti.h`的源文件就可以使用flag变量了

---
### 2.中断无法判断(关于exti的全报错)
- 比如这种报错:`..\Objects\stm32f103c8t6_all_in_one.axf: Error: L6218E: Undefined symbol EXTI_ClearITPendingBit (ref`
  - [参考链接](https://blog.csdn.net/m0_37135980/article/details/103889881)
- 这是因为本次实验给的模板里面均没有导入中断的头文件与源文件,需要导入对应头文件及源文件
  - ![20210417195316](http:cdn.ayusummer233.top/img/20210417195316.png)
  - ![20210417195335](http:cdn.ayusummer233.top/img/20210417195335.png)
  - ![20210417195359](http:cdn.ayusummer233.top/img/20210417195359.png)

----
## 实验程序
- 详见`Experiment`文件夹中对应实验目录

----
# 实验6-基本定时器实验
- [参考链接](https://nosteglic.blog.csdn.net/article/details/108704934)

----
## 实验内容
- 用定时器3中断方式控制LED0和LED1的闪烁频率；
- KEY0、KEY1和KEY2工作于中断方式；
- 用按键KEY0控制LED0启动闪烁，再按一次则LED0停止闪烁，熄灭；
- 用按键KEY1控制LED1启动闪烁，再按一次则LED1停止闪烁，熄灭；
- 如果LED0或LED1在闪烁，按KEY2点亮LED0或LED1，原来闪烁的停止，这时按KEY0或KEY1不发生任何改变；再按下KEY2后，恢复原来的状态，即闪烁的继续闪烁，熄灭的依然熄灭。


----
## 注意事项
- 改变闪烁频率
  ```
  TIM3_Int_Init(arr-1,psc-1);	// 改变计数值arr和分频系数psc
  ```

  ----
- `u8`：`unsigned char`
- `u16`、`u32`：`整型`

  ---
- 原项目中没有使用到,但是当前项目使用到的源码记得加
  ![20210428224744](http:cdn.ayusummer233.top/img/20210428224744.png)   
  ![20210428224839](http:cdn.ayusummer233.top/img/20210428224839.png)

----
## 实验程序
- `timer.c`
  ```C
  /*
  * @Author: your name
  * @Date: 2021-04-22 19:46:27
  * @LastEditTime: 2021-04-28 22:22:41
  * @LastEditors: Please set LastEditors
  * @Description: In User Settings Edit
  * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\实验8-第6次实验-定时器中断实验\timer-v3.0-lc.c
  */
  #include "timer.h"
  #include "led.h"
  //////////////////////////////////////////////////////////////////////////////////	 
  //本程序只供学习使用，未经作者许可，不得用于其它任何用途
  //ALIENTEK STM32F407开发板
  //定时器 驱动代码	   
  //正点原子@ALIENTEK
  //技术论坛:www.openedv.com
  //创建日期:2014/5/4
  //版本：V1.0
  //版权所有，盗版必究。
  //Copyright(C) 广州市星翼电子科技有限公司 2014-2024
  //All rights reserved									  
  ////////////////////////////////////////////////////////////////////////////////// 	 
  extern int press_key0;   // KEY0按键是否按下 : 1->按下
  extern int press_key1;   // KEY1是否按下 : 1->按下

  //通用定时器3中断初始化
  //定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
  //Ft=定时器工作频率,单位:Mhz
  //这里使用的是定时器3!

  void TIM3_Int_Init(u16 arr,u16 psc){
      TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
      NVIC_InitTypeDef NVIC_InitStructure;
      
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  // 使能TIM3时钟
      
        TIM_TimeBaseInitStructure.TIM_Period = arr; 		// 自动重装载值
      TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  		// 定时器分频, 时钟预分频数
      TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 	// 向上计数模式
      TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
      
      TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);	// 初始化TIM3
      
      TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); 			// 允许定时器3更新中断
      TIM_Cmd(TIM3,ENABLE); 	// 使能定时器3
      
      NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 		// 定时器3中断
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; 	// 抢占优先级1
      NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; 		// 子优先级3
      NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
      NVIC_Init(&NVIC_InitStructure);
      
  }

  // 定时器3中断服务函数
  void TIM3_IRQHandler(void){
      if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET){	// 溢出中断
          if(press_key1) LED1=!LED1; // LED1(绿灯)反相
          else LED1=1;
          if(press_key0) LED0=!LED0; // LED0(红灯)反相
          else LED0=1;
      }
      TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
  }

  ```

  ----
- `exti.c`
  ```C
  #include "exti.h"
  #include "delay.h" 
  #include "led.h" 
  #include "key.h"
  #include "timer.h"
  //////////////////////////////////////////////////////////////////////////////////     
  //本程序只供学习使用，未经作者许可，不得用于其它任何用途
  //ALIENTEK STM32F407开发板
  //外部中断 驱动代码       
  //正点原子@ALIENTEK
  //技术论坛:www.openedv.com
  //创建日期:2014/5/4
  //版本：V1.0
  //版权所有，盗版必究。
  //Copyright(C) 广州市星翼电子科技有限公司 2014-2024
  //All rights reserved                                      
  ////////////////////////////////////////////////////////////////////////////////// 

  int press_key1=0;          // key1按键状态, 0->按下, 1->未按下
  int press_key0=0;          // key0按键状态, 0->按下, 1->未按下
  int press_key2=0;          // key2按键状态, 0->按下, 1->未按下

  int L0_old=1;                // LED0原来值->用于交替闪烁保持
  int L1_old=1;                // LED1原来值->用于交替闪烁保持

  // 外部中断4服务程序(KEY0, 右键)
  void EXTI4_IRQHandler(void){
      delay_ms(100);                      // 消抖
      if(KEY0==0 && (!press_key2)){       // 按KEY0且未按下KEY2
          press_key0 = !press_key0;       // KET0按键状态改变
      }
      EXTI_ClearITPendingBit(EXTI_Line4); // 清除LINE4上的中断标志位  
  }


  // 外部中断3服务程序(KEY1, 下键)
  void EXTI3_IRQHandler(void){
      delay_ms(100);                    // 消抖
      if(KEY1==0&&(!press_key2)){       // 按KEY1且未按下KEY2
          press_key1=!press_key1;       // KEY1按键状态改变
      }
      EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
  }


  // 外部中断2服务程序(KEY2, 左键)
  void EXTI2_IRQHandler(void){
      delay_ms(100);                    // 消抖

      // 若KEY2按下
      if(KEY2 == 0){
          press_key2 =! press_key2;     // KEY2按下的标志位反相

          if(press_key2){     // 如果KEY2按下则给当前LED状态上锁
            // 将LED状态送给旧值
            L0_old=LED0;    
            L1_old=LED1;
            // 如果LED在闪烁则将其置为常亮, 若熄灭则不变
            if(press_key0) LED0=0;     // press_key0为1时，LED0正在闪烁，设置成常亮
            if(press_key1) LED1=0;
            
            TIM_Cmd(TIM3,DISABLE);    // 失能TIM3
          }
          // 如果KEY2松开(解锁)
          else{
            // LED状态返回旧值
            LED0=L0_old;             
            LED1=L1_old;
            TIM_Cmd(TIM3,ENABLE);     // 使能TIM3
          }    
      }         
      EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
  }


  //外部中断0服务程序
  void EXTI0_IRQHandler(void){
      delay_ms(10);    //消抖
      if(WK_UP==1){
        // do nothing
      }         
      EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
  }    

        
  //外部中断初始化程序
  //初始化PE2~4,PA0为中断输入.
  void EXTIX_Init(void){
      NVIC_InitTypeDef   NVIC_InitStructure;
      EXTI_InitTypeDef   EXTI_InitStructure;
      
      KEY_Init(); //按键对应的IO口初始化
  
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  // 使能SYSCFG时钟
      
  
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2); // PE2 连接到中断线2
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3); // PE3 连接到中断线3
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4); // PE4 连接到中断线4
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0); // PA0 连接到中断线0
      
      /* 配置EXTI_Line0 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line0;              // LINE0
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     // 中断事件
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  // 上升沿触发 
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;               // 使能LINE0
      EXTI_Init(&EXTI_InitStructure);                         // 配置
        
      /* 配置EXTI_Line2,3,4 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;       // 中断事件
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //下降沿触发
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;                 // 中断线使能
      EXTI_Init(&EXTI_InitStructure);                           // 配置
    
      NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;              // 外部中断0
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  // 抢占优先级0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;         // 子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               // 使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);                               //配置
        
      NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;              // 外部中断2
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;  // 抢占优先级3
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;         // 子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               // 使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);                               // 配置
        
        
      NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;              // 外部中断3
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  // 抢占优先级2
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;         // 子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               // 使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);                               // 配置
        
        
      NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;              // 外部中断4
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;  // 抢占优先级1
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;         // 子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               // 使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);                               // 配置
  }

  ```

  ---
- `main.c`
  ```C
  /*
  * @Author: your name
  * @Date: 2021-04-22 19:47:42
  * @LastEditTime: 2021-04-28 22:43:43
  * @LastEditors: Please set LastEditors
  * @Description: In User Settings Edit
  * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\实验8-第6次实验-定时器中断实验\main-v3.0-lc.c
  */
  #include "sys.h"
  #include "delay.h"
  #include "usart.h"
  #include "led.h"
  #include "timer.h"
  #include "exti.h"



  //ALIENTEK 探索者STM32F407开发板 实验8
  //定时器中断实验-库函数版本
  //技术支持：www.openedv.com
  //淘宝店铺：http://eboard.taobao.com
  //广州市星翼电子科技有限公司  
  //作者：正点原子 @ALIENTEK  
  int main(void){ 
      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
      delay_init(168);    // 初始化延时函数
      LED_Init();         // 初始化LED端口
      EXTIX_Init();       // 初始化外部中断输入
      // 定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数5000次为500ms 
      TIM3_Int_Init(5000-1,8400-1);        
      while(1){
          // do nothing
      };
  }

  ```

