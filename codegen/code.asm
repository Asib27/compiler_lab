.MODEL SMALL
.STACK 1000H
.DATA

	; ; global variable declaration
	b DW 1 DUP (0000H)	; declared at line 1
	a DW 1 DUP (0000H)	; declared at line 1
	j DW 1 DUP (0000H)	; declared at line 3
	i DW 1 DUP (0000H)	; declared at line 3
.CODE
abc PROC
	PUSH BP
	MOV BP,SP

	; line 6
	MOV BX,[BP+6]
	MOV CX,[BP+4]
	ADD BX,CX
	MOV [BP+6],BX

	; line 7

	; Line 7
	MOV AX,[BP+6]	; saving to register for printing
	CALL PRINT_OUTPUT
	CALL NEW_LINE

	; line 8
	MOV BX,[BP+6]
	MOV AX,BX
	ADD SP,0
	POP BP
	RET
abc ENDP
main PROC
	MOV AX,@DATA
	MOV DX,AX
	PUSH BP
	MOV BP,SP

	; line 12
	MOV BX,10
	PUSH BX
	MOV CX,30
	MOV DX,60
	ADD CX,DX
	PUSH CX
	CALL abc
	ADD SP,4
	MOV DX,AX
	POP CX
	POP BX
	MOV a,DX

	; line 13

	; Line 13
	MOV AX,a	; saving to register for printing
	CALL PRINT_OUTPUT
	CALL NEW_LINE
	ADD SP,0
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
