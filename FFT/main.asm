; FFT

.include "Macros.inc"
.include "Definitions.inc"


; indicates that the next segment refers to program memory
.cseg
; the org directive is used to specify a location in program memory where the program following directive is to be placed.
.org 0 ; 

;------------------------------------------------------
; start address 0000
;------------------------------------------------------
RESET:
	rjmp INIT


;------------------------------------------------------
; interrupts definitions
;------------------------------------------------------
; ...


.org INT_VECTORS_SIZE ; end address of 


;------------------------------------------------------
; includes
;------------------------------------------------------
.include "SPI.inc"
.include "DisplayRoutine.inc"

;------------------------------------------------------
; initialize
;------------------------------------------------------
INIT:
	; set Stack Pointer
	ldi rTEMP, high(RAMEND)
	out SPH, rTEMP
	ldi rTEMP, low(RAMEND)
	out SPL, rTEMP

	; reserve some SRAM
	.dseg
	LED_ARRAY: .byte 128
	LED_ROW_COUNTER: .byte 1
	.cseg

	/*
	 * PB5: MOSI
	 * PB6: MISO
	 * PB7: SCK
	 * 
	 * PD0: TXD
	 * PD1: RXD
	 * PD2: SSCK
	 * PD3: OE
	 * PD4: MR
	 * 
	 */

	; set PBx and PDx as out
	ldi rTEMP, 0xFF
	out DDRB, rTEMP
	out DDRD, rTEMP
	
	; set PortB low, set PortD low (except for MR)
	ldi rTEMP, 0x00
	out PortB, rTEMP
	ldi rTEMP, (1<<4)
	out PortD, rTEMP
	
	
	; SPI initialize
	rcall SPI_MASTER_INIT
	

	//// for testing purpose
	ldi rROW_COUNTER, 0b00000000
	sts LED_ROW_COUNTER, rROW_COUNTER

	rcall DISPLAY_ROUTINE_FILL_DEBUG
	rcall DISPLAY_ROUTINE
	////

;------------------------------------------------------
; Program
;------------------------------------------------------
Program:

	rjmp Program

;------------------------------------------------------
; End
;------------------------------------------------------
End:

	rjmp End

