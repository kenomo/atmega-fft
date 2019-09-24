
FFT:

	; init bin loop
	ldi rBIN_COUNTER, 0x01

FFT_BIN_LOOP:

	; outer bin loop
	cpi rBIN_COUNTER, 17
	breq FFT_END

	; set pointer to begin of data points
	; load even and odd pointer
	ldi XL, low(sFFT_POINTS)
    ldi XH, high(sFFT_POINTS)
	ldi YL, low(sFFT_POINTS)
    ldi YH, high(sFFT_POINTS)

	; init m loop
	ldi rM_COUNTER, 0x00

FFT_SUM_LOOP:

	; m loop
	cpi rM_COUNTER, 64
	breq FFT_SUM_END

	;------------------------------------------------------
	; load sin and cos
	
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


	; end of m loop
	inc rM_COUNTER
	rcall FFT_SUM_LOOP

FFT_SUM_END:


	
	


	; end of outer bin loop
	inc rBIN_COUNTER
	rcall FFT_BIN_LOOP

FFT_END:

	ret
