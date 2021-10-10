; 2.6.2.1-算术运算类指令-减法指令示例
.model small
.stack
.data
    ; X DD 778899AAH  ; 
    ; Y DD 9ABCDEF0H
    ; Z DD 56789ABCH
    ; W DD ?
    X DD 00000001H  ; 
    Y DD 00000002H
    Z DD 00000003H
    W DD ?
.code
START:  MOV AX, @DATA
        MOV DS, AX  ; 设置数据段段地址

        ; 将 X 存入 DX,AX
        MOV AX, WORD PTR X
        MOV DX, WORD PTR X+2
        
        ; X + Y
        ADD AX, WORD PTR Y      ; 先加低字
        ADC DX, WORD PTR Y+2 ; 再加高字 实现 X + Y 存放于 DX,AX

        ; X + Y + 24
        ADD AX, 24
        ADC DX, 0 ; X + Y + 24

        ; X + Y + 24 - Z
        SUB AX, WORD PTR Z
        SBB DX, WORD PTR Z+2 ; X + Y + 24 - Z

        ; w = X + Y + 24 - Z
        MOV WORD PTR W, AX
        MOV WORD PTR W+2, DX ; 结果存入W

        MOV AX, 4C00H   ; 为 DOS 功能调用设置功能号和入口参数(4C: 带返回码(AL)结束  00:程序终止(同INT 20H))
        INT 21H     ;DOS 功能调用, 返回 DOS 操作系统
    END START       ; 汇编结束