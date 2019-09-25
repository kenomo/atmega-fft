
FFT:

	; TODO: clear all



	;------------------------------------------------------
	; bin loop

	; init bin loop
	ldi rBIN_COUNTER, 0x01

FFT_BIN_LOOP:

	; outer bin loop
	cpi rBIN_COUNTER, 17
	brne FFT_BIN_LOOP_NOT_EQUAL
	rjmp FFT_END

FFT_BIN_LOOP_NOT_EQUAL:


	; set pointer to begin of data points
	; load even and odd pointer
	ldi pEVENL, low(sFFT_POINTS)
    ldi pEVENH, high(sFFT_POINTS)
	ldi pODDL, low(sFFT_POINTS)
    ldi pODDH, high(sFFT_POINTS)
	adiw pODDH:pODDL, 0x01 ; increment so pointer is odd


	;------------------------------------------------------
	; m loop

	; init m loop
	ldi rM_COUNTER, 0x00

FFT_SUM_LOOP:

	; m loop
	cpi rM_COUNTER, 64
	brne FFT_SUM_LOOP_NOT_EQUAL
	rjmp FFT_SUM_END

FFT_SUM_LOOP_NOT_EQUAL:


	;------------------------------------------------------
	; load sin and cos from table 1
	
	; set z pointer to sin_cos table start
	ldi ZH, high(sin_cos_table_1*2)
	ldi ZL, 0x00

	; multiply: rM_COUNTER * rBIN_COUNTER
	mul rM_COUNTER, rBIN_COUNTER
	
	; muliply by 2 <- address
	lsl r0
	rol r1

	; add offset m*k to Z-Pointer
	ADD16B r0, r1, ZL, ZH
	mov ZL, rC1
	mov ZH, rC2
	
	lpm rEXPR, Z+ ; sin
	lpm rEXPI, Z  ; cos


	;------------------------------------------------------
	; even real
	ld rTEMPA, X
	muls rTEMPA, rEXPR
	ADD_EVEN_R r1

	;------------------------------------------------------
	; even img
	muls rTEMPA, rEXPI
	ADD_EVEN_I r1
	
	;------------------------------------------------------
	; odd real
	ld rTEMPA, Y
	muls rTEMPA, rEXPR
	ADD_ODD_R r1

	;------------------------------------------------------
	; odd img
	muls rTEMPA, rEXPI
	ADD_ODD_I r1


	;------------------------------------------------------
	; increment pointer on data points
	adiw pEVENH:pEVENL, 0x02
	adiw pODDH:pODDL, 0x02

	; end of m loop
	inc rM_COUNTER
	rjmp FFT_SUM_LOOP

FFT_SUM_END:


	;------------------------------------------------------
	; load sin and cos from table 1

	; set z pointer to sin_cos table start
	ldi ZH, high(sin_cos_table_1*2)
	ldi ZL, 0x00

	; load k <- bin counter
	clr r1 ; high byte always zero
	mov r0, rBIN_COUNTER ; low byte is counter
	
	lsl r0 ; multiply by 2

	ADD16B r0, r1, ZL, ZH
	mov ZL, rC1
	mov ZH, rC2
	
	lpm rEXPR, Z+ ; sin
	lpm rEXPI, Z  ; cos

	
	;------------------------------------------------------
	; multiply exp factor on odd part

	; real part
	GET_ODD_R rTEMPA
	muls rEXPR, rTEMPA
	mov r2, r0
	mov r3, r1

	GET_ODD_I rTEMPA
	neg rTEMPA
	muls rEXPI, rTEMPA

	ADD16B r0, r1, r2, r3

	; save
	mov rTEMPCL, rC1
	mov rTEMPCH, rC2

	; imag part
	GET_ODD_I rTEMPA
	muls rEXPR, rTEMPA
	mov r2, r0
	mov r3, r1

	GET_ODD_R rTEMPA
	muls rEXPI, rTEMPA

	ADD16B r0, r1, r2, r3

	; save
	mov rTEMPDL, rC1
	mov rTEMPDH, rC2


	;------------------------------------------------------
	; real part

	GET_EVEN_R rTEMPA
	EXPLODE8b16b rTEMPA, rTEMPB

	ADD16B rTEMPA, rTEMPB, rTEMPCL, rTEMPCH
	mov rTEMPCL, rC1
	mov rTEMPCH, rC2

	MUL16B rTEMPCL, rTEMPCH, rTEMPCL, rTEMPCH

	;------------------------------------------------------
	; imag part

	GET_EVEN_I rTEMPA
	EXPLODE8b16b rTEMPA, rTEMPB

	ADD16B rTEMPA, rTEMPB, rTEMPDL, rTEMPDH
	mov rTEMPA, rC1
	mov rTEMPB, rC2

	MUL16B rTEMPA, rTEMPB, rTEMPA, rTEMPB


	;------------------------------------------------------
	; hier geht es weiter



	; end of outer bin loop
	inc rBIN_COUNTER
	rjmp FFT_BIN_LOOP

FFT_END:

	ret
