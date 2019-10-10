
FFT:

	/*
	; debug
	ldi rTEMPA, 65
	rcall USART_TRANSMIT
	*/

	;cli ; debug
	DEBUG_FFT_START

	;------------------------------------------------------
	; set display pointer to first bin
	ldi ZL, low(sLED_ARRAY)
	ldi ZH, high(sLED_ARRAY)
	adiw ZH:ZL, 0x07
	sts sFFT_DISPLAY_POINTER_L, ZL
	sts sFFT_DISPLAY_POINTER_H, ZH
	

	;------------------------------------------------------
	; bin loop

	; init bin loop
	ldi rBIN_COUNTER, 0x01

FFT_BIN_LOOP:

	; bin loop
	cpi rBIN_COUNTER, FFT_LAST_BIN - FFT_FIRST_BIN + 1 ; 1..17
	brne FFT_BIN_LOOP_CONTINUE
	rjmp FFT_END

FFT_BIN_LOOP_CONTINUE:


	;------------------------------------------------------
	; set pointer to begin of data points
	; load even and odd pointer
	ldi pEVENL, low(sFFT_POINTS)
    ldi pEVENH, high(sFFT_POINTS)
	ldi pODDL, low(sFFT_POINTS)
    ldi pODDH, high(sFFT_POINTS)
	adiw pODDH:pODDL, 0x01 ; increment so that pointer is odd


	;------------------------------------------------------
	; clear vars in data segment
	ldi rTEMPA, 0x00
	sts sEVENR, rTEMPA
	sts sEVENR + 0x01, rTEMPA
	sts sEVENI, rTEMPA
	sts sEVENI + 0x01, rTEMPA
	sts sODDR, rTEMPA
	sts sODDR + 0x01, rTEMPA
	sts sODDI, rTEMPA
	sts sODDI + 0x01, rTEMPA


	;------------------------------------------------------
	; sum loop

	; init sum loop
	ldi rSUM_COUNTER, 0x00

	/*
	ldi ZH, high(sDEBUG_SUM) ; debug: sum iterations
	ldi ZL, low(sDEBUG_SUM) ; debug: sum iterations
	*/

FFT_SUM_LOOP:

	; sum loop
	cpi rSUM_COUNTER, FFT_POINT_SIZE / 2
	brne FFT_SUM_LOOP_CONTINUE
	rjmp FFT_SUM_END

FFT_SUM_LOOP_CONTINUE:

	/*
	push r30 ; debug: sum iterations
	push r31 ; debug: sum iterations
	*/

	;------------------------------------------------------
	; load sin and cos from table 1
	
	; set z pointer to sin_cos table start
	ldi ZH, high(sin_cos_table_1*2)
	ldi ZL, 0x00

	; multiply: rSUM_COUNTER * rBIN_COUNTER
	mul rSUM_COUNTER, rBIN_COUNTER
	
	; muliply by 2 <- address
	lsl r0
	rol r1

	; add offset m*k to Z-Pointer
	add r0, ZL
	adc r1, ZH
	mov ZL, r0
	mov ZH, r1

	; load from memory
	lpm rEXPR, Z+ ; sin
	lpm rEXPI, Z  ; cos

	/*
	pop r31 ; debug: sum iterations
	pop r30 ; debug: sum iterations
	*/

	;------------------------------------------------------
	; even real
	ld rTEMPA, X
	muls rTEMPA, rEXPR
	ADD_EVEN_R

	;------------------------------------------------------
	; even img
	ld rTEMPA, X
	muls rTEMPA, rEXPI
	ADD_EVEN_I
	
	;------------------------------------------------------
	; odd real
	ld rTEMPA, Y
	muls rTEMPA, rEXPR
	ADD_ODD_R

	;------------------------------------------------------
	; odd img
	ld rTEMPA, Y
	muls rTEMPA, rEXPI
	ADD_ODD_I


	;------------------------------------------------------
	; increment pointer on data points
	adiw pEVENH:pEVENL, 0x02
	adiw pODDH:pODDL, 0x02


	; end of m loop
	inc rSUM_COUNTER
	rjmp FFT_SUM_LOOP

