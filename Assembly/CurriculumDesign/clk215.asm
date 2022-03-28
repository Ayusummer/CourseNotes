.MODEL	TINY		
	PA_8255		EQU	0270H      	; 8255端口     
	PB_8255		EQU	0271H
	PC_8255		EQU	0272H
	CTRL_8255	EQU	0273H

	PA_8253 	EQU 0260H		; 8253端口
	PB_8253 	EQU 0261H
	PC_8253 	EQU 0262H
	CTRL_8253 	EQU 0263H
		
	EVEN_8259	EQU 0250H		; 8259端口
	ODD_8259	EQU 0251H
	
.STACK	100

.DATA   
	BUFFER      DB 00H, 00H, 11H, 00H, 00H, 11H, 00H, 00H
	KEY_VALUE	DB -1
	STOP		DB 0			; 启停时间标志，0FFH表示停止
	C8			DB 8
	C10			DB 10
	
	HOUR		DB 00			; 保存当前时
	MINUTE      DB 00			; 保存当前分
	SECOND 		DB 00      		; 保存当前秒

	CLOCK_HOUR	DB 2 DUP (?)	; 保存设置闹钟的时
	CLOCK_MIN	DB 2 DUP (?)  	; 保存设置闹钟的分
	CLOCK_SEC	DB 2 DUP (?)	; 保存设置闹钟的秒
	NUM 		DB 0
	SEC_TEMP    Dw 0
	CLOCK_FLAG	DB 0			; 是否设置闹钟标志,大于等于1表示设置了闹钟
	CLOCK_TIME	DB 0			; 控制闹钟时间
	ALARM		DB 0			; 闹钟是否到来标志
	BITCODE		DB ?			; 位码
	SEG_TAB		DB 0C0H, 0F9H, 0A4H, 0B0H, 99H, 92H, 82H, 0F8H    
				DB 080H, 90H, 88H, 83H, 0C6H, 0A1H, 86H, 8EH, 0FFH, 0BFH

.CODE
	START:  	
				MOV AX, @DATA
				MOV DS, AX
				NOP
				CALL INIT_8255			; 初始化8255
				CALL INIT_8253	    	; 初始化8253
				CALL SET_VECTOR      	; 设置中断向量
				CALL INIT_8259       	; 初始化8259

				MOV	AL, 11111110B    	; 开放IR0请求的屏蔽位
				MOV DX, ODD_8259
				OUT	DX, AL
				STI                 	; 开中断	        	
	
	BEGIN:							; 踏步等待中断
				CALL CONVERT		; 将HOUR,MINUTE,SECOND转化成显示缓冲区的每一位
				CALL DISP 	   		; 显示   
				CALL SCAN			; 扫描按键
				CALL KEY_DO			; 执行相应的按键事件
				CALL TELL_TIME		; 整点报时
				
				CMP	 CLOCK_FLAG, 1	; 比较是否设置了闹钟
				JB	 BEGIN
				CALL ALARM_CLOCK	; 是否到达闹钟时间
	        	JMP	 BEGIN			; 主程序循环
	        	MOV  AX, 4C00H
	        	INT  21H
	        		
