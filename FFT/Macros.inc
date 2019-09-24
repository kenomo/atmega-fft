
;------------------------------------------------------
; SPI
;------------------------------------------------------

.MACRO SPI_WRITE
	out SPDR, @0
.ENDMACRO



;------------------------------------------------------
; FFT macros
;------------------------------------------------------

.MACRO ADD_EVEN_R
	ADD_TO_SUM @0, sEVENR
.ENDMACRO

.MACRO ADD_EVEN_I
	ADD_TO_SUM @0, sEVENI
.ENDMACRO

.MACRO ADD_ODD_R
	ADD_TO_SUM @0, sODDR
.ENDMACRO

.MACRO ADD_ODD_I
	ADD_TO_SUM @0, sODDI
.ENDMACRO

.MACRO ADD_TO_SUM ; @0 @1
	push XL
	push XH
	push r2
	push r3
	push r4

	ldi XL, low(@1)
    ldi XH, high(@1)

	ld r3, X+
	ld r2, X

	mov rTEMPA, @0
	EXPLODE8b16b rTEMPA, rTEMPB
	ADD16B rTEMPA, rTEMPB, r2, r3

	st X, rC1
	st -X, rC2

	pop r4
	pop r3
	pop r2
	pop XH
	pop XL
.ENDMACRO


.MACRO GET_EVEN_R
	ADD_TO_SUM @0, sEVENR
.ENDMACRO

.MACRO GET_EVEN_I
	ADD_TO_SUM @0, sEVENI
.ENDMACRO

.MACRO GET_ODD_R
	ADD_TO_SUM @0, sODDR
.ENDMACRO

.MACRO GET_ODD_I
	ADD_TO_SUM @0, sODDI
.ENDMACRO

.MACRO GET_SUMS ; @0 @1
	push XL
	push XH
	
	ldi XL, low(@1)
    ldi XH, high(@1)

	adiw X, 0x01

	ld @0, X
	
	pop XH
	pop XL
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

