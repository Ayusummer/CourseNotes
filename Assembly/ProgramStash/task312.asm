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