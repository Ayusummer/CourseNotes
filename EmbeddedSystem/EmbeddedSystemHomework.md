<!--
 * @Author: your name
 * @Date: 2021-03-27 15:36:25
 * @LastEditTime: 2021-03-27 21:44:32
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\EmbeddedSystemHomework.md
-->
# 作业一（STM32F4体系结构与时钟树）(3.16-3.23)


## 1、简述STM32F4与Cortex-M4的关系，STM32F407ZGT6有哪些外设资源？
- STM32F4的内核是Cortex-M4
- STM32F407ZGT6的外设
  - `GPIO`:7组16位端口,1组2位端口
  - `通信接口(17个接口)`:
    - 3个I2C接口
    - 6个串口
    - 3个SPI接口
    - 2个CAN2.0
    - 2个USB OTG
    - 1个SDIO
  - 2个12位DA
  - 16个DMA通道 ，带FIFO和突发支持;支持外设：定时器，ADC,DAC，SDIO,I2S,SPI,I2C,和USART
  - `定时器`：多达17个定时器
    - 10个通用定时器（TIM2和TIM5是32位）
    - 2个基本定时器
    - 2个高级定时器
    - 1个系统定时器
    - 2个看门狗定时器




> - ![20210327192727](http:qpokg4i30.hn-bkt.clouddn.com/img/20210327192727.png)
>   - `IO口`：STM32F407ZGT6: 144引脚  114个IO
>       - 大部分IO口都耐5V(模拟通道除外)
>       - 支持调试：SWD和JTAG，SWD只要2根数据线
>   - `存储器容量`：1024K FLASH，192K SRAM



> - ![20210327193954](http:qpokg4i30.hn-bkt.clouddn.com/img/20210327193954.png)
> - ![20210327193149](http:qpokg4i30.hn-bkt.clouddn.com/img/20210327193149.png)
> - ![20210327193222](http:qpokg4i30.hn-bkt.clouddn.com/img/20210327193222.png)


---
## 2、结合STM32F4的时钟树，回答问题：

---
### 1）STM32F4有哪几个时钟源，简述各自特点。
- 5个时钟源
  - `LSI`：低速内部时钟，RC 振荡器，频率为 32kHz 左右。供独立看门狗、RTC、自动唤醒单元使用
  - `LSE`：低速外部时钟，接频率为32.768kHz 的石英晶体。主要是 RTC 的时钟源 
  - `HSI`：高速内部时钟，RC 振荡器，频率为 16MHz。可以直接作为系统时钟或者用作 PLL输入 
  - `HSE`：高速外部时钟，可接石英/陶瓷谐振器，或者接外部时钟源，频率范围4MHz~26MHz。**开发板接8M晶振**。HSE也可以直接做为系统时钟或者 PLL 输入。 
  - `PLL`：锁相环倍频输出 
    - `主 PLL`：由 HSE 或者 HSI 提供时钟信号，并具有两个不同的输出时钟。
      - `PLLP`：生成高速的系统时钟（最高168MHz）
      - `PLLQ`：生成 USB OTG FS 的时钟（48MHz）、随机数发生器的时钟和 SDIO时钟 
    - `专用 PLL（PLLI2S）`：生成精确时钟，从而在 I2S 接口实现高品质音频性能 



---
### 2）简述锁相环PLL的工作原理。若PLL的输入时钟fin=4MHz，设置分频、倍频因子M=8，N=336，P=2，则PLL的输出时钟fout为多少？
- $f_{out} = f_{in} \times \frac{N}{M \times P} \\ = 4MHz \times \frac{336}{8 \times 2} \\ = 84MHz$
> - ![20210327202019](http:qpokg4i30.hn-bkt.clouddn.com/img/20210327202019.png)

---
## 3、正点原子探索者STM32F4开发板上SYSCLK（系统时钟）、AHB 总线、APB1 总线、APB2 总线、PLL主时钟的时钟频率分别是多少？
- SYSCLK（系统时钟） =168MHz
- AHB 总线时钟（HCLK=SYSCLK）=168MHz
- APB1 总线时钟（PCLK1=SYSCLK/4）=42MHz
- APB2 总线时钟（PCLK2=SYSCLK/2）=84MHz
- PLL主时钟 =168MHz 

---
## 4、STM32F4固件库中外设时钟使能函数有哪几个，写出函数原型。
```C
void RCC_AHB1PeriphClockCmd(uint32_t    
         RCC_AHB1Periph, FunctionalState NewState);
void RCC_AHB2PeriphClockCmd(uint32_t 
         RCC_AHB2Periph, FunctionalState NewState);
void RCC_AHB3PeriphClockCmd(uint32_t 
         RCC_AHB3Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t 
         RCC_AHB1Periph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t 
         RCC_AHB2Periph, FunctionalState NewState);

```


---
## 5、如何知道某个外设挂接哪个总线上，从而调用相应的时钟使能函数开启外设时钟？
- `数据手册`:P17：`Figure 5. STM32F40x block diagram`
  - ![20210327205451](http:qpokg4i30.hn-bkt.clouddn.com/img/20210327205451.png)
  > [数据手册是](https://wwe.lanzous.com/iEwOLndsnif)`硬件资料->2.芯片资料->2.芯片资料->STM32F407ZGT6.pdf`
- 查[固件库函数](https://cloud.189.cn/t/6nYBFjmq2iUn)中的参数宏定义:`stm32f4xx_rcc.h`
> - ![20210327211034](http:qpokg4i30.hn-bkt.clouddn.com/img/20210327211034.png)

---
## 6、写出使能GPIOA的时钟和使能TIM6的时钟的固件库函数调用语句。
- ![20210327214322](http:qpokg4i30.hn-bkt.clouddn.com/img/20210327214322.png)
- ![20210327214343](http:qpokg4i30.hn-bkt.clouddn.com/img/20210327214343.png)
```C
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);    // 使能TIM6时钟

RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   // 使能GPIOA的时钟
```

---
## 7、写出设置系统时钟源为HSI的函数调用语句。写出设置APB1时钟为HCLK的2分频的函数调用语句。
```C
// 设置系统时钟源为HSI
RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

// 设置APB1时钟为HCLK的2分频
RCC_PCLK1Config(RCC_HCLK_Div2);
```

