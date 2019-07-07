
DISPLAY_ROUTINE:
	cli

	lds rROW_COUNTER, LED_ROW_COUNTER ; load LED_ROW_COUNTER
	
	; change the row
	mov rTEMP, rROW_COUNTER
	ror rTEMP ; shift right into carry flag
	ror rROW_COUNTER
	
	; write back row counter to SRAM
	sts LED_ROW_COUNTER, rROW_COUNTER
	
	; set z pointer to last entry of LED_ARRAY
	ldi Z_POINTER_LOW, low(LED_ARRAY + LED_ARRAY_SIZE)
    ldi Z_POINTER_HIGH, high(LED_ARRAY + LED_ARRAY_SIZE)

	; shift z pointer to the row defined as a bit in rROW_COUNTER: 0b00000100 -> third row
	call DISPLAY_ROUTINE_Z_POINTER_ROW_SHIFT

	; load LED_ROW_COUNTER again to rROW_COUNTER
	lds rROW_COUNTER, LED_ROW_COUNTER

	
	ldi rSPI_BUFFER, 0x00 ; clear SPI Buffer
	ldi rCOLUMN_COUNTER, 0x01 ; set column counter to first column
	rcall DISPLAY_ROUTINE_WRITE_ROW_TO_SPI_BUFFER

	SPI_WRITE rSPI_BUFFER
	rcall SPI_WAIT_FOR_TRANSMIT


	ldi rSPI_BUFFER, 0x00 ; clear SPI Buffer
	ldi rCOLUMN_COUNTER, 0x01 ; set column counter to first column
	rcall DISPLAY_ROUTINE_WRITE_ROW_TO_SPI_BUFFER
	
	SPI_WRITE rSPI_BUFFER
	rcall SPI_WAIT_FOR_TRANSMIT
	
	; invert rROW_COUNTER: 0: row is on, ....
	ldi rTEMP, 0xFF
	eor rROW_COUNTER, rTEMP

	SPI_WRITE rROW_COUNTER
	rcall SPI_WAIT_FOR_TRANSMIT


	SHIFT_REGISTER_WRITE


	sei
	reti


DISPLAY_ROUTINE_Z_POINTER_ROW_SHIFT:
	
	lsl rROW_COUNTER ; shift left
	sbiw Z_POINTER_HIGH:Z_POINTER_LOW, 1 ; decrease z-pointer by one

	cpi rROW_COUNTER, 0x00 ; compare immediate
	brne DISPLAY_ROUTINE_Z_POINTER_ROW_SHIFT ; if rROW_COUNTER not equal to 0x00 jump to ...
		
	ret


DISPLAY_ROUTINE_WRITE_ROW_TO_SPI_BUFFER:
	
	ld rTEMP, Z ; load "LED bit" from SRAM

	sbrc rTEMP, 0 ; skip next line if bit 0 in rTEMP is clear -> LED off
	eor rSPI_BUFFER, rCOLUMN_COUNTER

	sbiw Z_POINTER_HIGH:Z_POINTER_LOW, 8 ; decrease z pointer by 8 bytes

	lsl rCOLUMN_COUNTER ; shift left
	cpi rCOLUMN_COUNTER, 0x00 ; compare immediate
	brne DISPLAY_ROUTINE_WRITE_ROW_TO_SPI_BUFFER ; if rCOLUMN_COUNTER not equal to 0x00 jump to ...

	ret


DISPLAY_ROUTINE_FILL_DEBUG:

	; set z pointer to last entry of LED_ARRAY
	ldi Z_POINTER_LOW, low(LED_ARRAY + LED_ARRAY_SIZE)
    ldi Z_POINTER_HIGH, high(LED_ARRAY + LED_ARRAY_SIZE)

	ldi rCOUNTER, 128
	rcall DISPLAY_ROUTINE_FILL_DISPLAY

	; set z pointer to first entry of LED_ARRAY
	ldi Z_POINTER_LOW, low(LED_ARRAY)
    ldi Z_POINTER_HIGH, high(LED_ARRAY)

	ldi rTEMP, 0x00
	std Z + 0, rTEMP
	std Z + 4, rTEMP
	std Z + 8, rTEMP
	std Z + 10, rTEMP
	std Z + 11, rTEMP
	std Z + 20, rTEMP
	std Z + 22, rTEMP
	std Z + 23, rTEMP
	std Z + 25, rTEMP
	std Z + 26, rTEMP
	std Z + 28, rTEMP
	std Z + 30, rTEMP
	std Z + 31, rTEMP
	std Z + 33, rTEMP
	std Z + 35, rTEMP
	std Z + 38, rTEMP
	std Z + 42, rTEMP
	std Z + 44, rTEMP
	std Z + 50, rTEMP
	std Z + 54, rTEMP
	std Z + 60, rTEMP
	std Z + 61, rTEMP
	std Z + 62, rTEMP
	std Z + 63, rTEMP

	adiw Z_POINTER_HIGH:Z_POINTER_LOW, 63

	ldi rTEMP, 0x00
	std Z + 0, rTEMP
	std Z + 4, rTEMP
	std Z + 8, rTEMP
	std Z + 10, rTEMP
	std Z + 11, rTEMP
	std Z + 20, rTEMP
	std Z + 22, rTEMP
	std Z + 23, rTEMP
	std Z + 25, rTEMP
	std Z + 26, rTEMP
	std Z + 28, rTEMP
	std Z + 30, rTEMP
	std Z + 31, rTEMP
	std Z + 33, rTEMP
	std Z + 35, rTEMP
	std Z + 38, rTEMP
	std Z + 42, rTEMP
	std Z + 44, rTEMP
	std Z + 50, rTEMP
	std Z + 54, rTEMP
	std Z + 60, rTEMP
	std Z + 61, rTEMP
	std Z + 62, rTEMP
	std Z + 63, rTEMP

	ret


DISPLAY_ROUTINE_FILL_DISPLAY:

	ldi rTEMP, 0xFF
	st -Z, rTEMP

	dec rCOUNTER

	cpi rCOUNTER, 0x00 ; compare immediate
	brne DISPLAY_ROUTINE_FILL_DISPLAY ; if rCOUNTER not equal to 0x00 jump to ...

	ret