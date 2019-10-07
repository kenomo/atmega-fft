;------------------------------------------------------
; Debug
;------------------------------------------------------
.MACRO DEBUG_FFT_START
	sbi PortC, 6
.ENDMACRO
.MACRO DEBUG_FFT_STOP
	cbi PortC, 6
.ENDMACRO

.MACRO DEBUG_DR_START
	sbi PortC, 7
.ENDMACRO
.MACRO DEBUG_DR_STOP
	cbi PortC, 7
.ENDMACRO


;------------------------------------------------------
; SPI
;------------------------------------------------------
.MACRO SPI_WRITE
	out SPDR, @0
.ENDMACRO


;------------------------------------------------------
; FFT macros
;------------------------------------------------------
.MACRO ADD_EVEN_R ; add r1:r0
	ADD_TO_SUM sEVENR
.ENDMACRO

.MACRO ADD_EVEN_I ; add r1:r0
	ADD_TO_SUM sEVENI
.ENDMACRO

.MACRO ADD_ODD_R ; add r1:r0
	ADD_TO_SUM sODDR
.ENDMACRO

.MACRO ADD_ODD_I ; add r1:r0
	ADD_TO_SUM sODDI
.ENDMACRO

.MACRO ADD_TO_SUM ; add r1:r0, address @0
	
	; load summand from sram
	lds r3, @0
	lds r2, @0 + 1

	mov rTEMPA, r1 ; high byte
	mov rTEMPB, r0 ; low byte
	rcall ROUNDTRUNC ; round after truncation of low byte
	
	EXPLODE8b16b rTEMPA, rTEMPB

	add rTEMPA, r2
	adc rTEMPB, r3 ; TODO: overflow handling

	; store new summand to sram
	sts @0 + 1, rTEMPA
	sts @0, rTEMPB

	/*
	st Z, rC2 ; debug: sum iterations
	adiw ZH:ZL, 0x01 ; debug: sum iterations
	st Z, rC1 ; debug: sum iterations
	adiw ZH:ZL, 0x01 ; debug: sum iterations
	*/
	
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

.MACRO GET_SUMS ; byte is in rTEMPA
		
	lds rTEMPA, @0 ; load high byte
	lds rTEMPB, @0 + 1 ; load low byte

	push r22
	rcall ROUNDTRUNC ; round after truncation of low byte
	pop r22
	
.ENDMACRO



;------------------------------------------------------
; display routine
;------------------------------------------------------

.MACRO SHIFT_REGISTER_WRITE
	sbi PORTD, 2 ; set STCP storage clock pulse high and to ->
	cbi PORTD, 2 ; low
.ENDMACRO

.MACRO DISPLAY_ROUTINE_PUSH_STACK
	
	push rTEMPA
	push rSPI_BUFFER
	push rROW_COUNTER
	push rCOLUMN_COUNTER
	push ZL
	push ZH
	push r0
	push r1
	
	in rTEMPA, SREG ; status register
	push rTEMPA

.ENDMACRO

.MACRO DISPLAY_ROUTINE_POP_STACK

	pop rTEMPA
	out SREG, rTEMPA

	pop r1
	pop r0
	pop ZH
	pop ZL
	pop rCOLUMN_COUNTER
	pop rROW_COUNTER
	pop rSPI_BUFFER
	pop rTEMPA

.ENDMACRO

.MACRO DISPLAY_ROUTINE_WRITE_Z_POINTER_TO_SRAM
	sts sLED_Z_POINTER_L, ZL
	sts sLED_Z_POINTER_H, ZH
.ENDMACRO

.MACRO DISPLAY_ROUTINE_READ_Z_POINTER_FROM_SRAM
	lds ZL, sLED_Z_POINTER_L
	lds ZH, sLED_Z_POINTER_H
.ENDMACRO

