; 习题-表达式计算1
; Z = 2 * (W - X) / (5 * Y) = 2 * (11-1) / (5*2) = 2
.model small
.stack
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