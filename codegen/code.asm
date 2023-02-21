.MODEL SMALL
.STACK 1000H
.DATA

	; ; global variable declaration
	b DW 1 DUP (0000H)	; declared at line 1
	a DW 1 DUP (0000H)	; declared at line 1
	j DW 1 DUP (0000H)	; declared at line 3
	i DW 1 DUP (0000H)	; declared at line 3
.CODE
main PROC
	MOV AX,@DATA
	MOV DX,AX
	PUSH BP
	MOV BP,SP

	; line 11
	MOV BX,1
	MOV a,BX

	; line 12
	MOV BX,2
	MOV b,BX

	; line 13
	MOV BX,3
	MOV i,BX

	; line 14
	MOV BX,4
	MOV j,BX

	; line 15
	MOV BX,a
	MOV CX,b
	MOV DX,i
	MOV AX,j
	ADD DX,AX
	ADD CX,DX
	ADD BX,CX
	MOV a,BX

	; line 16

	; Line 16
	MOV AX,a	; saving to register for printing
	CALL PRINT_OUTPUT
	CALL NEW_LINE
	ADD SP,0
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
