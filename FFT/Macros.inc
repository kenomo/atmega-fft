
;------------------------------------------------------
; SPI
;------------------------------------------------------

.MACRO SPI_WRITE
	out SPDR, @0
.ENDMACRO



;------------------------------------------------------
; FFT macros
;------------------------------------------------------

.MACRO ADD_EVEN_R ; add @1:@0
	ADD_TO_SUM @0, @1, sEVENR
.ENDMACRO

.MACRO ADD_EVEN_I ; add @1:@0
	ADD_TO_SUM @0, @1, sEVENI
.ENDMACRO

.MACRO ADD_ODD_R ; add @1:@0
	ADD_TO_SUM @0, @1, sODDR
.ENDMACRO

.MACRO ADD_ODD_I ; add @1:@0
	ADD_TO_SUM @0, @1, sODDI
.ENDMACRO

.MACRO ADD_TO_SUM ; add @1:@0, address @2
	push r2
	push r3
	push rTEMPA
	push rTEMPB

	; load summand from sram
	lds r3, @2
	lds r2, @2 + 1

	mov rTEMPA, @1 ; high byte
	mov rTEMPB, @0 ; low byte
	rcall ROUNDTRUNC ; round after truncation of low byte
	
	EXPLODE8b16b rTEMPA, rTEMPB
	ADD16B rTEMPA, rTEMPB, r2, r3

	; store new summand to sram
	sts @2 + 1, rC1
	sts @2, rC2

	/*
	st Z, rC2 ; debug: sum iterations
	adiw ZH:ZL, 0x01 ; debug: sum iterations
	st Z, rC1 ; debug: sum iterations
	adiw ZH:ZL, 0x01 ; debug: sum iterations
	*/
	
	pop rTEMPB
	pop rTEMPA
	pop r3
	pop r2
.ENDMACRO


.MACRO GET_EVEN_R
	GET_SUMS sEVENR
.ENDMACRO

.MACRO GET_EVEN_I
	GET_SUMS sEVENI
.ENDMACRO

.MACRO GET_ODD_R
	GET_SUMS sODDR
.ENDMACRO

.MACRO GET_ODD_I
	GET_SUMS sODDI
.ENDMACRO

.MACRO GET_SUMS
	push rTEMPB
		
	lds rTEMPA, @0 ; load high byte
	lds rTEMPB, @0 + 1 ; load low byte

	rcall ROUNDTRUNC ; round after truncation of low byte
	
	pop rTEMPB
.ENDMACRO



;------------------------------------------------------
; display routine
;------------------------------------------------------

.MACRO SHIFT_REGISTER_WRITE
	sbi PORTD, 2 ; set STCP storage clock pulse high and to ->
	cbi PORTD, 2 ; low
.ENDMACRO

.MACRO DISPLAY_ROUTINE_PUSH_ON_STACK
	
	push rTEMPA
	push rSPI_BUFFER
	push rDR_ROW_COUNTER
	push rDR_COLUMN_COUNTER

.ENDMACRO

.MACRO DISPLAY_ROUTINE_POP_FROM_STACK

	pop rDR_COLUMN_COUNTER
	pop rDR_ROW_COUNTER
	pop rSPI_BUFFER
	pop rTEMPA

.ENDMACRO

.MACRO DISPLAY_ROUTINE_WRITE_Z_POINTER_TO_SRAM
	sts sLED_Z_POINTER_LOW, ZL
	sts sLED_Z_POINTER_HIGH, ZH
.ENDMACRO

.MACRO DISPLAY_ROUTINE_READ_Z_POINTER_FROM_SRAM
	lds ZL, sLED_Z_POINTER_LOW
	lds ZH, sLED_Z_POINTER_HIGH
.ENDMACRO

