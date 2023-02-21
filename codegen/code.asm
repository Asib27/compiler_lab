.MODEL SMALL
.STACK 1000H
.DATA

	; ; global variable declaration
	c DW 1 DUP (0000H)	; declared at line 1
	b DW 1 DUP (0000H)	; declared at line 1
	a DW 1 DUP (0000H)	; declared at line 1
.CODE
func_a PROC
	PUSH BP
	MOV BP,SP

	; line 4
	MOV BX,7
	MOV a,BX
	POP BP
	RET
func_a ENDP
foo PROC
	PUSH BP
	MOV BP,SP

	; line 8
	MOV BX,[BP+4]
	MOV CX,3
	ADD BX,CX
	MOV [BP+4],BX

	; line 9
	MOV BX,[BP+4]
	MOV AX,BX
	POP BP
	RET
foo ENDP
bar PROC
	PUSH BP
	MOV BP,SP

	; line 14
	MOV BX,4
	MOV CX,[BP+6]
	MOV AX,BX
	MUL CX
	MOV BX,2
	MOV CX,[BP+4]
	MOV AX,BX
	MUL CX
	ADD AX,AX
	MOV c,AX

	; line 15
	MOV BX,c
	MOV AX,BX
	POP BP
	RET
bar ENDP
main PROC
	MOV AX,@DATA
	MOV DX,AX
	PUSH BP
	MOV BP,SP

	; line 20
	SUB SP,8	; initializing local variables

	; line 22
	MOV BX,5
	MOV [BP-8],BX

	; line 23
	MOV BX,6
	MOV [BP-6],BX

	; line 25
	CALL func_a
	ADD SP,0
	MOV BX,AX	; moving the result to empty register

	; line 26

	; Line 26
	MOV AX,a	; saving to register for printing
	CALL PRINT_OUTPUT
	CALL NEW_LINE

	; line 28
	MOV BX,[BP-8]
	PUSH BX
	CALL foo
	ADD SP,2
	MOV BX,AX	; moving the result to empty register
	MOV [BP-4],BX

	; line 29

	; Line 29
	MOV AX,[BP-4]	; saving to register for printing
	CALL PRINT_OUTPUT
	CALL NEW_LINE

	; line 31
	MOV BX,[BP-8]
	PUSH BX
	MOV BX,[BP-6]
	PUSH BX
	CALL bar
	ADD SP,4
	MOV BX,AX	; moving the result to empty register
	MOV [BP-2],BX

	; line 32

	; Line 32
	MOV AX,[BP-2]	; saving to register for printing
	CALL PRINT_OUTPUT
	CALL NEW_LINE

	; line 34
	MOV BX,6
	PUSH BX
	MOV BX,[BP-8]
	PUSH BX
	MOV BX,[BP-6]
	PUSH BX
	CALL bar
	ADD SP,4
	MOV CX,AX	; moving the result to empty register
	POP BX
	MOV AX,BX
	MUL CX
	MOV BX,2
	ADD AX,BX
	MOV BX,3
	PUSH BX
	MOV BX,[BP-8]
	PUSH BX
	CALL foo
	ADD SP,2
	MOV CX,AX	; moving the result to empty register
	POP BX
	MOV AX,BX
	MUL CX
	SUB AX,AX
	MOV [BP-6],AX

	; line 35

	; Line 35
	MOV AX,[BP-6]	; saving to register for printing
	CALL PRINT_OUTPUT
	CALL NEW_LINE

	; line 38
	MOV BX,0
	MOV AX,BX
	ADD SP,8
	POP BP
	MOV AX,4CH
	INT 21H
main ENDP
NEW_LINE PROC
    PUSH AX
    PUSH DX
    
    MOV AH, 2       ; output a char
    MOV DL, 0DH     
    INT 21H         ; print CR
    MOV DL, 0AH     
    INT 21H         ; print LF
    
    POP DX                    
    POP AX                    
    RET
NEW_LINE ENDP

PRINT_OUTPUT PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX

    ; if AX < 0
    OR AX, AX
    JGE @END_IF1

    ; then
    PUSH AX         ; save number
    MOV DL, '-'     ; get '-'
    MOV AH, 2       ; print char function
    INT 21H         
    POP AX          ; get AX back
    NEG AX          ; AX = - AX
@END_IF1:
    
    ; get decimal digits                   
    XOR CX, CX      ; CX counts digits
    MOV BX, 10D     ; BX has divisor
                                
DEC_OUTPUT_WHILE:
    XOR DX, DX      ; prepare high word of dividend
    DIV BX          ; AX = quotient, DX = remainder
    PUSH DX         ; save remainder on stack
    INC CX          ; count = count + 1
    
    ; until
    OR AX,  AX      ; quotient = 0?
    JNE DEC_OUTPUT_WHILE      
    
    ; convert digit to char and print
    MOV AH, 2       ; print char function
DEC_PRINT_LOOP:
    POP DX          ; digit in DL
    OR DL, 30H      ; convert to char
    INT 21H         ; print digit
    LOOP DEC_PRINT_LOOP
    
    ; end for
    
    POP DX  
    POP CX     
    POP BX
    POP AX       
    RET
PRINT_OUTPUT ENDP

END MAIN
