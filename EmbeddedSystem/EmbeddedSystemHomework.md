<!--
 * @Author: your name
 * @Date: 2021-03-27 15:36:25
 * @LastEditTime: 2021-04-26 10:01:37
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\EmbeddedSystemHomework.md
-->
# 作业1（STM32F4体系结构与时钟树）(3.16-3.23)


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




> - ![20210327192727](http:cdn.ayusummer233.top/img/20210327192727.png)
>   - `IO口`：STM32F407ZGT6: 144引脚  114个IO
>       - 大部分IO口都耐5V(模拟通道除外)
>       - 支持调试：SWD和JTAG，SWD只要2根数据线
>   - `存储器容量`：1024K FLASH，192K SRAM



> - ![20210327193954](http:cdn.ayusummer233.top/img/20210327193954.png)
> - ![20210327193149](http:cdn.ayusummer233.top/img/20210327193149.png)
> - ![20210327193222](http:cdn.ayusummer233.top/img/20210327193222.png)


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
> - ![20210327202019](http:cdn.ayusummer233.top/img/20210327202019.png)

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
  - ![20210327205451](http:cdn.ayusummer233.top/img/20210327205451.png)
  > [数据手册是](https://wwe.lanzous.com/iEwOLndsnif)`硬件资料->2.芯片资料->2.芯片资料->STM32F407ZGT6.pdf`
- 查[固件库函数](https://cloud.189.cn/t/6nYBFjmq2iUn)中的参数宏定义:`stm32f4xx_rcc.h`
> - ![20210327211034](http:cdn.ayusummer233.top/img/20210327211034.png)

---
## 6、写出使能GPIOA的时钟和使能TIM6的时钟的固件库函数调用语句。
- ![20210327214322](http:cdn.ayusummer233.top/img/20210327214322.png)
- ![20210327214343](http:cdn.ayusummer233.top/img/20210327214343.png)
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

---
# 作业2(GPIO)

---
## 1、STM32F407ZGT6有哪几组GPIO，共多少I/O引脚？
- STM32F407ZGT6，包含
  - 7组16位IO端口（GPIOA~GPIOG，PA~PG）
  - 1组2位端口GPIOH（GPIOH.0/PH0、GPIOH.1/PH1）
- STM32F407ZGT6有144个I/O引脚
> ![20210329074700](http:cdn.ayusummer233.top/img/20210329074700.png)


---
## 2、GPIO除作一般I/O用之外，还可以复用为外设引脚，请问如何实现引脚复用？PA9可以复用为哪些功能？
- 微控制器的 I/O 引脚通过一个复用器连接到板载外设/模块，该复用器一次仅允许一个外设的复用功能 (AF) 连接到 I/O 引脚，确保共用同一个 I/O 引脚的外设之间不发生冲突,从而实现引脚复用;
- PA9可以复用为如下功能
  - USART1_TX(串口1)
  - TIM1_CH2(定时器TIM1的输出脚2)
  - I2C3_SMBA(第3组I2C的SMBus alert mode的模式)
  - DCMI_D0(数字摄像头接口D0)
  - EVENTOUT(配置用于输出 Cortex™-M4F EVENTOUT 信号的 I/O 引脚)
  - OTG_FS_VBUS(用于检测USB的连接)
> ![20210329075026](http:cdn.ayusummer233.top/img/20210329075026.png)
> ![20210329090501](http:cdn.ayusummer233.top/img/20210329090501.png)
> ![20210329091009](http:cdn.ayusummer233.top/img/20210329091009.png)

---
## 3、下图是STM32F4 GPIO的原理图，简述其输入和输出的工作过程？
- ![20210327220331](http:cdn.ayusummer233.top/img/20210327220331.png)
  
  ---
- [参考链接@CSDN:ATONEMAN](https://blog.csdn.net/weixin_39869569/article/details/93141430)
  
  ---
- 输入的工作过程
  - 输入模式的信号从引脚传入，进来后，有一个上拉电阻和下拉电阻的选择，是可以控制的（上下拉关闭->浮空;接入上拉电阻->上拉;接入下拉电阻->下拉），之后
    - 信号可能传入模拟通道（如果开启了ADC设备，信号会被送到ADC中）[模拟输入]
    - 信号经过TTL施密特触发器，经过TTL施密特触发器整流，信号相对稳定，一些小的波动被忽略了；然后
      - 信号可以进入复用功能输入通道，如果开启了复用工作模式，相关硬件会来接管这个信号，硬件会自行判断；
      - 信号进入输入数据寄存器，用户可以访问输入数据寄存器来感知传入的信号是高电平还是低电平了。
- 输出的工作过程
  - 信号是从左到右，通过置位/复位寄存器写数据，然后再把置位和复位寄存器里的数据转移到输出数据寄存器中
  - 接着,输出数据寄存器的数据到了输出控制那里，完成信号的调理、逻辑转换以及选择开楼/推挽模式。同时，复用功能的输出也会对输出进行控制。
  - 输出控制之后是开关门，通过了逻辑门，信号才会被转化为真正的信号；通过了逻辑门，就到了上拉、下拉电阻接入控制区，在之后，就是输出引脚了。



---
## 4、GPIO有哪几种输入方式和哪几种输出方式，简述每种方式的特点？
- `推挽输出`
  - 可以输出强高、低电平，连接数字器件;高电平由VDD决定,低电平由VSS决定
  - 推挽结构指两个三极管受两路互补的信号控制,总是在一个导通的时候另外一个截止,优点是开关效率高,电流大,驱动能力强
  - 输出高电平时,电流输出到负载,叫灌电流,可以理解为推;
  - 输出低电平时,负载电流流向芯片,叫拉电流,可以理解为挽
- `开漏输出`
  - 只可以输出强低电平，高电平得靠外部电阻拉高。输出端相当于三极管的集电极;
  - 要得到高电平状态需要上拉电阻才行。
  - 适合于做电流型的驱动,其吸收电流的能力相对强(一般20mＡ以内)
  - 开漏输出具有"线与"功能,一个为低,全部为低,多用于I2C和SMBUS总线
- `复用输出`：数据来自复用外设的输出脚



---
## 5、每组GPIO有哪些相关寄存器，每个寄存器的作用是什么？
- 每组GPIO端口包括10个寄存器
  - 4个32位配置寄存器
    - `端口模式寄存器(GPIOx_MODER)` : 配置端口x.y 的I/O方向模式
    - `端口输出类型寄存器(GPIOx_OTYPER)` : 配置端口x.y的输出类型
    - `端口输出速度寄存器(GPIOx_OSPEEDR)` : 配置端口x.y的输出速度。
    - `端口上拉下拉寄存器(GPIOx_PUPDR)` : 端口 x.y上、下拉配置位
  - 2个32位数据寄存器
    - `端口输入数据寄存器(GPIOx_IDR)` : 端口x输入数据，只读形式，只能在字模式下访问。包含相应 I/O 端口的输入值。
    - `端口输出数据寄存器(GPIOx_ODR)` : 端口输出数据，可通过软件读、写。
  - `端口置位/复位寄存器(GPIOx_BSRR)`
    - 位 31:16 BRy： 端口 x.y 复位位，只写。0：无操作；1：复位
    - 位 15:0 BSy： 端口 x.y 置位位，只写。 0：无操作；1：置位 
    - 如果同时对 BSx 和 BRx 置位，则 BSx 优先。
  - `端口配置锁存寄存器(GPIOx_LCKR)` : 用于锁定端口位的配置，在一个端口上执行特定的锁定程序后，在下次复位前将不能再更改该端口位的配置。主要用于防止程序跑飞引起灾难性后果。
  - `复用功能寄存器(GPIOx_AFRL & GPIOx_AFRH)` : 端口x.y的复用功能选择

---
## 6、GPIO_InitTypeDef结构体有哪些成员，各成员的作用是什么？
```C
typedef struct{
  uint32_t GPIO_Pin              // 指定要初始化的端口
  GPIOMode_TypeDef GPIO_Mode;    // 端口模式
  GPIOSpeed_TypeDef GPIO_Speed;  // 速度
  GPIOOType_TypeDef GPIO_OType;  // 输出类型
  GPIOPuPd_TypeDef GPIO_PuPd;    // 上拉或者下拉
}GPIO_InitTypeDef;
```


---
## 7、用寄存器方式和固件库方式写出GPIOA的初始化程序，将PA.0初始化成50MHZ上拉输入方式，PA.1初始化成100MHZ推挽输出方式。
> ![20210329094646](http:cdn.ayusummer233.top/img/20210329094646.png)

  ---
- `寄存器方式`

```C
void GPIOA_init(void){
  RCC->AHB1ENR |= 1<<0;     // 打开GPIOA时钟，RCC_AHB1ENR.5  GPIOA->MODER &= ~(3<<2*9);  //GPIOF.9通用输出模式
  GPIOA->MODER |= 1<<(2*9);
  GPIOF->OSPEEDR &= ~(3<<2*9); //GPIOF.9速度100MHz
  GPIOF->OSPEEDR |= 3<<(2*9);
  GPIOF->PUPDR &= ~(3<<2*9);     //GPIOF.9上拉
  GPIOF->PUPDR |=1<<(2*9);
  GPIOF->OTYPER &= ~(1<<9);        //GPIOF.9推挽输出模式
  GPIOF->OTYPER |=0<<9;
  GPIOF->ODR|= 1<<9;                      //GPIOF.9=1，熄灭DS0

  GPIOF->MODER &= ~(3<<2*10);        //GPIOF.10设置，同GPIOF.9
  GPIOF->MODER |= 1<<(2*10);
  GPIOF->OSPEEDR &= ~(3<<2*10);
  GPIOF->OSPEEDR |= 3<<(2*10);
  GPIOF->PUPDR &= ~(3<<2*10);
  GPIOF->PUPDR |=1<<(2*10);
  GPIOF->OTYPER &= ~(1<<10);
  GPIOF->OTYPER |=0<<10;
  GPIOF->ODR|= 1<<10;
}
```

  ---
- `固件库方式`

```C

```

---
# 作业3-NVIC与外部中断

---
## 1、Cortex-M4 NVIC支持多少中断？STM32F407支持多少中断？
- Cortex-M4支持256个中断
  - 16个内核中断
  - 240个可屏蔽中断
  - 每个I/O口都可以作为中断输入


---
## 2、Cortex-M4 NVIC对中断优先级是如何管理的？其中断嵌套规则是什么？



---
## 3、STM32F4 中，若采用中断分组2，则抢占优先级和响应优先级各占几位？若中断a的抢占优先级为2，响应优先级为1；中断b的抢占优先级为3，响应优先级为0；中断c的抢占优先级为2，响应优先级为0；中断d的抢占优先级为1，响应优先级为2；则4个中断的优先级顺序如何，嵌套规则如何？





---
## 4、写出把PB2配置到外部中断线EXTI2的固件库函数调用语句。



---
## 5、简述stm32中中断和事件的区别，相比中断使用事件方式有什么好处？


---
## 6、写出设置中断分组2，使能EXTI0，并将其初始化为抢占优先级为2，响应优先级为1的代码。




---
## 7、将EXTI2设置为上升沿和下降沿均可触发的中断，并将其使能，写出相应的代码。









---
## 8、若PA5连接一LED指示灯（PA5为0时灯亮，为1时灯灭），PB5连接一按钮开关（开关闭合时为低电平）。现欲实现开关每按一次，LED的状态翻转一次。请用中断方式编写实现该功能的代码。

---
# 作业4-看门狗WDG

----
## 1、什么是看门狗？看门狗的作用是什么？STM32F4有哪些看门狗？
- `什么是看门狗` : 出于对单片机运行状态进行实时监测的考虑，便产生了一种专门用于监测单片机程序运行状态的模块或者芯片，俗称“看门狗”(watchdog)
- `看门狗的作用`
  - 监测单片机程序运行状态
  - 递减器计数（定时器），溢出时，使系统复位
- STM32F4有独立看门狗和窗口看门狗

---
## 2.结合框图叙述独立看门狗（IWDG）的工作原理。
![20210420072310](http:cdn.ayusummer233.top/img/20210420072310.png)  
![20210420115439](http:cdn.ayusummer233.top/img/20210420115439.png)
- 在键值寄存器（IWDG_KR）中写入0xCCCC（启动），开始启用独立看门狗。此时计数器开始从其复位值0xFFF递减
- 重装寄存器(IWDG_RLR​)受写访问保护。这个值由软件设置，每次对IWDR_KR 寄存器写入值 AAAAh （喂狗）时，这个值就会重装载到看门狗计数器中。之后，看门狗计数器便从该值开始递减计数。
- 状态寄存器(IWDG_SR​)
  - 位 1 RVU： 看门狗计数器重载值更新，可通过硬件将该位置 1 以指示重载值正在更新。
  - 位 0 PVU： 看门狗预分频器值更新，可通过硬件将该位置 1 以指示预分频器值正在更新。
- 预分频寄存器(IWDG_PR​)位 2:0 PR[2:0]：​受写访问保护。,数据传入8位预分频器
- 低速内部时钟(LSI)经8位预分频器分频触发12位减1计数器
- 当计数器值计数到尾值0x000时会产生一个复位信号（IWDG_RESET）。​
- 如果程序异常，就无法正常喂狗，则导致系统复位。​


---
## 3、写出独立看门狗的库函数配置过程。
- 取消寄存器写保护:
  ```C
  IWDG_WriteAccessCmd();​
  ```
- 设置独立看门狗的预分频系数，确定时钟: ​
  ```C
  IWDG_SetPrescaler();​
  ```
- 设置看门狗重装载值，确定溢出时间:​
  ```C
  IWDG_SetReload();​
  ```
- 使能（启动）看门狗​
  ```C
  IWDG_Enable();​
  ```
- 应用程序喂狗:​
  ```C
  IWDG_ReloadCounter();​
  ```


---
## 4、结合框图叙述窗口看门狗（WWDG）的工作原理。
![20210420072333](http:cdn.ayusummer233.top/img/20210420072333.png)  
![20210420121437](http:cdn.ayusummer233.top/img/20210420121437.png)  
- PCLK1经过WDG预分频器(WDGTB)再次分频送入6位递减计数器
- 上窗口就是配置寄存器WWDG->CFR里设定的W[6:0];
- 下窗口是固定的0x40；
- 当窗口看门狗的计数器在上窗口值之外，或是低于下窗口值都会触发CMP=1从而写WWDG_CR产生复位。



---
## 5、写出窗口看门狗的库函数配置过程。
- 使能看门狗时钟：​
  ```C
  RCC_APB1PeriphClockCmd();​
  ```
- 设置分频系数：​
  ```C
  WWDG_SetPrescaler();​
  ```
- 设置上窗口值：​
  ```C
  WWDG_SetWindowValue();​
  ```
- 开启提前唤醒中断并对NVIC初始化(可选)：​
  ```C
  WWDG_EnableIT();   NVIC_Init();​
  ```
- 使能看门狗：​
  ```C
  WWDG_Enable();​
  ```
- 喂狗:​
  ```C
  WWDG_SetCounter();​
  ```
- 编写中断服务函数​
  ```C
  WWDG_IRQHandler();​
  ```


---
# 作业5-定时器

----
## 1、STM32F4有哪些定时器，有什么区别？




---
## 2、STM32F4的通用定时器有哪些计数模式，简述其特点。







----
## 3、写出通用定时器溢出中断的库函数配置流程。









---
## 4、下列代码把TIM2通道3配置为输入捕获方式的初始化代码，请将其补充完整
```C
void TIM2_CH3_Cap_Init(u32 arr, u16 psc){
    GPIO_InitTypeDef  GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_ICInitTypeDef  TIM2_ICInitStructure；
    NVIC_InitTypeDef  NVIC_InitStructure;
    //TIM2时钟    

    //GPIO时钟	
    
    GPIO_InitStructure.GPIO_Pin =                  ; 
    GPIO_InitStructure.GPIO_Mode =                ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN; 
                                                 ; 
                                                 ; 
    TIM_TimeBaseStructure.TIM_Prescaler=psc;  
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseStructure.TIM_Period=arr;   
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
                                            ;
    TIM2_ICInitStructure.TIM_Channel =                   ; 
    TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1
    TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //不分频
    TIM2_ICInitStructure.TIM_ICFilter =                ;     //不滤波
                                                ;
                                                ;//更新中断，CC1IE捕获中断使能
                                                ;
    NVIC_InitStructure.NVIC_IRQChannel =              ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelCmd =           ; 
    NVIC_Init(&NVIC_InitStructure);
}
```

----
## 5、PWM波有什么作用？简述STM32定时器产生PWM波的原理，PWM波的周期和占空比是如何确定的？







---
## 6、写出用库函数配置定时器为PWM输出方式的流程（以TIM14的通道1为例）


