# 第2章

## 9.16作业

### 数据段的定义如下，阅读后解答后面的问题。
```
VARX DB -1, ’AB’,2 DUP(?，3)
VARY DW 2078H, ’AB’
VARZ DW $-VARX
```
- 1.画出数据段内各变量所定义数据的存放示意图。（6 分）  
  - ![输入图片说明](https://images.gitee.com/uploads/images/2021/0103/091042_447b8924_7703072.png "屏幕截图.png")
  - ![](../res/img/Assembly/ASCII码表.png)
- 2.`MOV CX, SIZE VARX` 执行后，（CX）=`1`。（2 分）
  - size=Length*Type 
  - Length返回DUP定义的元素个数，否则返回1；
  - Type返回变量或标号的类型 DB:1 DW:2
- 3.`MOV AL,BYTE PTR VARY` 执行后, （AL）=`78H`。（2 分）
  - 类型 PTR 变量名/标号：临时改变/指定变量/标号的使用类型
  - VARY变成byte类型，只留有78H 

---
## 9.19 8086基础
### 一.单选题
- 1.设`A=0.4H，B=0.8H，C=0.4，D=0.4Q`，它们之间的关系是( )
  - `A、C+D=B, B、A+D=B, C、B=D, D、A>C>D`
  - 正确答案：C
  - $A=0.4H=(0.0100)_2$  
    $B=0.8H=(0.1000)_2$  
    $C=0.4=(0.011)_2$   
    $D=0.4Q=(0.100)_2$
---
- 2.标志寄存器中属于控制标志位的是（ ）
  - A、DF，OF，SF  
    B、DF，IF，TF  
    C、OF，CF，PF  
    D、AF，OF，SF  
  - 正确答案：B
  - 6个状态标志位的功能分别叙述如下：
    - `CF(Carry Flag)`——进位标志位。当执行一个加法(或减法)运算，使最高位产生进位(或借位)时，CF为1；否则为0。
    - `PF(Parity Flag)`——奇偶标志位。该标志位反映运算结果中1的个数是偶数还是奇数。当指令执行结果的低8位中含有偶数个1时，PF=1；否则PF=0。
    - `AF(Auxiliary carry Flag)`——辅助进位标志位。当执行一个加法(或减法)运算，使结果的低4位向高4位有进位(或借位)时，AF=1；否则AF=0。
    - `ZF(Zero Flag)`——零标志位。若当前的运算结果为零，ZF=1；否则ZF=0。
    - `SF(Sign Flag)`——符号标志位。它和运算结果的最高位相同。
    - `OF(Overflow Flag)`——溢出标志位。当补码运算有溢出时，OF=1；否则OF=0。
  - 3个控制标志位用来控制CPU的操作，由指令进行置位和复位。
    - `DF(Direction Flag)`——方向标志位。它用以指定字符串处理时的方向，当该位置“1”时，字符串以递减顺序处理，即地址以从高到低顺序递减。反之，则以递增顺序处理。
    - `IF(Interrupt enable Flag)`——中断允许标志位。它用来控制8086是否允许接收外部中断请求。若IF=1，8086能响应外部中断，反之则不响应外部中断。
    - `TF(Trap Flag)`——跟踪标志位。它是为调试程序而设定的陷阱控制位。当该位置“1”时，8086 CPU处于单步状态，此时CPU每执行完一条指令就自动产生一次内部中断。当该位复位后，CPU恢复正常工作。
---
- 3.8088/8086存储器分段，每个段不超过（ ）
  - A、64K个字  
    B、32K个字节  
    C、1M个字节  
    D、64K个字节
  - 正确答案：A
  - 16位寄存器表示的最大寻址空间为64KB，$2^{16}$
---
- 4.已知某操作数的物理地址是2117AH，则它的段地址和偏移地址可能是（ ）
  - A、2025:0F2A  
    B、2108:00EA  
    C、2000:017A  
    D、2100:117A
  - 正确答案：A
  - 2025:0F2A 20250+0F2A=2117A 
  - 2108:00EA 21080+00EA=2116A
  - 2000:017A 20000+017A=2017A
  - 2100:117A 21000+117A=2217A
---
- 5.某程序装入内存后，DS=1200H，CS=1400H，则程序中数据段中的数据最多是( )字节。
  - A、2K    
    B、4K   
    C、8K  
    D、16K   
  - 正确答案：A
  - DS到CS之间一共可以有14000h-12000h=2000h个字节
---
- 6.设物理地址(21000H)=20H,(21001H)=30H，(21002H)=40H。如从地址21001H中取出一个字的内容是（ ）
  - A、2030H  
    B、3040H  
    C、3020H  
    D、4030H
  - 正确答案：D
---
- 7.真值-1，用8位二进制补码表示是11111111，如果用16位二进制补码表示是（ ）。
  - A、1111111111111111  
    B、0000000011111111  
    C、1111111100000000  
    D、0000000000000000
  - 正确答案：A
-----
- 9.汇编语言的优点不包括（ ）
  - A、直接有效地控制硬件  
    B、生成的代码序列短小  
    C、编程容易  
    D、运行速度快
  - 正确答案：C
---
### 二.判断题（共2题,20.0分）
- 9.汇编程序使用的保留字，例如寄存器名称等，是不能用作用户定义的标识符的。
  - 正确答案：对
- 10.进位和溢出标志都表达结果超出范围，所以加法运算有溢出，一定也进位了。
  - 正确答案：错
---- 
## 9.28随堂练习
### 编写程序段，求以下变量表达式的值，所有变量均为有符号字变量:
$Z = ( X + Y)/W - S*Y$
- 正确答案:
```
MOV AX, X
ADD AX, Y      ; X + Y (1分)
CWD
IDIV  W        ; ( X + Y)/W (2分)  
CWD    
MOV CX, DX
MOV BX, AX     ; 暂存( X + Y)/W (2分)
MOV AX, S
IMUL Y         ; S*Y (2分)
SUB BX, AX
SBB CX, DX     ; ( X + Y)/W - S*Y (2分)
MOV Z, BX 
MOV Z+2, CX
```

---
## 9.28课后练习    
- P87,2-14(2), 写出实现下列计算的指令序列。（假定X、Y、Z、W、R都为有符号字变量）  
$Z = 2*（W-X）/（5*Y）$
- 参考答案
  ```
  MOV AX, W
  SUB AX, X   ; W-X,结果在AX中
  SAL AX,1    ; 2(W-X), 结果在AX中
  MOV BX, Y
  MOV CL, 2
  SAL BX, CL  ; 4Y
  ADD BX, Y   ; 5Y
  CWD         ; 2(W-X),扩展,结果在DX,AX中
  IDIV BX     ; 2(W-X)/(5Y),结果在AX中
  MOV Z, AX
  ```
  ```
  MOV  AX, W    
  SUB  AX, X   ;  W-X ,结果在AX中  
  SAL  AX, 1   ;  2（W-X ）,结果在AX中  
  MOV  BL, 5
  IDIV BL      ; 2(W-X)/5 ,结果在AL中  
  CBW
  CWD
  IDIV Y       ; 2(W-X)/5Y ,结果在AX中  
  MOV  Z, AX
  ```
- 8086乘除法指令不支持立即寻址
  - 如IMUL 2
    - 这条指令是错误的
- SAL
  - 算数左移指令
- 当移位指令移位次数>2时用CL
  - 移位指令第二位只能是1或者CL

---
## 2.7  8086/8088指令系统
### 2.7.3 逻辑运算类指令
#### 逻辑运算指令预习检测
- 1.已知$(AX)= 0FF60H，CF = 1。$
  ```
  MOV DX, 96
  XOR DH, 0FFH
  SBB AX, DX
  ```
  上述程序段执行后：（AX）= ?，CF = ?。
  - 答案:(AX) = 0 , CF = 0;
  - MOV DX,96
    - DX <- 60H
    - XOR DH,OFFH
    - 
    - **CF置零**
  -      

  -  XOR DX,96
    - XOR 96,96 = 0  

- 2.将CX寄存器低4位清零的正确指令是?
  - 答案:AND CX，0FFF0H

- 3.下列指令执行后既能使AX=0同时又使CF=0,OF=0的是?
  - 答案:XOR AX，AX

- 4.AND，OR，XOR，NOT为四条逻辑运算指令，下面的解释正确的是?
  - 答案:指令AND AX，OFH执行后，分离出AL低四位  

- 5.无论BH中原有的数是奇数或偶数，若要使BH中的数一定为奇数，应执行的指令是?
  - OR BH，01H

- 6.设AL=0AH，下列指令执行后能使AL=05H的是?
  - 答案:XOR AL，0FH 
  - NOT整体取反
    - NOT AL -> F5H

- 7.执行“and al,80h”指令后，可以肯定的执行结果是AL寄存器的?
  - 答案:A.低7位均为0

- 8.下列指令中，执行后对标志不发生影响的是
  - mov指令不影响标志位
---
#### 移位指令预习检测
- 1.将AX中有符号数除以2的正确指令是?
  -  SAR AX，1
  -  > 逻辑左移一位相当于无符号数乘以2  
     > 逻辑右移一位相当于无符号数除以2  
     > 算术左移一位相当于有符号数乘以2  
     > 算术右移一位相当于有符号数除以2    

- 2.算术右移指令SAR和逻辑右移指令SHR，两条指令执行结果完全相同的条件是?
  - 目的操作数最高位为0

- 3.下面两条指令执行后，DA2中两字节单元内容分别是?
    ```   
    DA1 EQU WORD PTR DA2
    DA2 DB OABH，OCDH
    SHL DA1，1
    SHR DA2，1
    ```
    - 2BH，9BH
    - .
  
- 4.下列指令执行后影响CF值的是?
  - SHL 
  - ![](https://codimd.s3.shivering-isles.com/demo/uploads/upload_aa2b4439d0be890688f80b159a73047c.png)

- 5.设CL＝8，AL=0C8H，执行SAR AL，CL后，AL中的数据是?
  - 0FFH
  - 每一动都在最高位补充符号位,总共八位移位八位高位补齐了1 

- 6.完成对CL寄存器的内容乘以4的正确操作是
```
SHL CL，1
SHL CL，1 
```

- 7.能将CF标志位移入AL最低位的指令是?
  - rcl al, 1
  - ![](https://codimd.s3.shivering-isles.com/demo/uploads/upload_f0f0c78a2ecb9ca925d127de42eba474.png)

- 8.SHL指令左移一位，就是乘10。
  - 错
  - *2 

---
## 2.8 转移指令与分支程序设计
### 转移指令1
- 1.​JA和JG指令的条件都是“大于”，所以是同一个指令的两个助记符。
  - (×) 
- 2.在双分支程序结构中，顺序执行的分支体最后需要JMP指令，目的是使第一个分支体执行结束之后，跳过第二个分支体，避免误入第二个分支体中。
  - (√) 
- 3.对无符号数和有符号数进行加减采用同样的指令，所以比较两者大小的条件转移指令也可以采用同样的指令。
  - (×)
- 4.执行JNS指令顺序执行的条件是SF＝1 。
  - (√) 
- 5.执行JNZ指令发生转移的条件是ZF＝1 。
  - (×) 
- 6.条件转移指令JC和JB虽然是两个助记符，但却是同一条指令。
  - (√) 
- 7.CS不变，只改变IP值，不能改变程序的执行顺序。
  - (×)
- 8.指令指针IP或者还包括代码段寄存器CS值的改变将引起程序流程的改变。
  - (√) 

--- 
### 转移指令2
- 1.转移指令JMP NEAR PTR PROCA的转移范围是?
  - 8000H～7FFFH
- 2.无条件转移指令JMP实现段间间接转移，转移的目标地址在?
  - 某个双字存储单元中
- 3必答 (单选题) 已知again是一个标号，则指令”jmp again”中，again不包含?
- byte或者dword类型
- 4.在一段顺序结构的程序中，不应该出现的指令是? 
  - jz
- 5.MASM中，实现段间转移的转移类型属性是?
  - FAR
- 6.使用CMP指令比较两个有符号数之后，程序希望“大于”时发生转移，则应该使用的条件转移指令是?
  - JG
- 7.当逻辑运算AND指令执行后，低8位结果中“1”的个数是零或偶数发生转移的指令是?
  - JP
- 8.JCXZ指令发生转移的条件是?
  - CX＝0
- 9.如果AX＝100、DX＝200时，执行“CMP AX, DX”指令，接着(   )条件转移指令会发生控制转移。
  - JB
- 10.条件转移指令JNBE产生转移的条件是（    ）
  - CF=0 AND ZF=0

---
## 10.5课后练习题
- ARRAY为数据段中定义的有符号字节数组，存放了100个字节数据。  试编写指令序列，统计ARRAY数组中正数、负数和0的个数，分别存放在PLUS、MINUS和ZERO三个字节变量中。
```
;个人答案:
        LEA SI,ARRAY
        MOV CX,100    
CYCLE:  MOV AL,[SI]
        CALL LES
        LOOP AGAIN
LES:    CMP AL,0
        JGE BIGER
        INC MINUS
        RET
BIGER:  JE OK
        INC PLUS
        RET
   OK:  INC ZERO
        RET
```
```
;老师的答案
      ;先将要用的变量清零
      XOR AL,AL     
      XOR PLUS,AL
      XOR MINUS,AL
      XOR ZERO,AL
      LEA SI,ARRAY  ;设置地址指针(SI:源变址寄存器)
      MOV CX,100    ;设置循环次数(CX:计数寄存器)
CHECK:MOV AL,[SI]   ;取出数组里的第一个数
      AND AL,AL
      JS MS         ;判断正负(SIGN=1是负数则转移)
      JZ ZO         ;判断0(ZERO=1是0则转移)
      INC PLUS      ;正数的个数
      JMP NEXT
  MS: INC MINUS     ;负数的个数,语句体2
      JMP NEXT
  ZO: INC ZERO      ;0的个数,语句体3
;SI取的时候ARRAY的首地址,本质上是ARRAY首地址的引用
;因此取数组中下一个数的操作可以是INC SI(SI=SI+1)
NEXT: INC SI        
      DEC CX        ;CX=CX-1,循环次数-1
;DEC指令影响ZF,下面循环结束判断直接判断ZF
      JNZ CHECK     ;当前ZERO!=0时跳转回CHECK
```
> 最好不用BP(基址指针寄存器)

```
;使用循环结构
      XOR AL,AL ;清零
      MOV PLUS,AL
      MOV MINUS AL
      MOV ZERO,AL
      LEA SI,ARRAY
      MOV CX,100 
CHECK:MOV AL.[SI]
      AND AL,AL
      JS MS     ;判断正负
      JZ ZO
      INC PLUS  ;正数的个数,语句体1
      JMP NEXT
  MS: INC MINUS ;负数的个数,语句体2
      JMP NEXT
  ZO: INC ZERO  ;0的个数,语句体3
NEXT: INC SI
      DEC CX
      JNZ CHECK
```
> DEC CX JNZ CHECK 等价于LOOP CHECK

---
# 第3章
## 3.3 循环程序设计
### 10.12 预习检测 循环控制1
- 1.循环控制指令LoopNZ/LoopNE控制循环继续执行的条件是?
  - CX≠0且ZF=0
- 2.使用LOOP指令控制计数循环，循环次数应赋予的寄存器是?
  - CX
- 3.若CX＝0，则语句“AGAIN: LOOP AGAIN”将会重复执行?次。 
  - $2^{16}$  
- 4.判断循环是否结束的循环控制部分只能安排在循环体之后。
  - ×
- 5.通常循环体中应该包含进行循环条件修改的代码。
  - √

---
## 3.4 子程序设计
### 10.14 预习检测 子程序1
- 1.设（SP）=0028H，执行段内返回指令RET 8后，SP的内容是?
  - 0032H
  - RET指针会使SP+2
  - 0028H+8+2=0032H
- 2.call指令执行后，堆栈的栈顶内容为?
  - call指令的下一条指令的地址
  - call指令利用堆栈保存地址,保存了call指令下条指令的地址
- 3.CALL指令的执行并不影响堆栈指针SP。
  - (×)
- 4.过程定义PROC是一条MASM伪指令。
  - (√)
- 5. 进入子程序后，将AX、BX、CX和DX按顺序压入堆栈，则子程序返回前弹出这些寄存器的顺序还是AX、BX、CX和DX。
  - (×)


---
### 子程序设计20201019
- 1.内存中在以BLOCK为首地址处存放100个无符号字节数。试编写一程序，求出该数组中的最大数与最小数的差，并将其送入RESULT单元，要求调用子程序来完成对最大数和最小数的求解。
```
DATA SEGMENT
  BLOCK DB 46,37,29,56,25,35,11,27,66,42,82,61
  COUNT EQU $-BLOCK
  RESULT DB 0
DATA ENDS
CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
  START:  MOV AX,DATA
          MOV DS,AX
          LEA SI, BLOCK
          MOV CX, COUNT
          CALL MAXMIN
          SUB AH,AL
          MOV RESULT, AH
  EXIT:   MOV AX, 4C00H
          INT 21H
  MAXMIN PROC
          MOV AH, 0 
          MOV AL, 255
  AGAIN:  MOV DL, [SI]
          CMP AL,DL
          JBE ABOVE
          MOV AL, DL      ; 小于当前最小值则替换
  ABOVE:  CMP AH, DL
          JAE BELOW
          MOV AH, DL      ; 大于当前最大值则替换
  BELOW:  INC SI
          LOOP AGAIN
          RET
  MAXMIN ENDP
CODEENDS
          END START
```



- 2.某年级参加英语4级考试的有250名学生，试编写一程序完成60-69，70-79，80-89，90-100四个分数段的统计工作，要求用子程序完成每个分数段的统计工作。
```
DATA SEGMENT
    BLOCK DB 66,75,89,62,77,82,95,73,99
    C60 DB 0  ; 60-70
    C70 DB 0  ; 70-80
    C80 DB 0  ; 80-90
    C90 DB 0  ; 90-100
DATA ENDS
CODE SEGMENT
  ASSUME CS:CODE, DS:DATA
  START:  MOV AX, DATA
          MOV DS, AX
          MOV CX, 4
          LEA DI, C60
          MOV AL, 60
  STATS:  LEA SI, BLOCK
          CALL COUNT
          MOV [DI], DL
          ADD AL, 10
          INC DI
          LOOP STATS
  EXIT:   MOV AX, 4C00H
          INT 21H
  COUNT PROC
          PUSH CX
          MOV CX, 15
          MOV DL, 0
          MOV AH, AL
          ADD AH, 9
          CMP AH, 99
          JNZ CONTIN
          INC AH
  CONTIN: CMP [SI], AL
          JB NEXT
          CMP [SI], AH
          JA NEXT
          INC DL
  NEXT:   INC SI
          LOOP CONTIN
          POP CX
          RET
  COUNT ENDP
  CODE ENDS
          END START
```


# 第4章 16位微处理器的外部特性
## 总线时序1
- 如果（AX）=1234H，（DX）=2000H，外设的访问速度足够快（不需要插入TW状态），则
  - 8086在指令“OUT   DX, AX”的执行阶段需要哪种总线周期操作？
    - 需要总线写周期操作
  - 在该总线周期的各个T状态，8086相关引脚输出的信息分别是什么？
    - $T_1$状态
      - $M/\bar{IO}$有效
        - 用来指出本次写周期是写存储器还是写外设,一直保持到&T_4$
      - 输出物理地址
      - 发出ALE地址锁存信号
      - $DT/\bar{R}$输出低电平
    - $T_2$状态
      - $\bar{WR}$有效
        - 代表写操作
      - 撤销地址信号
      - 在总线上输出16位数据1234H
      - 有效则对存储器或外设进行写操作,使数据收发器可以传输数据
    - $T_3$状态
      - 数据写入存储器
    - $T_4$状态
      - 撤销各控制及状态信号


---
# 第6章 微型计算机输入和输出技术


---
# 第8章 可编程接口芯片

---
## 8255练习1
- 设8255A的
  - A口接3个按键
  - B口接1个共阴极八段LED显示器
- 如下图所示。
  - 根据PA0～PA2引脚的输入状态让LED显示器显示对应的数字0～7。
- 设
  - 8255A的端口地址范围为60H～66H
    - 这里没有给出具体的四个地址所以这里最好选择间隔的地址60,62,64,66H
    - 选择60-63H也不为错
    > 只能选择错位相连的60,62,64,66H或者连续连接的60,61,62,63H 
  - 数字0～7的段选码依次放在数据段DATA自DUANXUAN开始的连续8个存储单元。
- 请编写实现上述功能的完整程序，初始化时无关项置0。

![](../res/img/Assembly/8255A练习1.png)

---
- 共阴极数码管
  - 高电位亮,低电位暗

![数码管字形码](../res/img/Assembly/数码管字形码.png)

- 数据段定义

```
data segment
  DUANXUAN db 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H  
  mesg1 db 0dh,0ah,'Input a num (0--9h):',0dh,0ah,'$'
data ends

```





---
- 各端口工作方式
  - A
    - 方式0输入
  - B
    - 方式0输出
- 方式控制字
  - $90H$
    - $10010000B$
    - | 1 | 00   | 1  | 0  | 0  | 0 | 0 | B |
      | - | -    | -  | -  | -  | - | - | - |
      |   | D6D5 | D4 | D3 | D2 | D1 | D0 |
      | 默认 | 方式0 | A口输入 |  C口上半无关,置零 | 方式0 | 端口B输出 | 端口C下半无关,置零 | 二进制 |

---
- 8255A端口地址为60H，61H，62H，63H,64H,65H,66H
- 初始化的程序段：
  ```
  mov dx,63h    ; 控制端口为63H
  mov al,90h    ; 方式控制字
  out dx,al     ; 或out 63h,al  送到控制端口
  ```

---
- 参考答案
```
; 数据段
DATA SEGMENT
        DUANXUAN DB 3FH,06H,5BH,4FH,66H,7DH,07H
DATA ENDS    
; 代码段
CODE SEGMENT
        ASSUME DS:DATA, CS:CODE     ; 段设定         
START:  MOV AX, DATA
        MOV DS, AX                  ; 装配数据段寄存器
        MOV AL, 10010000B（90H）  
        OUT 66H，AL                 ; 初始化(66H是控制端口)      
        MOV BX，OFFSET  DUANXUAN    ; 初始化段选码基址
LOP1：  IN  AL, 60H                 ; 读按键值 
        NOT AL   ; 这是取反(可要可不要)[只是影响电路可操纵的功能]
        AND AL, 07H                 ; 屏蔽高5位  
        XLAT                        ; 查段选码    
        OUT 62H, AL                 ; 输出段选码
        JMP LOP1                    ; 循环进行 
CODE ENDS
        END START

```

---
- 完整程序
```
data segment
  DUANXUAN db 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H  
  mesg1 db 0dh,0ah,'Input a num (0--9h):',0dh,0ah,'$'
data ends

code segment
  assume cs:code, ds:data
start:
  mov ax, data
  mov ds, ax
  mov dx, 63h     ; 控制端口为63H
  mov al, 90h     ; 方式控制字,均为方式0,A输入,B输出
  out dx, al      ; 或out 63h,al  送到控制端口

sss:
  mov dx, offset mesg1 ; 显示提示信息
  mov ah, 09h
  int 21h

  mov ah, 01      ; 从键盘接收字符
  int 21h

  cmp al, '0'     ; 是否小于0
  jb sss          ; 若是则退出
  cmp al, '7'     ; 是否大于7
  ja sss          ; 若是则退出

  and al, 0fh     ; 将所得字符的ASCII码减30H
  mov bx, offset DUANXUAN  ; bx为数码表的起始地址
  xlat            ; 求出相应的段码

  mov dx, 61H ; 从8255的B口输出
  out dx, al
  jmp sss         ;转SSS

exit:
  mov ax, 4c00h     ;返回DOS
  int 21h

code ends
  end start

```





---
```
data segment
  DUANXUAN db 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H  
data ends

code segment
  assume cs:code, ds:data
start:
  mov dx, 63h     ; 控制端口为63H
  mov al, 90h     ; 方式控制字,均为方式0,A输入,B输出
  out dx, al      ; 或out 63h,al  送到控制端口
  lea bx, DUANXUAN

sss:
  mov dx, 60h
  in al, dx
  and al, 07h
  alat

  mov dx, 61h
  out dx, al
  jmp sss

  mov ax, 4c00h
  in 21h

code ends
  end start

```


```
data segment
ioport equ 2400h-0280h
io8255a equ ioport+288h
io8255b equ ioport+28bh
led db 3fh,06h,5bh,4fh,66h,6dh,7dh,07h,7fh,6fh
mesg1 db 0dh,0ah,'Input a num (0--9h):',0dh,0ah,'$'
data ends
code segment
assume cs:code,ds:data
start:
mov ax,data
mov ds,ax
mov dx,io8255b ;使8255的A口为输出方式
mov ax,10000000b ;80h,A组方式0，A口输出，B组方式0，B口输出，C口输出
out dx,al
sss:
mov dx,offset mesg1 ;显示提示信息
mov ah,09h
int 21h
mov ah,01 ;从键盘接收字符
int 21h
cmp al,'0' ;是否小于0
jb sss ;若是则退出
cmp al,'9' ;是否大于9
ja sss ;若是则退出
and al,0fh ;将所得字符的ASCII码减30H
mov bx,offset led ;bx为数码表的起始地址
xlat ;求出相应的段码
mov dx,io8255a ;从8255的A口输出
out dx,al
jmp sss ;转SSS
exit:
mov ah,4ch ;返回DOS
int 21h
code ends
end start
```

---
## 8253A
- 1.(单选题)下列关于8253的说法中，错误的是（  ）
  - 8253的每个通道有4种工作方式
    - 8253/8254有6种工作方式，由方式控制字确定
  - 8253内部有3个独立的16位定时/计数器通道
  - 8253的定时/计数器通道可按照二进制和十进制两种方式计数
  - 8253的计数范围是1～65536
    - $2^16 = 65536$

- 2.(单选题) 8253A工作在**十进制**计数状态时，最大计数次数为（  ）
  - 10000

- 3.(单选题)  8253的各种工作方式中，在初始化编程时，写入控制字后，将使OUT端（  ）
  - 变为相应的高电平或低电平


- 4.(单选题) 要使8253达到最大计数次数，初始化时写入的初值应为（  ）
  - 0
  - 选择二进制时
    - 计数值范围：0000H～FFFFH
    - 0000H是最大值，代表65536
      - 全零计数开始-1就变成全1了
      - FFFFH计数开始-1就变成FFFEH了


- 5.(单选题) 若要在8253计数过程中读取当前计数值，则应该（  ）
  - 先发锁存命令，再读取计数值，计数通道会自动解除锁存状态


- 6.(单选题) 下列关于8253的说法中，正确的是（  ）
  - 8253有3个计数通道，但只有1个通道控制寄存器

- 7.(单选题) 8253的下列工作方式中可以通过门控信号GATE重复触发的方式为（  ）
  - 方式0
  - 方式1
  - 方式2
  - 方式3

- 8.(单选题) 在8253的下列工作方式中，能输出连续的周期性波形的工作方式是(      )
  - 方式2(速率发生器)    

- 9.(单选题) 8253的通道1无论工作在哪种方式下，在初始化编程时，写入控制字后，计数初值写入（  ）
  - 通道0
  - 通道1
  - 通道2
  - 控制端口

- 10.(单选题) 在8253中，用于启动或停止定时计数器工作的信号是（  ）
  - GATE


- 11.(单选题) 8253能够自动循环计数的工作方式为（  ）
  - 方式2和方式3

- 12.(单选题) 若对8253写入控制字的值为96H，则说明设定8253的（  ）
  - 计数器2工作在方式3且将只写低8位计数初值  


- 13.(单选题) 若8253A的计数器0工作在方式3（方波发生器），CLK端输入的脉冲频率是100kHz，当计数器初值为25时，OUT端输出方波高电平和低电平的宽度分别是（  ）
  - 130μs,120μs

- 14.(单选题) 8253的通道1为二进制计数，若CLK1的输入频率1MHz，OUT1的输出信号作为中断请求信号，则中断请求信号的最大间隔时间为（  ）
  - 10ms  
  - 65.535ms
  - 65.536ms 
  - 1s

- 15.(单选题) 8253的通道1为BCD计数，若CLK1的输入频率1MHz，OUT1的输出作为中断请求信号，则中断请求信号的最大间隔时间为（  ）
  - 10ms


- 16.(单选题) 8253的通道0与通道1级连，均为BCD计数，若CLK0的输入频率1MHz，OUT0的输出和CLK1相连，若OUT1作为中断请求信号，则中断请求信号的间隔时间最长为（  ）
  - 10ms
  - 1s
  - 100s
  - 4295s

---
## 8253初始化1
- 某系统中8253的地址范围是$0FFF8H$ ~ $0FFFEH$
  - 通道0工作在方式2
  - $CLK0=2MHz$
- 要求： 
  - OUT0输出1KHz的速率波；
  - 通道1工作在方式0，其CLK1为外部计数事件
    - 每计满100个，向CPU发出中断请求。
- 请编写通道0和通道1的初始化程序。

- 通道0工作在方式2,$n_0 = 2M / 1K = 2000$
- 通道1工作在方式0,

----
- 参考答案
```
  MOV DX, 0FFFEH
  ; 00(计数器0)11(先读低字节再读高字节)010(方式2),1(BCD码4计数)
  MOV AL, 00110101B       ; 0#初始化,BCD计数
  OUT DX, AL
  MOV AL, 01010000B
  OUT DX, AL
  MOV DX, 0FFF8H
  MOV AL, 2000H   
  OUT DX, AL
  MOV AL, AH
  OUT DX, AL
  MOV DX, 0FFFAH
  MOV AX, 100
  OUT DX, AL
```




---
  ```
  ; 通道0初始化
  MOV DX, 0FFFEH
  ; 00(计数器0)01(只读写低字节)010(方式2),0(二进制)
  MOV AL, 00010100B       ; 0#初始化,BCD计数
  OUT DX, AL
  MOV DX, 0FFF8H
  MOV AL, 02H   
  OUT DX, AL

  ; 通道1初始化
  MOV DX, 0FFFEH
  ;01(计数器1)11(先读低字节再读高字节)000(方式0)1(BCD)
  MOV AL, 01110001B 
  OUT DX, AL
  MOV DX, 0FFFAH
  MOV AL, 00H   ; 计数器1初始值低八位
  OUT DX, AL
  MOV AL, 01H   ; 计数器1初始值高八位
  OUT DX, AL
  ```

---
# 第10章 模-数和数-模转换技术

---
## DAC0832应用1
- 1.编写用8位D/A转换器DAC0832产生100个周期的三角波（不考虑信号的周期）的程序段。
- DAC0832工作于单缓冲方式
  - 输入寄存器的端口地址为`51H`
  - DAC寄存器处于直通状态
  - 转换公式为$Vo= — (D/256)×Vref，Vref= -5V$
    ![](../res/img/计算机网络/EX10.1.png) 

- 由于$Vo = - \frac{D}{256} \times Vref = \frac{5}{256} \times D = \frac{5}{256} \times (2^1 + ... + 2^7) = \frac{5}{256} \times 255 ≈ 5$

---
- 参考答案
```

```



---
- 个人
```
S0: MOV AL, 0     ; AL中置初值0
S1: CALL OUTPUT   ; 输出三角波的上升段
    INC AL
    JNZ S1
    DEC AL
S2: CALL OUTPUT   ; 输出三角波的下降段
    DEC AL        ; 产生下降段的一个值
    JNZ S2
    JMP S1        ; 下降段结束
                  ; 输出下一个三角波
OUTPUT PROC NEAR
        ......
        MOV DX, 51H
        MOV AL, 0
REPEAT: OUT DX, AL
        INC AL
        JMP REPEAT
        ......
        RET 
OUTPUT ENDP
```

---
## ADC0809应用1
- 在某微机应用系统中8255用作CPU与`ADC0809`的接口，系统的连线如图所示。
- 其中
  - `ADC0809`的`EOC`作为状态信号使用
  - `IN3`连接一个模拟信号源。
  - 8255A的基地址为$200H$。
- 试编写程序段，通过`0809`对`IN3`输入的模拟信号连续采样100次，将100次采样的平均值保存在`result`单元。

---
- 参考答案
```

```



----
```
DATA SEGMENT
  COUNT DB 99
  MIN DB 00H
  MAX DB 80H
DATA ENDS
CODE SEGMENT
  ASSUME CS:CODE, DS:DATA  
START:  MOV DX, PORT
        MOV AL, MIN
        DEC AL
UP:     INC AL
        OUT DX, AL
        CMP AL, MAX
        JB UP
DOWN:   DEC AL
        OUT DX, AL
        CMP AL, MIN
        JA DOWN
        DEC COUNT
        CMP COUNT 00H
        JNZ UP
CODE ENDS
        END START
```




---
# 综合练习题
- 仔细读下图给出的应用系统电路图，`8255`用作系统总线和`ADC0809`之间的接口电路，通过`8254计数通道0`输出周期为$1ms$的信号定时启动对`ADC0809模拟通道IN4`的`A/D`转换，`计数通道1`输出的信号用作`ADC0809`所需的$500KHz$时钟信号，`A/D`转换结束后通过`8259`的`IR2`向CPU发送中断请求。如果`8259`已经完成初始化，全嵌套、非自动中断结束方式，中断类型号为$80H$ ~ $87H$。请完成以下几个问题：   
![](../res/img/Assembly/综合练习题图1.png)

---
- (1).写出对8255A初始化的程序段（包括设定8255的方式选择控制字、选择ADC0809的模拟通道IN4，输出8254所需要的有效GATE信号）。

---
- (2).写出对8254初始化的程序段，输出A/D转换所需要的两个时钟信号

---
- (3).A/D转换结束后通过8259的IR2向CPU发送中断请求，产生的中断的类型号是多少？该中断源的中断向量放在内存中的什么位置？如果中断服务程序的入口地址为3210H：7880H，画出中断向量表中的相关存储空间内容。

---
- (4).根据（5）中编写的中断服务程序INTPROC，完成中断向量表的初始化，并开放8259的IR2。

---
- (5).编写完整的中断服务程序INTPROC，将模拟通道IN4的一次A/D转换结果读入内存字节变量Temp。