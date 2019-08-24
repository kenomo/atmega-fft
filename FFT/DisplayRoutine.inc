

DISPLAY_ROUTINE:
	cli ; global interrupt disable
	
	; jump to program position of display routine
	lds rTEMPA, sLED_PROGRAM
	cpi rTEMPA, 0x01
	breq DISPLAY_ROUTINE_COLUMNS_A
	cpi rTEMPA, 0x02
	breq DISPLAY_ROUTINE_ROWS
	cpi rTEMPA, 0x03
	breq DISPLAY_ROUTINE_WRITE_SHIFT_REGISTER
	
	
	lds rDR_ROW_COUNTER, sLED_ROW_COUNTER ; load sLED_ROW_COUNTER from SRAM
	
	; change the row
	mov rTEMPA, rDR_ROW_COUNTER
	ror rTEMPA ; shift right into carry flag
	ror rDR_ROW_COUNTER ; shift right and carry flag in
	
	; write back row counter to SRAM
	sts sLED_ROW_COUNTER, rDR_ROW_COUNTER
	
	
	; set z pointer to last entry of LED_ARRAY
	ldi Z_POINTER_LOW, low(sLED_ARRAY + LED_ARRAY_SIZE)
    ldi Z_POINTER_HIGH, high(sLED_ARRAY + LED_ARRAY_SIZE)

	; shift z pointer to the row defined as a bit in rDR_ROW_COUNTER: 0b00000100 -> third row
	call DISPLAY_ROUTINE_Z_POINTER_ROW_SHIFT


DISPLAY_ROUTINE_COLUMNS_B: ; write last 8 columns
	
	ldi rSPI_BUFFER, 0x00 ; clear SPI Buffer
	ldi rDR_COLUMN_COUNTER, 0x01 ; set column counter to first column
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
	ldi rDR_COLUMN_COUNTER, 0x01 ; set column counter to first column
	rcall DISPLAY_ROUTINE_WRITE_ROW_TO_SPI_BUFFER
	
	DISPLAY_ROUTINE_WRITE_Z_POINTER_TO_SRAM
	
	; set display routine program position
	ldi rTEMPA, 0x02
	sts sLED_PROGRAM, rTEMPA
	
	; write and end
	SPI_WRITE rSPI_BUFFER
	rjmp DISPLAY_ROUTINE_END
	

DISPLAY_ROUTINE_ROWS: ; write rows

	; load sLED_ROW_COUNTER again to rDR_ROW_COUNTER
	lds rDR_ROW_COUNTER, sLED_ROW_COUNTER

	; invert rDR_ROW_COUNTER: 0: row is on, ....
	ldi rTEMPA, 0xFF
	eor rDR_ROW_COUNTER, rTEMPA
	
	; set display routine program position
	ldi rTEMPA, 0x03
	sts sLED_PROGRAM, rTEMPA
	
	; write and end
	SPI_WRITE rDR_ROW_COUNTER
	rjmp DISPLAY_ROUTINE_END


DISPLAY_ROUTINE_WRITE_SHIFT_REGISTER: ; write the shift register
	SHIFT_REGISTER_WRITE

	; set display routine program position
	ldi rTEMPA, 0x00
	sts sLED_PROGRAM, rTEMPA


DISPLAY_ROUTINE_END:
	sei ; global interrupt enable
	reti ; return from interrupt




DISPLAY_ROUTINE_Z_POINTER_ROW_SHIFT:
	
	lsl rDR_ROW_COUNTER ; shift left
	sbiw Z_POINTER_HIGH:Z_POINTER_LOW, 1 ; decrease z-pointer by one

	cpi rDR_ROW_COUNTER, 0x00 ; compare immediate
	brne DISPLAY_ROUTINE_Z_POINTER_ROW_SHIFT ; if rDR_ROW_COUNTER not equal to 0x00 jump to ...
		
	ret


DISPLAY_ROUTINE_WRITE_ROW_TO_SPI_BUFFER:
	
	ld rTEMPA, Z ; load "LED bit" from SRAM

	sbrc rTEMPA, 0 ; skip next line if bit 0 in rTEMPA is clear -> LED off
	eor rSPI_BUFFER, rDR_COLUMN_COUNTER

	sbiw Z_POINTER_HIGH:Z_POINTER_LOW, 8 ; decrease z pointer by 8 bytes

	lsl rDR_COLUMN_COUNTER ; shift left
	cpi rDR_COLUMN_COUNTER, 0x00 ; compare immediate
	brne DISPLAY_ROUTINE_WRITE_ROW_TO_SPI_BUFFER ; if rCOLUMN_COUNTER not equal to 0x00 jump to ...

	ret


DISPLAY_ROUTINE_FILL_DEBUG:

	; set z pointer to last entry of sLED_ARRAY
	ldi Z_POINTER_LOW, low(sLED_ARRAY + LED_ARRAY_SIZE)
    ldi Z_POINTER_HIGH, high(sLED_ARRAY + LED_ARRAY_SIZE)

	ldi rCOUNTER, 128
	rcall DISPLAY_ROUTINE_FILL_DISPLAY

	; set z pointer to first entry of sLED_ARRAY
	ldi Z_POINTER_LOW, low(sLED_ARRAY)
    ldi Z_POINTER_HIGH, high(sLED_ARRAY)

	ldi rTEMPA, 0x00
	std Z + 0, rTEMPA
	std Z + 4, rTEMPA
	std Z + 8, rTEMPA
	std Z + 10, rTEMPA
	std Z + 11, rTEMPA
	std Z + 20, rTEMPA
	std Z + 22, rTEMPA
	std Z + 23, rTEMPA
	std Z + 25, rTEMPA
	std Z + 26, rTEMPA
	std Z + 28, rTEMPA
	std Z + 30, rTEMPA
	std Z + 31, rTEMPA
	std Z + 33, rTEMPA
	std Z + 35, rTEMPA
	std Z + 38, rTEMPA
	std Z + 42, rTEMPA
	std Z + 44, rTEMPA
	std Z + 50, rTEMPA
	std Z + 54, rTEMPA
	std Z + 60, rTEMPA
	std Z + 61, rTEMPA
	std Z + 62, rTEMPA
	std Z + 63, rTEMPA

	adiw Z_POINTER_HIGH:Z_POINTER_LOW, 63

	ldi rTEMPA, 0x00
	std Z + 0, rTEMPA
	std Z + 4, rTEMPA
	std Z + 8, rTEMPA
	std Z + 10, rTEMPA
	std Z + 11, rTEMPA
	std Z + 20, rTEMPA
	std Z + 22, rTEMPA
	std Z + 23, rTEMPA
	std Z + 25, rTEMPA
	std Z + 26, rTEMPA
	std Z + 28, rTEMPA
	std Z + 30, rTEMPA
	std Z + 31, rTEMPA
	std Z + 33, rTEMPA
	std Z + 35, rTEMPA
	std Z + 38, rTEMPA
	std Z + 42, rTEMPA
	std Z + 44, rTEMPA
	std Z + 50, rTEMPA
	std Z + 54, rTEMPA
	std Z + 60, rTEMPA
	std Z + 61, rTEMPA
	std Z + 62, rTEMPA
	std Z + 63, rTEMPA
	
	ret


DISPLAY_ROUTINE_FILL_DISPLAY:

	ldi rTEMPA, 0xFF
	st -Z, rTEMPA

	dec rCOUNTER

	cpi rCOUNTER, 0x00 ; compare register immediate
	brne DISPLAY_ROUTINE_FILL_DISPLAY ; if rCOUNTER not equal to 0x00 jump to ...

	ret