;------------------------------------------------------------------------------------------------------------------	        		
	
	;--------------------------中断服务程序-------------------------------------------------	
	INTRPROC  PROC  FAR		; 中断服务程序
				PUSH AX            			; 保护现场
				PUSH DS
				PUSH DX
				MOV  AX, SEG SECOND
				MOV	 DS, AX
		;---------------------------------------------------------------
		SECINC: 
		        INC	SEC_TEMP
                CMP	SEC_TEMP, 100
                JNZ	OVER3
                MOV	SEC_TEMP, 0
                INC SECOND          ; 秒钟加1
                CMP SECOND, 60      ; 判断秒钟是否等于60
                JZ	ADD_MINUTE		; 达到60则分钟加1
				JMP OVER
		;--------------------------------------------------------------
		ADD_MINUTE:
	  			MOV  SECOND, 0		; 秒钟清零
	  			INC  MINUTE			; 分钟加一
	  			CMP	 MINUTE, 60		; 判断分钟是否达到60
	  			JZ	 ADD_HOUR		; 达到60则时钟加1
	  			JMP	 OVER
		;---------------------------------------------------------------
		ADD_HOUR:
				MOV	 MINUTE,0		; 分钟清零
				INC  HOUR			; 时钟加1
				CMP	 HOUR, 24
				JZ	 RSTART			; 达到24
				JMP	 OVER
		;---------------------------------------------------------------
		RSTART:
				MOV	HOUR, 0			; 时钟清零
		;---------------------------------------------------------------
		OVER:
					CLI				; 关中断，准备返回
	        		CMP  ALARM, 1	; 判断闹钟是否到来
	        		JNZ	 OVER3
	        		INC	 CLOCK_TIME	; 是则闹钟时间加1
	 	;---------------------------------------------------------------
	 	OVER3:
	        		MOV  AL, 20H
	        		MOV  DX, EVEN_8259		; 发送EOI命令
	        		OUT	 DX, AL
	        		POP	 DX
	        		POP	 DS              	; 恢复现场
	        		POP  AX         
	        		IRET                   	; 中断返回
	INTRPROC  ENDP
	
	;-------------------------产生100MS的延时，用于蜂鸣报时---------------------------------------
	DL100MS  PROC  NEAR		; 产生100MS的延时，用于蜂鸣报时
				PUSH CX
				MOV	 CX, 30
				LOOP $
				POP	 CX
				RET
	DL100MS  ENDP
	
	;-------------------------------------------------------------------------------------
	DL1MS  PROC  NEAR		; 产生1MS的延时	
				PUSH CX
				MOV	 CX, 500
				LOOP $		; 显示对应存储单元地址，与位置无关
				POP	 CX
				RET
	DL1MS  ENDP
	;------------------------------------------------------------------------------------

		;---------------更新HOUR,MINUTE,SECOND------------------------------------
	UPDATE_TIME	PROC NEAR		; 更新HOUR,MINUTE,SECOND
				PUSH SI
				LEA	 SI, BUFFER
				MOV	 BL, [SI]	; 先保存秒钟的个位至BL
				INC	 SI			; 移动指针至秒针的十位
				MOV	 AH, 0
				MOV	 AL,[ SI]	; 秒钟的十位送入AL
				MUL	 C10
				ADD	 AL, BL
				MOV	 SECOND, AL	; SECOND=十位*10+个位
				INC	 SI
				INC	 SI			; 跳过中间的‘-’
				MOV	 BL, [SI]	; 先保存分钟的个位至BL
				INC	 SI			; 移动指针至分钟的十位
				MOV	 AH, 0
				MOV	 AL, [SI]	; 分钟的十位送入AL
				MUL	 C10
				ADD	 AL, BL
				MOV	 MINUTE, AL	; MINUTE=十位*10+个位
				INC	 SI
				INC	 SI			; 跳过中间的‘-’
				MOV	 BL, [SI]	; 先保存时钟的个位至BL
				INC	 SI			; 移动指针至时钟的十位
				MOV	 AH, 0
				MOV	 AL, [SI]	; 时钟的十位送入AL
				MUL	 C10
				ADD	 AL, BL
				MOV	 HOUR, AL	; HOUR=十位*10+个位
				POP			SI
				RET
	UPDATE_TIME	ENDP

	;-------------------------------------扫描键盘子程序-------------------------------------
	SCAN  PROC  NEAR	;扫描键盘子程序
				PUSH BX
				PUSH DX
				CALL ALLKEY			; 粗扫描
				JNZ	 ALLKEY_AGAIN	; 如果检测到有键按下，再次粗扫描
				JMP	 SCAN_OVER		; 否则扫描结束
	;----------------------------------------------------------------------
	ALLKEY_AGAIN:
				CALL DL1MS
				CALL ALLKEY			; 再次粗扫描
				JNZ	 GETKEY			; 检测到真的有键按下，转去执行细扫描
				JMP	 SCAN_OVER		; 否则扫描结束
	;----------------------------------------------------------------------
	GETKEY:
				MOV	 BX, -1			; 累加器
				MOV  AH, 0FEH       ; 指定列码，从PB0列开始细扫描
				MOV  CX, 8          ; 最多扫描8列	
	;----------------------------------------------------------------------
	NEX:
				INC  BX
				MOV  AL, AH
				ROL  AH, 1           ; 形成下一行的行码
				MOV  DX, PB_8255
				OUT  DX, AL            
				MOV  DX, PC_8255
				IN 	 AL, DX          ; 读取列码到AL里
				NOT	 AL			
				AND	 AL, 03H				
				LOOPZ NEX
				DEC 		AL
				MUL	 C8
				ADD	 AL, BL			; 读取到的数字存放在AL里
				MOV	 BL, AL			; 保存至BL
				MOV	 DX, PB_8255 
				MOV	 AL, 0 
				OUT  DX, AL			; B端口输出全0
				MOV  DX, PC_8255
		;-----------------------------------------------------------------
		WAIT2:
				IN   AL, DX				; 读列码
				AND  AL, 03H			; 保留低两位
				CMP	 AL, 03H			; 非全1，表示未释放
				JNZ	 WAIT2				; 继续等待
				MOV  AL, BL				; AL恢复按键数值
				MOV	 KEY_VALUE, AL
				JMP	 SCAN_OVER2
		;------------------------------------------------------------------
		SCAN_OVER:
				MOV  AL,-1				; 若没有按键，AL赋值-1
		;-----------------------------------------------------------------
		SCAN_OVER2:
				POP	 DX
				POP	 BX
				RET
	SCAN ENDP
	
	;-----------------------------键盘粗扫描--------------------------------------------
	ALLKEY	PROC  NEAR            		;键盘粗扫描 
				MOV	 DX, PB_8255                                                
				XOR	 AL, AL                                      
				OUT	 DX, AL		 		; 行输出全零
				MOV  DX, PC_8255                                           
				IN	 AL, DX		 		; 读列码
				NOT	 AL
				AND	 AL, 03H		
				RET
	ALLKEY	ENDP
	     
	;------------------------------------------------------------------------------------
	CONVERT	 PROC  NEAR			; 将HOUR,MINUTE,SECOND转换至个位，十位
				LEA	 SI, BUFFER
				MOV	 AH, 0
				MOV  AL, SECOND		; 转换秒
				DIV	 C10			
				MOV  [SI], AH		; 保存秒钟个位
				INC  SI
				MOV	 [SI], AL		; 保存秒钟十位
				INC	 SI
				INC	 SI				; 跳过‘-’
				MOV	 AH, 0
				MOV	 AL, MINUTE		; 转换分
				DIV	 C10
				MOV	 [SI], AH		; 保存分钟个位
				INC	 SI
				MOV	 [SI], AL		; 保存分钟十位
				INC	 SI
				INC  SI				; 跳过‘-’
				MOV	 AH, 0
				MOV	 AL, HOUR		; 转换时
				DIV	 C10
				MOV	 [SI], AH		; 保存时钟个位
				INC	 SI
				MOV	 [SI], AL		; 保存时钟十位
				RET
	CONVERT	 ENDP   

	;----------------------8255初始化------------------------------------------	
	INIT_8255  PROC  NEAR		; 8255初始化
				PUSH DX
				PUSH AX
	       	    MOV	 DX, CTRL_8255	; 8255控制口
				MOV	 AL, 81H        ; A,B输出。C高位输出，低位输入
				OUT	 DX, AL			
				MOV  AL, 0FH		; 00001111，通过PC7产生蜂鸣
				OUT	 DX, AL			; PC7置位，即不产生蜂鸣，控制闹钟
				MOV	 AL, 0DH		; 00001101，通过PC6产生蜂鸣
				OUT	 DX, AL			; PC6置位，即不产生蜂鸣，控制报时
				POP			AX
				POP			DX
				RET
	INIT_8255  ENDP

	;-------------------------8253初始化-----------------------------------------	
	INIT_8253  PROC  NEAR		; 8253初始化
				PUSH AX
				PUSH DX
				MOV  AL, 34H		; 00110100,计数器0，方式2，二进制	
				MOV  DX, CTRL_8253
				OUT  DX, AL
				MOV  AX, 1953		; 写入计数值1953，外接频率1953HZ，产生1S的中断
				MOV  DX, PA_8253
				OUT  DX, AL			; 先写低位
				MOV  AL, AH
				OUT  DX, AL			; 再写高位
				POP  DX
				POP  AX
				RET
	INIT_8253  ENDP
	        	
	;---------------------------设置中断向量-----------------------------------------
	SET_VECTOR  PROC  NEAR		; 设置中断向量
				PUSH AX
				PUSH BX
				MOV  AX, 0
				MOV	 ES, AX     	; 中断向量表段基址为0000H
				MOV	 BX, 40H*4      ; BX中预置中断向量地止，中断类型号为40H
				MOV	 AX, OFFSET INTRPROC	; 向量表中低地址存放偏移地址，
				MOV	 ES:[BX], AX
				MOV	 AX, SEG INTRPROC
				MOV	 ES:[BX+2], AX          ; 向量表中高地址存放段基地址
				POP  BX
				POP	 AX
				RET
	SET_VECTOR  ENDP
	
	;-------------------------;8259初始化--------------------------------------------
	INIT_8259  PROC  NEAR		; 8259初始化
				PUSH AX
				PUSH DX
				MOV	 AL, 13H                	; ICW1:边沿触发，单片系统，需要ICW4
				MOV	 DX, EVEN_8259
				OUT	 DX, AL
				MOV	 AL, 40H                	; ICW2:类型号从40H开始
				MOV  DX, ODD_8259
				OUT	 DX, AL
				MOV  AL, 01H                	; ICW4:完全嵌套方式，非缓冲，非自动结束
				MOV  DX, ODD_8259
				OUT  DX, AL  
				POP	 DX
				POP	 AX
				RET
	INIT_8259  ENDP     

	;---------------------------显示时间子程序-------------------------------  	
	DISP PROC NEAR		; 显示时间子程序
				PUSH SI
				PUSH CX
				PUSH BX
				LEA  BX, SEG_TAB	; BX置为段码表首址
				MOV  BITCODE, 0FEH	; 位码初始值11111110，从最右边开始
				MOV  SI, 0			; SI用作输出缓冲区指针，初值0
				MOV  CX, 8
		;------------------------------------------------------------
		ONE1:
				MOV  AL, BUFFER[SI]	; 取出一个待输出数字
				XLAT				; 转换成七段码
				MOV  DX, PA_8255
				OUT  DX, AL			; 输出段码
				MOV  AL, BITCODE
				MOV  DX, PB_8255
				OUT  DX, AL			; 输出位码
				CALL DL1MS
				ROL  BITCODE,1		; 修改位码，得到下一个位码
				INC  SI				; 修改指针
				LOOP ONE1			; 循环，点亮下一个LED
		  		CALL DELE
				POP	 BX
				POP	 CX
				POP	 SI
				RET
		;--------------------------------------------------------------
	DISP ENDP

	;------------------------------------------------------------------
	DELE PROC NEAR
				PUSH AX
				PUSH DX
				MOV	 AL, 0FFH
				MOV	 DX, PA_8255
				OUT	 DX, AL
				MOV	 DX, PB_8255
				OUT	 DX, AL
				NOP
				POP	 DX
				POP	 AX
				RET
	DELE ENDP

		;----------------------相应的按键处理事件--------------------------------
	KEY_DO PROC NEAR	; 相应的按键处理事件
				CMP  AL, -1	
				JZ 	 DONE		; 键值为1，则无键按下
				CMP	 AL,0FH		; 否则判断是否是F键按下
				JNZ	 IS_E       ; 若不是，继续判断是否是E键
				CALL F_KEY		; 若是F键，则执行相应事件
				JMP	 DONE
		;------------------------------------------------------------
		IS_E:
				CMP  AL, 0EH
				JNZ	 IS_D		; 若不是E键，则继续判断是否是D键
				CALL E_KEY		; 若是E键，执行控制闹钟的子程序
				JMP	 DONE
		;---------------------------------------------------------------
		IS_D:
				CMP	 AL,0DH
				JNZ	 IS_C		; 若不是D键，则继续判断是否是C键
				CALL D_KEY		; 若是D键，则执行设置闹钟的子程序
				JMP	 DONE
		;---------------------------------------------------------------
		IS_C:
				CMP	 AL,0CH			
				JNZ	 DONE		; 若不是C键，则结束
				CALL C_KEY 		; 若是C键，则执行设置时间的子程序
				JMP	 DONE
		;---------------------------------------------------------------
		DONE:				
				RET
	KEY_DO	ENDP

	;-------------------------------------------C时钟设置--------------------------------------------
	C_KEY PROC NEAR		; 执行C键，设置显示时间
				CLI					; 关中断
				NOT  STOP			; 给外部设备足够的响应时间；或是软件的延时
				LEA	 SI, BUFFER
				MOV	 CX, 8
		;--------------清除显示缓冲区-------------------------
		CLE:	; 清除显示缓冲区							
				MOV	 AL, 11H
				MOV	 [SI], AL
				INC  SI
				LOOP CLE
				DEC	 SI
		;--------------设置时钟的十位-------------------------
		H1:		;设置时钟的十位
				CALL DISP
				CALL SCAN
				CMP	 AL, -1
				JZ	 H1
				CMP	 AL, 3			; 时钟的十位必须小于3？
				JNB	 H1				; 若不是，则重新扫描
				MOV	 [SI], AL		; 键值保存到显示缓冲区
				MOV	 BL, AL			; 保存至BL以便于下面判断时钟的个位
				CALL DISP
				DEC	 SI
		;-----------------设置时钟的个位--------------------------
		H0:		; 设置时钟的个位
				CALL DISP
				CALL SCAN
				CMP	 AL, -1
				JZ	 H0
				CMP	 BL, 2			; 判断时钟的十位是否为2
				JNZ	 A				; 不为2
				CMP	 AL, 4
				JNB	 H0
		;------------判断时钟的个位是否小于10------------------------------------
		A:		; 判断时钟的个位是否小于10
				CMP  AL, 10
				JNB	 H0				; 大于等于10，继续扫描
				MOV	 [SI], AL		; 否则保存至缓冲区
				CALL DISP
				DEC	 SI
				DEC	 SI
		;-------------设置分钟的个位-------------------------------------------
		M1:		; 设置分钟的个位
				CALL DISP
				CALL SCAN
				CMP	 AL, -1
				JZ	 M1
				CMP	 AL, 6			; 判断是否大于等于6
				JNB	 M1				; 是则继续扫描
				MOV	 [SI], AL		; 否则保存至缓冲区
				CALL DISP
				DEC	 SI
		;----------------设置分钟的个位----------------------------------------
		M0:		; 设置分钟的个位
				CALL DISP
				CALL SCAN
				CMP	 AL, -1
				CMP	 AL, 10			; 判断是否大于等于10
				JNB	 M0				; 是则继续扫描
				MOV	 [SI], AL		; 否则保存至缓冲区
				CALL DISP
				DEC	 SI
				DEC  SI
		;-------------------设置秒钟的十位--------------------------------------
		S1:		; 设置秒钟的十位
				CALL DISP
				CALL SCAN
				CMP	 AL, -1
				JZ	 S1
				CMP	 AL, 6			; 判断是否大于等于6
				JNB	 S1				; 是则继续扫描
				MOV	 [SI], AL		; 否则保存至缓冲区
				CALL DISP
				DEC  SI
		;--------------------设置秒钟的个位-------------------------------------
		S0:		; 设置秒钟的个位
				CALL DISP
				CALL SCAN
				CMP  AL, -1
				JZ	 S0
				CMP	 AL, 10			; 判断是否大于等于10
				JNB	 S0				; 是则继续扫描
				MOV	 [SI], AL		; 否则保存至缓冲区
				
				CALL DISP
				CALL UPDATE_TIME	; 将缓冲区的值保存至HOUR,MINUTE,SECOND
				CALL CONVERT		; 更新显示缓冲区为设置时间
				CALL DISP			; 重新显示

				RET
	C_KEY ENDP	

	;--------------------------------------F启停键-----------------------------------------
	F_KEY PROC NEAR		; 执行F键，控制时间
				NOT	 STOP			; 标志位取反
				CMP	 STOP, 0FFH		; 判断STOP为0FFH？
				JZ	 STOP_TIME		; 若是，则关中断，停止时间
				STI					; 否则需要再次开中断
				JMP	 F_OVER				
		;-------------------------------------------------------
		STOP_TIME:				
				CLI		; 关中断
		;-------------------------------------------------------
		F_OVER:
				RET
	F_KEY ENDP


	;----------------***整点报时子程序***------------------------    	
	TELL_TIME PROC NEAR				; 整点报时子程序
				CMP	 MINUTE, 59		; 判断分钟是否达到59
				JB	 NEXT			; 若小于59，继续判断
				CMP	 SECOND, 55		; 否则判断秒钟是否达到55
				JB	 NO_TELL		; 秒钟<55则不报时，结束
				JZ	 SEP_TELL
                CMP	 SECOND,56
                JZ	 SEP_TELL
                CMP	 SECOND,57
                JZ	 SEP_TELL
                CMP	 SECOND,58
                JZ	 SEP_TELL
                CMP	 SECOND,59
                JZ	 SEP_TELL      
				CALL BAOSHI			; 否则开始报时
				JMP	 DELAY			; 延时
		;---------
		SEP_TELL:             
				CMP  SEC_TEMP, 50
				JB	 NO_TELL
				CALL BAOSHI         ; **-00-00开始报时
				JMP	 EXIT
				CALL DL1ms          
		;---------若分钟小于59，继续判断-------------------------
		NEXT:
				CMP  MINUTE, 0		; 判断分钟是否为0
				JNZ	 NO_TELL		; 不为0，结束
				CMP	 SECOND,0		; 否则判断秒钟是否为0
				JNZ	 NO_TELL		; 不为0，结束
				CALL BAOSHI			; **-00-00开始报时
		;----------------延时---------------------------------
		DELAY:
				CALL DL100MS		; 产生100ms的蜂鸣
		;----------------不报时-------------------------------
		NO_TELL:
				CALL N_BAOSHI		; 关闭蜂鸣
		EXIT:
				RET					; 从子程序返回
	TELL_TIME ENDP 	; 整点报时子程序结束
	
	;--------------报时子程序------------------------------------
	BAOSHI PROC	NEAR	; 报时子程序
				MOV	DX, CTRL_8255
				MOV	AL, 0CH			; 8255的PC6连接蜂鸣器
				OUT	DX, AL			; PC6清零，产生蜂鸣，开始报时
				RET
	BAOSHI ENDP
	;-------------停止报时子程序----------------------------------
	N_BAOSHI PROC NEAR		; 停止报时子程序
				MOV	DX, CTRL_8255
				MOV	AL, 0DH			; 8255的PC6连接蜂鸣器
				OUT	DX, AL			; PC6置1，关闭蜂鸣，停止报时
				RET
	N_BAOSHI ENDP
    
		;-------------------------------------D设置闹钟------------------------------------------------
	D_KEY PROC NEAR		; 执行D键，设置闹钟时间
				LEA	 SI, BUFFER                                    
				MOV	 CX, 8
		;-------------------------------------------------------------------
		CLEAR:			
				MOV	 AL, 11H		; 清除显示缓冲区
				MOV	 [SI], AL
				INC	 SI
				LOOP CLEAR
				DEC	 SI				; SI指向最后BUFFER一位，即时钟的十位
		;---------------------设置时钟的十位---------------------------------
		CLOCK_H1:		;设置时钟的十位
				CALL DISP
				CALL SCAN
				
				CMP  AL, -1
				JZ	 CLOCK_H1
				CMP	 AL, 3			; 时钟的十位必须小于3
				JNB	 CLOCK_H1		; 若不是，则重新扫描
				MOV	 [SI], AL		; 键值保存到显示缓冲区
				MOV	 BL, AL			; 保存至BL以便于下面判断时钟的个位
				CALL DISP
				DEC	 SI
		;---------------------设置时钟的个位---------------------------------
		CLOCK_H0:		;设置时钟的个位
				CALL DISP			; 显示时间
				CALL SCAN			; 扫描
				
				CMP  AL, -1			
				JZ	 CLOCK_H0
				CMP	 BL, 2			; 判断时钟的十位是否为2
				JNZ	 CLOCK_A		; 不为2
				CMP	 AL, 4
				JNB	 CLOCK_H0
		;----------------------判断时钟的个位是否小于10----------------
		CLOCK_A:		;判断时钟的个位是否小于10
				CMP	 AL,10
				JNB	 CLOCK_H0		; 大于等于10，继续扫描
				MOV	 [SI],AL		; 否则保存至缓冲区
				CALL DISP
				DEC	 SI
				DEC	 SI
		;-----------------------设置分钟的十位-------------------------
		CLOCK_M1:					; 设置分钟的十位
				CALL DISP
				CALL SCAN
				CMP	 AL, -1
				JZ   CLOCK_M1
				CMP	 AL, 6			; 判断是否大于等于6
				JNB	 CLOCK_M1		; 是则继续扫描
				MOV	 [SI], AL		; 否则保存至缓冲区
				CALL DISP
				DEC	 SI
		;---------------------设置分钟的个位--------------------------
		CLOCK_M0:		;设置分钟的个位
				CALL DISP
				CALL SCAN
				CMP	 AL, -1
				JZ	 CLOCK_M0
				CMP	 AL, 10			; 判断是否大于等于10
				JNB  CLOCK_M0		; 是则继续扫描
				MOV	 [SI], AL		; 否则保存至缓冲区
				CALL DISP
				DEC	 SI
				DEC	 SI
				MOV	 AL, 0
				MOV	 [SI], AL		; 将闹钟的秒钟设置为0
				DEC	 SI
				MOV	 [SI], AL
				CALL DISP
				CALL SAVE_CLOCK		; 保存闹钟时间
				
				CALL CONVERT		; 切换至显示时间
				CALL DISP
				RET
	D_KEY ENDP
	


	;------------------------- 保存闹钟时间--------------------------------------------
	SAVE_CLOCK  PROC  NEAR			; 保存闹钟时间
				PUSH SI
				PUSH BX
				CMP  NUM, 2
				JAE  DDI
				JMP  DOIT
			
		;------------------------------------------------------------
		DDI:   
				MOV  BX, 0
			    MOV  NUM, 0
		;-----------------------------------------------------------
		DOIT:	
				LEA  SI, BUFFER
				INC	 SI				; 移动指针至秒针的十位
				MOV	 CLOCK_SEC[BX], 0	;SECOND=十位*10+个位
				INC  SI
				INC	 SI				; 跳过中间的‘-’
				MOV	 DL, [SI]
				INC	 SI				; 移动指针至分钟的十位
				MOV	 AH, 0
				MOV	 AL,[SI]
				MUL	 C10
				ADD	 AL, DL
				MOV	 CLOCK_MIN[BX], AL	; MINUTE=十位*10+个位
				INC  SI
				INC	 SI				; 跳过中间的‘-’
				MOV	 DL, [SI]
				INC	 SI				; 移动指针至时钟的十位
				MOV	 AH, 0
				MOV	 AL, [SI]
				MUL	 C10
				ADD	 AL, DL
				MOV	 CLOCK_HOUR[BX], AL	; HOUR=十位*10+个位
				INC	 CLOCK_FLAG
				INC  NUM
				INC  BX
				POP	 BX
				POP	 SI
				RET
	SAVE_CLOCK ENDP
	



	;-------------判断闹钟子程序---------------------------------      	
	ALARM_CLOCK	PROC NEAR	; 判断闹钟子程序
				PUSH DX
				PUSH AX
				PUSH BX			
				MOV  BX, 0
				CMP	 ALARM, 1		; 判断闹钟是否到来
				JZ	 NEXT9			; 如果到来继续判断闹钟时间
				MOV	 AL, HOUR			
	        	MOV	 DL, CLOCK_HOUR[BX]
				CMP	 AL, DL
				JNZ	 NO_ALARM
				JA 	 HHH			; 比较闹钟的时与当前时间的时
				MOV	 AL, MINUTE
				MOV	 DL, CLOCK_MIN[BX]
				CMP	 AL, DL
				JA 	 HHH			; 比较闹钟的分与当前时间的分
				JNZ	 NO_ALARM
				MOV	 AL, SECOND		; 比较闹钟的秒与当前时间的秒
				CMP	 AL, 0
				JNZ	 NO_ALARM
				MOV	 ALARM, 1		; 闹钟到来标志设为1，表示闹钟到来
				JMP  NEXT9
		;-------------比较闹钟的时与当前时间的时--------------------
		HHH:	
				MOV  BX, 1
				CMP	 ALARM, 1		; 判断闹钟是否到来
				JZ	 NEXT9			; 如果到来继续判断闹钟时间
				MOV	 AL, HOUR			
	        	MOV	 DL, CLOCK_HOUR[BX]
				CMP	 AL, DL
				JNZ  NO_ALARM
				MOV	 AL,MINUTE
				MOV	 DL,CLOCK_MIN[BX]
				CMP	 AL,DL			; 比较闹钟的分与当前时间的分
				JNZ	 NO_ALARM
				MOV	 AL, SECOND		; 比较闹钟的秒与当前时间的秒
				CMP	 AL, 0
				JNZ	 NO_ALARM
				MOV	 ALARM, 1	
		;----------------------------------------------------------		
	    NEXT9:
				CMP	 CLOCK_TIME, 30		; 比较闹钟是否持续30秒
				JZ	 DEC_CLOCK
				CALL BAOSHI
				JMP	 NO_ALARM
		;-----------------------------------------------------------
		DEC_CLOCK:
				DEC  NUM
				MOV	 CLOCK_TIME, 0  ; 闹钟时间回到0
				MOV	 ALARM, 0		; 闹钟到来标志置位0
				CALL N_BAOSHI		; 停止蜂鸣
		;-----------------------------------------------------------
		NO_ALARM:
                POP  BX
				POP	 AX
				POP	 DX
				RET
	ALARM_CLOCK	ENDP 


	;---------------------------------------E停止闹钟---------------------------------------
	E_KEY PROC NEAR		; 执行E键，停止闹钟
				DEC  CLOCK_FLAG		; 设置闹钟标志为0
				MOV	 ALARM, 0		; 设置闹钟到来标志0
				MOV	 CLOCK_TIME, 0	; 设置闹钟时间0
				CALL N_BAOSHI       ; 停止蜂鸣
				RET
	E_KEY			ENDP

        	END	START