FFT_SUM_END:


	;------------------------------------------------------
	; load sin and cos from table 1

	; set z pointer to sin_cos table start
	ldi ZH, high(sin_cos_table_2*2)
	ldi ZL, 0x00

	; load k <- bin counter
	clr r1 ; high byte always zero
	mov r0, rBIN_COUNTER ; low byte is counter
	
	lsl r0 ; multiply by 2

	; add to Z pointer
	add ZL, r0
	adc ZH, r1

	; load from program memory
	lpm rEXPR, Z+ ; sin
	lpm rEXPI, Z  ; cos

	
	;------------------------------------------------------
	; multiply exp factor on odd part

	; real part
	GET_ODD_R
	muls rEXPR, rTEMPA
	mov r2, r0
	mov r3, r1

	GET_ODD_I
	neg rTEMPA
	muls rEXPI, rTEMPA

	ADD16B r0, r1, r2, r3

	; save
	mov rTEMPCL, rC1
	mov rTEMPCH, rC2


	; imag part
	GET_ODD_I
	muls rEXPR, rTEMPA
	mov r2, r0
	mov r3, r1

	GET_ODD_R
	muls rEXPI, rTEMPA

	ADD16B r0, r1, r2, r3

	; save
	mov rTEMPDL, rC1
	mov rTEMPDH, rC2


	;------------------------------------------------------
	; real part

	GET_EVEN_R
	EXPLODE8B16B rTEMPA, rTEMPB

	ADD16B rTEMPA, rTEMPB, rTEMPCL, rTEMPCH
	mov rTEMPCL, rC1
	mov rTEMPCH, rC2

	MUL16B rTEMPCL, rTEMPCH, rTEMPCL, rTEMPCH ; square

	rcall SCALE32B16B ; scale rC4:rC3:rC2:rC1
	mov rTEMPCL, rC1
	mov rTEMPCH, rC2


	;------------------------------------------------------
	; imag part

	GET_EVEN_I
	EXPLODE8B16B rTEMPA, rTEMPB

	ADD16B rTEMPA, rTEMPB, rTEMPDL, rTEMPDH
	mov rTEMPA, rC1
	mov rTEMPB, rC2

	MUL16B rTEMPA, rTEMPB, rTEMPA, rTEMPB ; square

	rcall SCALE32B16B ; scale rC4:rC3:rC2:rC1
	mov rTEMPDL, rC1
	mov rTEMPDH, rC2


	;------------------------------------------------------
	; add real and imag

	ADD16B rTEMPCL, rTEMPCH, rTEMPDL, rTEMPDH
	mov rTEMPCL, rC1
	mov rTEMPCH, rC2	


	;------------------------------------------------------
	; square root by table
	
	; set z pointer to sqrt_table start
	ldi ZH, 0x00
	ldi ZL, 0x00
	ldi rTEMPA, byte3(sqrt_table<<1) ; -> 0x01
	out RAMPZ, rTEMPA

	add ZL, rTEMPCL
	adc ZH, rTEMPCH
	
	elpm rTEMPA, Z


	;------------------------------------------------------
	; write result to display
	rcall FFT_WRITE_TO_DISPLAY


	; end of outer bin loop
	inc rBIN_COUNTER
	rjmp FFT_BIN_LOOP

FFT_END:

	DEBUG_FFT_STOP

	; restart adc
	ldi rTEMPA, (1<<ADEN)|(1<<ADATE)|(1<<ADIE)|(1<<ADSC)|(1<<ADPS1)|(1<<ADPS2)
	; ADEN: ADC Enable
	; ADATE: ADC Auto Trigger Enable
	; ADIE: ADC Interrupt Enable
	; ADSC: ADC Start Conversion
	; ADPS0, ADPS1: ADC prescaler selection -> 64
	sts ADCSRA, rTEMPA

	;sei ; debug
	ret


FFT_WRITE_TO_DISPLAY:

	lds ZL, sFFT_DISPLAY_POINTER_L
	lds ZH, sFFT_DISPLAY_POINTER_H

	ldi r20, 0xAA
	ldi r21, 0xFF

	; turn off the LED
	cpi rTEMPA, FFT_POWER_8
	brsh FFT_WRITE_TO_DISPLAY_8
	st Z, r20

	cpi rTEMPA, FFT_POWER_7
	brsh FFT_WRITE_TO_DISPLAY_7
	st -Z, r20

	cpi rTEMPA, FFT_POWER_6
	brsh FFT_WRITE_TO_DISPLAY_6
	st -Z, r20

	cpi rTEMPA, FFT_POWER_5
	brsh FFT_WRITE_TO_DISPLAY_5
	st -Z, r20

	cpi rTEMPA, FFT_POWER_4
	brsh FFT_WRITE_TO_DISPLAY_4
	st -Z, r20

	cpi rTEMPA, FFT_POWER_3
	brsh FFT_WRITE_TO_DISPLAY_3
	st -Z, r20

	cpi rTEMPA, FFT_POWER_2
	brsh FFT_WRITE_TO_DISPLAY_2
	st -Z, r20

	cpi rTEMPA, FFT_POWER_1
	brsh FFT_WRITE_TO_DISPLAY_1
	st -Z, r20

	rjmp FFT_WRITE_TO_DISPLAY_END

	; turn on the LED
FFT_WRITE_TO_DISPLAY_8:	
	st Z, r21
FFT_WRITE_TO_DISPLAY_7:
	st -Z, r21
FFT_WRITE_TO_DISPLAY_6:
	st -Z, r21
FFT_WRITE_TO_DISPLAY_5:
	st -Z, r21
FFT_WRITE_TO_DISPLAY_4:
	st -Z, r21
FFT_WRITE_TO_DISPLAY_3:
	st -Z, r21
FFT_WRITE_TO_DISPLAY_2:
	st -Z, r21
FFT_WRITE_TO_DISPLAY_1:
	st -Z, r21

FFT_WRITE_TO_DISPLAY_END:

	adiw ZH:ZL, 15

	sts sFFT_DISPLAY_POINTER_L, ZL
	sts sFFT_DISPLAY_POINTER_H, ZH

	ret