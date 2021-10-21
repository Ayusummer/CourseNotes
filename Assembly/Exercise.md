# 随堂练习

---

## 2021-9-6

1. 汇编语言的优点不包括（ C ）

   - A. 直接有效地控制硬件
   - B.生成的代码序列短小
   - C. 编程容易
   - D. 运行速度快
2. 8086处理器有20条地址线．可寻址访问的内存空间为（ B ）

   - A.1K
   - B.1M
   - C. 640K
   - D. 64K

   > $2^{20} B = 2^{10} KB = 1 MB$
   >
3. 由8086处理器组成的PC机的数据线是？（ A ）

   - A. 8条双向线
   - B. 8条单向线
   - C. 16条双向线
   - D. 16条单向线

   > 1 条总线可以给出 2 个不同的符号(0 和 1), 8086 的数据线为 16 位
   >

---

# 作业

---

## 数据表示 1

1. (单选题) 在机器数（  C ）中，对真值0的表示是唯一的。

   - A 原码
   - B 反码
   - C 补码
   - D 以上都不对

   > 原码反码中 0 都有 +0 与 -0 两种表示
   >
   > 补码中 +0 与 -0 的补码相同(均为全0), 多余的一个仅含最高位1的补码用于表示 $-2^n$
   >
   >> 例如 8位2进制码中 10000000 为 -128 的补码
   >>
   >
