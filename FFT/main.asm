; FFT

.include "Macros.inc"
.include "Definitions.inc"

.include "sin_cos.inc"
.include "sqrt.inc"

; indicates that the next segment refers to program memory
.cseg
; the org directive is used to specify a location in program memory where the program following directive is to be placed.
.org 0x00

;------------------------------------------------------
; start address 0000
;------------------------------------------------------
RESET:
	rjmp INIT


;------------------------------------------------------
; interrupts definitions
;------------------------------------------------------

.org OVF0addr ; Timer/Counter0 Overflow interrupt address
	jmp DISPLAY_ROUTINE

.org SPIaddr ; SPI Serial Transfer Complete interrupt address
	jmp DISPLAY_ROUTINE

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


	;------------------------------------------------------
	; stack
	;------------------------------------------------------
	; set Stack Pointer
	ldi rTEMPA, high(RAMEND)
	out SPH, rTEMPA
	ldi rTEMPA, low(RAMEND)
	out SPL, rTEMPA


	;------------------------------------------------------
	; data segment
	;------------------------------------------------------
	; reserve some SRAM
	.dseg ; data segment
		
		sLED_ARRAY: .byte LED_ARRAY_SIZE
		sLED_PROGRAM: .byte 1
		sLED_ROW_COUNTER: .byte 1
		sLED_Z_POINTER_LOW: .byte 1
		sLED_Z_POINTER_HIGH: .byte 1

	.cseg ; program memory segment


	;------------------------------------------------------
	; IO
	;------------------------------------------------------
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
	ldi rTEMPA, 0xFF
	out DDRB, rTEMPA
	out DDRD, rTEMPA
	
	; set PortB low, set PortD low (except for MR)
	ldi rTEMPA, 0x00
	out PortB, rTEMPA
	ldi rTEMPA, (1<<4)
	out PortD, rTEMPA
	

	;------------------------------------------------------
	; interrupt
	;------------------------------------------------------
	
	; set 8bit timer/counter 0
	ldi rTEMPA, (1<<CS01) ; set clock select bit (see p. 107)
	out TCCR0B, rTEMPA ; Timer/Counter 0 Control Register B

	; set interrupt
	ldi rTEMPA, (1<<TOIE0) ; TOIE0: interrupt at timer overflow
	sts TIMSK0, rTEMPA ; Timer/Counter 0 Interrupt Mask Register


	;------------------------------------------------------
	; spi
	;------------------------------------------------------
	; SPI initialize
	rcall SPI_MASTER_INIT
	

	;------------------------------------------------------
	; display routine
	;------------------------------------------------------
	; initialize row counter
	ldi rDR_ROW_COUNTER, 0b0000001
	sts sLED_ROW_COUNTER, rDR_ROW_COUNTER
	
	; initialize display routine position
	ldi rTEMPA, 0b0
	sts sLED_PROGRAM, rTEMPA

	; for testing
	rcall DISPLAY_ROUTINE_FILL_DEBUG
	
	
	;------------------------------------------------------
	; misc
	;------------------------------------------------------
	sei ; global interrupt enable


;------------------------------------------------------
; program
;------------------------------------------------------
	
Program:
	

	rjmp Program

;------------------------------------------------------
; end
;------------------------------------------------------
End:

	rjmp End
