
ADC_CONVERSION_COMPLETE:
	cli

	ADC_PUSH_STACK
	DEBUG_ADC_CONVERSION_START

	; reset counter
	ldi rTEMPA, (1<<OCF1B) ; OCF1B: Timer/Counter1, Output Compare B Match Flag	
	out TIFR1, rTEMPA ; Timer/Counter1 Interrupt Flag Register
		
	; load from adc
	lds rTEMPA, ADCH
	subi rTEMPA, 127
	
	; scaling
	ldi rTEMPB, 6
	muls rTEMPA, rTEMPB
	mov rTEMPA, r0

	; log to usart
	;rcall USART_TRANSMIT

	
	; store to SRAM
	lds ZL, sADC_SAMPLES_POINTER_L
	lds ZH, sADC_SAMPLES_POINTER_H
	st Z+, rTEMPA


	/*
	ldi rTEMPA, 86
	rcall USART_TRANSMIT
	*/


	; compare
	cpi ZL, 128
	brne ADC_CONVERSION_COMPLETE_END
	

	/*
	; debug
	ldi rTEMPA, 78
	rcall USART_TRANSMIT
	*/


	; stop adc interrupt
	CLRB ADCSRA, ADIE, rTEMPA


	; set pointer on start
	ldi ZL, low(sFFT_POINTS)
	ldi ZH, high(sFFT_POINTS)


ADC_CONVERSION_COMPLETE_END:
	
	sts sADC_SAMPLES_POINTER_L, ZL
	sts sADC_SAMPLES_POINTER_H, ZH

	DEBUG_ADC_CONVERSION_STOP
	ADC_POP_STACK

	sei
	reti