2. (单选题) 设计算机字长 8位，设x = -5, [x]补 为 ( A ) (单选）

- A FBH
- B FDH
- C FAH
- D 05H

> $[-5]_补 = ([-5]_原)_{求反} + 1 = (10000101)_{求反} + 1 = 11111010 + 1 = 11111011 = FBH$

3. (单选题) 十进制数-75用二进制数10110101表示，其表示方式是（   B   ）。

- A 原码
- B 补码
- C 反码
- D ASCII码

> $(-75)_原 = 1100 1011$
>
> $(-75)_反 = 1011 0100$
>
> $(-75)_补 = 1011 0101$

4. (单选题) 二进制数10101转换成十进制数是（   C   ）。

- A 25
- B 23
- C 21
- D 22

> $(10101)_2 = 2^0 + 2^2 + 2^4 = 21$

5. (单选题) 十进制负数-38的八位二进制补码是（    C  ）。

- A 01011011
- B 10100110
- C 11011010
- D 00100110

> $-38 = - (32 + 4 + 2) = (1010 0110)_原 = (1101 1001)_反 = (1101 1010)_补$

6. (单选题) 有一个八位二进制数补码是11111101，其相应的十进制数是 （     ）。

- A -3
- B -2
- C 509
- D 253

> $(1111 1101)_补 = (1111 1100)_反 = (1000 0011)_原 = -(2^0 + 2^1) = -3$

7. (单选题) 某计算机字长8位，机器数 11111111 对应的十进制真值不可能是（ D ）。（单选）

- A  -1
- B 127
- C 0
- D -128

> 8位二进制数能表示的真值范围为 -127 ~ + 127, "-0 的补码"用于表示 -128

8. (单选题) 主存储器是计算机系统的记忆设备，它主要用来（   C  ）。

- A 存放数据
- B 存放程序
- C 存放数据和程序
- D 存放微程序

9. (单选题) 关于补码机器数的描述中错误的是（ D ） （ 单选）

- A 数的符号用0和1表示
- B 数值“0”的表示唯一
- C 加法和减法按模进行运算
- D 不可能出现一个数的补码与其原码相同

> 正数的原码和补码相同

10. (单选题) 与十进制数56等值的二进制数是（    ）

- A 111000
- B 111001
- C 101111
- D 110110

> $56 = 32 + 16 + 8 = [0011 1000]_2$

---

## 寻址方式&数据传送 1

一. 单选题（共8题，49.6分）

1. (单选题)   有数据定义语句 `BUF DW 0ABH，1，10 DUP(3 DUP(1，0)，2)` 汇编后，为变量 `BUF` 分配的存储单元字节数是（ `C` ）

- A 48
- B 60H
- C 90H
- D 120

> `BUF` 是字类型(`DW`)变量,   `0ABH, 1` 2 个字; `10 DUP(3 DUP(1, 0), 2)` 70 个字, 总共 72 字, 占 144 字节
>
> 60 H = 96,  90 H = 144

2. (单选题)

```assembly
BUF1 DB 3 DUP(0, 2 DUP(1, 2), 3) 
COUNT EQU $ - BUF1 
```

符号 `COUNT` 等价的值是( `B` )

- A 6
- B 18
- C 16
- D 8

> `3 DUP(0, 2 DUP(1, 2), 3) = 3 DUP(0, 1, 2, 1, 2, 3)` 18 个字节
>
> `COUNT EQU $ - BUF1` 相当于求 `BUF1` 有多少字节

3. (单选题)  假设 `VAR` 为变量，指令 `MOV BX, OFFSET VAR` 的源操作数寻址方式是（ `A` ）

- A 立即寻址
- B 直接寻址
- C 间接录址
- D 存储器寻址

> `OFFSET VAR` 取出 `VAR` 的偏移地址立即数, 所以这里应该是立即寻址

4. (单选题)  下面两个传送指令语句中源操作数寻址方式是( `D` )

```assembly
VAR1 DW 32H 
VAR2 EQU 32H 
...
MOV AX, VAR1 
MOV BX, VAR2 
```

- A 都是立即数寻址
- B 都是直接寻址
- C 前一条指令是立即数寻址，后一条指令是直接寻址
- D 前一条指令是直接寻址，后一条指令是立即数寻址

> `VAR1` 是字变量, `MOV AX, VAR1` 是直接寻址
>
> `VAR2` 等价于 `32H`, 相当于一个立即数, `MOV BX, VAR2` 是立即寻址
>
> `EQU` 符号常量伪指令不会给符号分配存储单元, 要与变量定义伪指令相区别
>
> ![image-20211004163629154](http://cdn.ayusummer233.top/img/202110041636432.png)

5. (单选题) 指令 `mov [bx+8], ax` 的目的操作数采用（ `A`  ）寻址方式。

- A 寄存器相对
- B 存储器间接
- C 寄存器
- D 立即数

> 题干问目的操作数 `[bx+8]` 的寻址方式, 是寄存器相对寻址
>
> ![image-20211004164029308](http://cdn.ayusummer233.top/img/202110041640486.png)
>
> ![image-20211004164135263](http://cdn.ayusummer233.top/img/202110041641437.png)

6. (单选题)  指令 `mov ax, 2010`  的源操作数采用( `B` )寻址方式。

- A 直接
- B 立即数
- C 寄存器
- D 寄存器间接

> 2010 立即寻址
>
> ![image-20211004164637189](http://cdn.ayusummer233.top/img/202110041646352.png)

7. (单选题)  设物理地址 `(21001H)=20H,(21002H)=30H，(21003H)=40H`。如从地址 `21002H` 中取出一个字的内容是（ `D` ）

- A 2030 H
- B 3040 H
- C 3020 H
- D 4030 H

> 高高低低, 4030 H

8. (单选题)  源操作数采用存储器的直接寻址的指令是( `C` )（ `var`是一个变量）

- A `mov var, ax`
- B `mov cx,1234`
- C `mov bx, var+2`
- D `mov dx,offset var`

> ![image-20211004165209748](http://cdn.ayusummer233.top/img/202110041652934.png)
>
> ax 是寄存器寻址, 1234 是立即寻址, offset var 取出偏移地址也是立即寻址

二. 判断题（共8题，50.4分）
9. (判断题)  寄存器间接寻址方式，操作数是在某一寄存器中。`×`

> 寄存器间接寻址属于存储器寻址

10. (判断题)  立即数寻址只会出现在源操作数中。`√`

> ![image-20211004165630340](http://cdn.ayusummer233.top/img/202110041656509.png)
>
> 立即数无法作目的操作数因其不可变

11. (判断题) 指令 `lea ax,[bx+di+50]` 可以将 `BX＋DI＋50` 的结果传送给 `AX` 。 `√`
12. (判断题)  指令 `mov [si],[di]` 是错误的，因为8086系统不存在这种传送组合。 `√`

> ![image-20211004170259529](http://cdn.ayusummer233.top/img/202110041702651.png)
>
> MOV指令不支持两个存储器操作数

13. (判断题) 有符号数前面进行符号扩展，位数加长一位、数值增加一倍。`×`

> 有符号数符号位扩展不会改变数值大小, 高位扩展符号位

14. (判断题)  语句 `mov [bx], 250` 没有MASM语法错误。 `×`

> 两操作数类型不明确, 指令两端都可以自适应类型

15. (判断题)  汇编程序使用的保留字，例如寄存器名称等，是不能用作用户定义的标识符的。`√`
16. (判断题)  指令 `MOV AX,0` 使AX结果为0，所以标志 `ZF＝1`。`×`

---

## 表达式计算1

1. (简答题) 写出实现下列计算的指令序列。（假定X、Y、Z、W、R都为有符号字变量）

   $Z = 2 * (W - X) / (5 * Y)$

![image-20211009202515305](http://cdn.ayusummer233.top/img/202110092025495.png)

```assembly
.model small
.stack
; Z = 2 * (W - X) / (5 * Y) = 2 * (11-1) / (5*2) = 2
.data
    X DW 0001H  ; X = 1
    Y DW 0002H  ; Y = 2
    Z DW ?
    W DW 000BH  ; W = 11
    R DW ?      ; R 在算式里没出现,就写了个 0
.code
START:  MOV AX, @DATA
        MOV DS, AX  ; 设置数据段段地址

        ; W 存入 AX, 用于后面 - X 
        MOV AX, W
        ; W - X
        SUB AX, X
        
        ; 2 * (W - X) 算数左移 1 位就是 × 2
        SAL AX, 1

        ; Y 存入 BX, 用于后面 * 5
        MOV BX, Y
        ; 5 * Y = 4 * Y + Y
        MOV CL, 2
        SAL BX, CL
        ADD BX, Y


        ; 2 * (W - X) / (5 * Y)  即 AX / BX 要先将 AX 扩展到 DX,AX 再做除法, 商在 AX 里, 余数在 DX 里
        CWD
        IDIV BX

        ; Z = 2 * (W - X) / (5 * Y)
        MOV Z, AX

        MOV AX, 4C00H   ; 为 DOS 功能调用设置功能号和入口参数(4C: 带返回码(AL)结束  00:程序终止(同INT 20H))
        INT 21H     ;DOS 功能调用, 返回 DOS 操作系统
    END START       ; 汇编结束
```

---

## 汇编指令客观题 2

一. 单选题（共35题，100分）
1. (单选题) 转移指令JMP NEAR PTR PROCA的转移范围是（   ）
  - A 8000H～7FFFH
  - B 7FFFH～0FFFH
  - C 80H～7FH
  - D 0FH～7FH

> 



2. (单选题) 循环控制指令LoopNZ/LoopNE控制循环继续执行的条件是（  ）
  - A CX≠0且ZF=1
  - B CX≠0且ZF=0
  - C CX≠0或ZF=1
  - D CX≠0或ZF=0

> 

3. (单选题) 完成对CL寄存器的内容乘以4的正确操作是（    ）
A	ROL CL，1
ROL CL，1

B
MUL 4

C
SHL CL，1
SHL CL，1

D
MOV CL，2
SHL CL，CL

4. (单选题) 下面程序段完成测试DA-BYTE字节单元中数是否为负数，若是则将全1送DH中，否则全0送DH中，那么程序段中括号内应填的语句是（   ）
MOV CH,0

TEST DA-BYTE,80H

      （                       ）

MOV CH, 0FFH

ZERO:  MOV DH, CH

A
JNZ ZERO

B
JS ZERO

C
JZ ZERO

D
JC ZERO

5. (单选题) MOV AL，79
ADD AL，0B1H
上面指令执行后，设置的标志位 CF和OF的值是（ ）
A
CF=0，OF=0

B
CF=1，OF=1

C
CF=0，OF=1

D
CF=1，OF=0

6. (单选题) call指令执行后，堆栈的栈顶内容为（   ）
A
子程序的入口地址

B
call指令的下一条指令

C
call指令所在地址

D
call指令的下一条指令的地址

7. (单选题) 无论BH中原有的数是奇数或偶数，若要使BH中的数一定为奇数，应执行的指令是（ ）
A
ADD BH，01H

B
OR BH，01H

C
XOR BH，01H

D
TEST BH，01H

8. (单选题) 执行“and al,80h”指令后，可以肯定的执行结果是AL寄存器的( )。
A
低7位均为0

B
最高位为0

C
最高位为1

D
低7位均为1

9. (单选题) 已知again是一个标号，则指令”jmp again”中，again不包含(   )
A
byte或者dword类型

B
near或者far类型

C
逻辑地址

D
段内或者段间类型

10. (单选题) 指令“INC BYTE PTR [SI]”的操作数来自（ ）。
A
寄存器

B
立即数

C
外设端口

D
存储器

11. (单选题) 如果AX＝100、DX＝200时，执行“CMP AX, DX”指令，接着(   )条件转移指令会发生控制转移。
A
JA

B
JZ

C
JO

D
JB

12. (单选题) 将AX中有符号数除以2的正确指令是（ ）
A
SHR AX，1

B
SAR AX，1

C
ROR AX，1

D
RCR AX，1

13. (单选题) DA1 EQU WORD PTR DA2
DA2 DB OABH，OCDH
    ┇
SHL DA1，1
SHR DA2，1
上述两条指令执行后，DA2中两字节单元内容分别是(    )
A
0ABH，0CDH

B
2BH，9BH

C
4DH，57H

D
56H，9BH

14. (单选题) 指令（ ）实现对AX当中D15和D0位求反，其他位不变的功能。
A
and ax,7ffeh

B
xor ax,8001h

C
or ax,8001h

D
not ax

15. (单选题) 设AL=0AH，下列指令执行后能使AL=05H的是（ ）
A
NOT AL

B
AND AL，0FH

C
XOR AL，0FH

D
OR AL，0FH

16. (单选题) 下列指令执行后既能使AX=0同时又使CF=0,OF=0的是（ ）
A
XOR AX，AX

B
AND AX，AX

C
OR AX，AX

D
TEST AX，0

17. (单选题) 检查2个无符号数的关系，若要实现AL≥BL时分支去LOP1处，那么在“CMP AL，BL”指令后应跟的分支指令是(   )
A
JNC LOP1

B
JA LOP1

C
JC LOP1

D
JGE LOP1

18. (单选题) JCXZ指令发生转移的条件是(   )
A
CX≠0

B
CX＝0

C
ZF＝0

D
ZF＝1

19. (单选题) 使用LOOP指令控制计数循环，循环次数应赋予的寄存器是（  ）
A
AX

B
BX

C
CX

D
DX

20. (单选题) 已知AX，BX中均为带符号数，当进行字相除时，下面指令或指令序列正确的是( )
A
DIV BX

B
CWD
IDIV BX

C
XOR DX，DX
DIV BX

D
CBW
IDIV BX

21. (单选题) DA1 DW 2A05H
DA2 DB 0FAH
┇
MOV AL，BYTE PTR DA1
SUB DA2，AL
上述指令执行后，DA2中的内容是（ ）
A
0DAH

B
0FAH

C
0F5H

D
0D0H

22. (单选题) 若CX＝0，则语句“AGAIN: LOOP AGAIN”将会重复执行（  ）次。
A
 2的15次方

B
0

C
1

D
2的16次方

23. (单选题) 下面程序片段条件转移语句发生跳转的条件是AL＝（   ）
cmp al,0fbh

jnl next

A
80h

B
0ffh

C
8fh

D
0f0h

24. (单选题) AND，OR，XOR，NOT为四条逻辑运算指令，下面的解释正确的是( )
A
指令XOR AX，AX执行后，AX内容不变，但设置了标志位.

B
指令OR DX，1000H执行后，将DX最高位置1，其余各位置0

C
指令AND AX，OFH执行后，分离出AL低四位

D
NOT AX，执行后，将AX清0

25. (单选题) 将CX寄存器低4位清零的正确指令是（ ）
A
AND CX，0F0H

B
AND CX，0FFF0H

C
AND CX，1110H

D
MOV CX，0

26. (单选题) 在一段顺序结构的程序中，不应该出现的指令是（   ）
A
div

B
add

C
mul

D
jz

27. (单选题) 设（SP）=0028H，执行段内返回指令RET 8后，SP的内容是(  )
A
0036H

B
0038H

C
0032H

D
0020H

28. (单选题) 已知（AX）= 0FF60H，CF = 1。
                 MOV   DX, 96
                 XOR   DH, 0FFH
                 SBB   AX, DX
    上述程序段执行后：（AX）=________，CF =________。
    A
    0FFFFH    0

B
0    0

C
0FFFFH    1

D
0     1

29. (单选题) 若AX= - 15要得到AX=15应执行的指令是( )
A
NEG AX

B
NOT AX

C
INC AX

D
DEC AX

30. (单选题) 下列指令执行后既能使AX=0同时又使CF=0,OF=0的是（ ）
A
XOR AX，AX

B
AND AX，AX

C
OR AX，AX

D
TEST AX，0

31. (单选题) MASM中，实现段间转移的转移类型属性是（    ）
A
SHORT

B
NEAR

C
FAR

D
PTR

32. (单选题) 使用CMP指令比较两个有符号数之后，程序希望“大于”时发生转移，则应该使用的条件转移指令是（    ）
A
JA

B
JG

C
JC

D
JB

33. (单选题) 能将CF标志位移入AL最低位的指令是：( )。
A
rcr al, 1

B
ror al, 1

C
rol al, 1

D
rcl al, 1

34. (单选题) 下列指令执行后影响CF值的是（ ）
A
DEC

B
XCHG

C
LEA

D
SHL

35. (单选题) 执行指令“push ax”后、接着执行指令“pop dx”，其功能与（ ）相同。
A
mov ax, dx

B
mov dx, ax

C
xchg ax, dx

D
xchg dx, ax

---

## 分支程序设计 2

试编程实现：从键盘输入一个字符，若是数字，放入 `DIGITAL` 单元，若是英文字母，放入 `ENGLISH` 单元，其它字符，则放入 `OTHER` 单元。

分解题意:

- 从键盘输入一个字符:  `AH = 01H` 输入字符以 ASCII 码的形式存入 `AL` 

  ![image-20211021140956845](http://cdn.ayusummer233.top/img/202110211410241.png)	

- 若是数字，放入 `DIGITAL` 单元，若是英文字母，放入 `ENGLISH` 单元，其它字符，则放入 `OTHER` 单元。

  - 数据段定义 3 个包含一个数据的字节变量

    -  `DIGITAL`   `ENGLISH`  `OTHER` 
    - 字节变量: ASCII 码是一个字节
    - 一个数据: 题设中键盘上只输入一个字符

    ```assembly
    DIGITAL DB ?
    ENGLISH DB ?
    OTHER DB ?
    ```

  - 输入的字符以 ASCII 码的形式传入 `AL`, 数字(0~9)的 ASCII 码为 `30H ~ 39H`, 英文字母为 `大写字母: 41H ~ 5AH`, `小写字母: 61H ~ 7AH` 

    分支可以从 ASCII 码大小入手进行切分, 首先明确的是跳转到的分支总共有三个, 分别对应三类字符的存放, 然后就是判断何时进行分支跳转, 从上述 ASCII 码区别来看, 可以在 `30H 39H 41H 5AH 61H 7AH` 6 处利用 `CMP` 进行判断然后跳转相应分支

- ![task312](http://cdn.ayusummer233.top/img/202110211500493.png)

- ```assembly
  ; 分支程序设计 2
  ; 试编程实现：从键盘输入一个字符，若是数字，放入DIGITAL单元，
  ;            若是英文字母，放入 ENGLISH 单元，其它字符，则放入 OTHER 单元。
  .MODEL SMALL
  .STACK
  .DATA
      DIGITAL DB ?
      ENGLISH DB ?
      OTHER DB ?
  .CODE
  START:  MOV AX, @DATA
          MOV DS, AX
  
          MOV CX, 3       ; 为了方便调试所以一次性完成三次判断
  
  ONE:    MOV AH, 1
          INT 21H         ; 输入一个字符以 ASCII 码形式送入 AL
  
          CMP AL, 30H
          JB S_OTHER      ; AL BELOW 30H 说明其为其他字符
          CMP AL, 3AH
          JB S_DIGITAL    ; 30H <= AL BELOW 3AH 则其为数字
          CMP AL, 41H
          JB S_OTHER      ; 3AH <= AL < 41H 则其为其他字符
          CMP AL, 5BH
          JB S_ENGLISH    ; AL ∈ [41H, 5AH] 为大写字母
          CMP AL, 61H
          JB S_OTHER      ; AL ∈ [5BH, 60H] 为其他字符
          CMP AL, 7BH     
          JB S_ENGLISH    ; AL ∈ [61H, 7AH] 为小写字母
          JMP S_OTHER     ; 除此之外都算其他字符
  
  S_DIGITAL:  MOV DIGITAL, AL
              JMP NEXT    ; 三段分支是独立的, 所以要无条件跳转到 NEXT
  S_ENGLISH:  MOV ENGLISH, AL
              JMP NEXT
  S_OTHER:    MOV OTHER, AL
  
  NEXT:   LOOP ONE
          MOV AX, 4C00H
          INT 21H
  
      END START
  ```

