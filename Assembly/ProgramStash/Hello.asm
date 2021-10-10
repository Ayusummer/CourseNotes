; 输出 Hello, Assembly!
DSEG SEGMENT        ; 数据段开始
    STRING DB 0DH, 0AH, 'Hello, Assembly!', 0DH, 0AH, '$'   ; 0DH 回车  0AH  换行
DSEG ENDS           ; 数据段结束

CSEG SEGMENT        ; 代码段开始
    ASSUME CS:CSEG, DS:DSEG     ; 设定段寄存器与逻辑段的关系

START:  MOV AX, DSEG
        MOV DS, AX  ; 设置数据段段地址
        MOV DX, OFFSET STRING   ; 为 DOS 功能调用设置入口参数
        MOV AH, 9   ; 为 DOS 功能调用设置功能号(09: 显示字符串  DS:DX=串地址  '$'结束字符串)
        INT 21H     ; DOS 功能调用, 显示字符串
        MOV AX, 4C00H   ; 为 DOS 功能调用设置功能号和入口参数(4C: 带返回码(AL)结束  00:程序终止(同INT 20H))
        INT 21H     ; DOS 功能调用, 返回 DOS 操作系统
CSEG ENDS           ; 代码段结束
    END START       ; 汇编结束
