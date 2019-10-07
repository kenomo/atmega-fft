
DISPLAY_ROUTINE_TIMER:
	cli ; global interrupt disable


	push rTEMPA
	ldi rTEMPA, 0x00
	out TCNT0, rTEMPA ; clear timer compare register
	pop rTEMPA


DISPLAY_ROUTINE:
	cli ; global interrupt disable

	DISPLAY_ROUTINE_PUSH_STACK


	; for debug purpose -> set PIN PC7 high
	ldi rTEMPA, (1<<7)
	out PortC, rTEMPA
	

	; jump to program position of display routine
	lds rTEMPA, sLED_PROGRAM
	cpi rTEMPA, 0x01
	breq DISPLAY_ROUTINE_COLUMNS_A
	cpi rTEMPA, 0x02
	breq DISPLAY_ROUTINE_ROWS
	cpi rTEMPA, 0x03
	breq DISPLAY_ROUTINE_WRITE_SHIFT_REGISTER
	
	
	lds rROW_COUNTER, sLED_ROW_COUNTER ; load sLED_ROW_COUNTER from SRAM
	
	; change the row
	mov rTEMPA, rROW_COUNTER
	ror rTEMPA ; shift right into carry flag
	ror rROW_COUNTER ; shift right and carry flag in
	
	; write back row counter to SRAM
	sts sLED_ROW_COUNTER, rROW_COUNTER
	
	
	; set z pointer to last entry of LED_ARRAY
	ldi ZL, low(sLED_ARRAY + LED_ARRAY_SIZE)
    ldi ZH, high(sLED_ARRAY + LED_ARRAY_SIZE)

	; shift z pointer to the row defined as a bit in rROW_COUNTER: 0b00000100 -> third row
	call DISPLAY_ROUTINE_Z_POINTER_ROW_SHIFT


DISPLAY_ROUTINE_COLUMNS_B: ; write last 8 columns
	
	ldi rSPI_BUFFER, 0x00 ; clear SPI Buffer
	ldi rCOLUMN_COUNTER, 0x01 ; set column counter to first column
	rcall DISPLAY_ROUTINE_WRITE_ROW_TO_SPI_BUFFER

	DISPLAY_ROUTINE_WRITE_Z_POINTER_TO_SRAM
	
	; set display routine program position
	ldi rTEMPA, 0x01
	sts sLED_PROGRAM, rTEMPA

	; write and end
	SPI_WRITE rSPI_BUFFER
	rjmp DISPLAY_ROUTINE_END


DISPLAY_ROUTINE_COLUMNS_A: ; write first 8 columns

	DISPLAY_ROUTINE_READ_Z_POINTER_FROM_SRAM

	ldi rSPI_BUFFER, 0x00 ; clear SPI Buffer
	ldi rCOLUMN_COUNTER, 0x01 ; set column counter to first column
	rcall DISPLAY_ROUTINE_WRITE_ROW_TO_SPI_BUFFER
	
	DISPLAY_ROUTINE_WRITE_Z_POINTER_TO_SRAM
	
	; set display routine program position
	ldi rTEMPA, 0x02
	sts sLED_PROGRAM, rTEMPA
	
	; write and end
	SPI_WRITE rSPI_BUFFER
	rjmp DISPLAY_ROUTINE_END
	

DISPLAY_ROUTINE_ROWS: ; write rows

	; load sLED_ROW_COUNTER again to rROW_COUNTER
	lds rROW_COUNTER, sLED_ROW_COUNTER

	; invert rROW_COUNTER: 0: row is on, ....
	ldi rTEMPA, 0xFF
	eor rROW_COUNTER, rTEMPA
	
	; set display routine program position
	ldi rTEMPA, 0x03
	sts sLED_PROGRAM, rTEMPA
	
	; write and end
	SPI_WRITE rROW_COUNTER
	rjmp DISPLAY_ROUTINE_END


DISPLAY_ROUTINE_WRITE_SHIFT_REGISTER: ; shift register
	SHIFT_REGISTER_WRITE

	; set display routine program position
	ldi rTEMPA, 0x00
	sts sLED_PROGRAM, rTEMPA


DISPLAY_ROUTINE_END:

	; for debug purpose -> set PIN PC7 low
	ldi rTEMPA, 0x00
	out PortC, rTEMPA


	DISPLAY_ROUTINE_POP_STACK

	sei ; global interrupt enable
	reti ; return from interrupt


DISPLAY_ROUTINE_Z_POINTER_ROW_SHIFT:
	
	lsl rROW_COUNTER ; shift left
	sbiw ZH:ZL, 0x01 ; decrease z-pointer by one

	cpi rROW_COUNTER, 0x00 ; compare immediate
	brne DISPLAY_ROUTINE_Z_POINTER_ROW_SHIFT ; if rROW_COUNTER not equal to 0x00 jump to ...
		
	ret


DISPLAY_ROUTINE_WRITE_ROW_TO_SPI_BUFFER:
	
	ld rTEMPA, Z ; load "LED bit" from SRAM

	sbrc rTEMPA, 0 ; skip next line if bit 0 in rTEMPA is clear -> LED off
	eor rSPI_BUFFER, rCOLUMN_COUNTER

	sbiw ZH:ZL, 8 ; decrease z pointer by 8 bytes

	lsl rCOLUMN_COUNTER ; shift left
	cpi rCOLUMN_COUNTER, 0x00 ; compare immediate
	brne DISPLAY_ROUTINE_WRITE_ROW_TO_SPI_BUFFER ; if rCOLUMN_COUNTER not equal to 0x00 jump to ...

	ret


