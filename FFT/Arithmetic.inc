
;------------------------------------------------------
; arithmetic
;------------------------------------------------------


;------------------------------------------------------
; explode 8b signed to 16b signed
;------------------------------------------------------
; @0 low
; @1 high
.MACRO EXPLODE8B16B
    ldi @1, 127
    cp @1, @0
    sbc @1, @1
.ENDMACRO


;------------------------------------------------------
; round signed 8b after 16b-8b truncation
;------------------------------------------------------
; rTEMPA: high byte
; rTEMPB: low byte
; uses r22 !!!
ROUNDTRUNC:

	; check if modulo is greater or equal than half of 2^8
	; for positive numbers -> 0..127
	; for negative numbers -> 0..128
	ldi r22, 128
	sbrc rTEMPA, 7
	ldi r22, 129

	sub rTEMPB, r22
	brlo ROUNDTRUNC_END

	ldi rTEMPB, 0x01
	add rTEMPA, rTEMPB ; add a one

	brvc ROUNDTRUNC_END ; branch if overflow flag is cleared -> no overflow
	ldi rTEMPA, 127 ; -> saturation on overflow
	
ROUNDTRUNC_END:
	ret


;------------------------------------------------------
; scale 32b -> 16b 
;------------------------------------------------------
; rC4:rC3:rC2:rC1 / 2^FFT_SCALING_FACTOR -> rC2:rC1
SCALE32B16B:
    push rTEMPA

	ldi rTEMPA, 0x00

SCALE32B16B_LOOP:
	sbrc rC4, 7 ; skip if bit in register is cleared
	sec ; set carry flag -> number is negative
	
	ror rC4
	ror rC3
	ror rC2
	ror rC1

	inc rTEMPA ; increase loop counter
	cpi rTEMPA, FFT_SCALING_FACTOR ; compare
	brne SCALE32B16B_LOOP ; loop

	; TODO: check if rC4:rC3 is zero

	pop rTEMPA

	ret


;------------------------------------------------------
; add two 16b numbers
;------------------------------------------------------
; A + B -> C
; C = rC2:rC1
.MACRO ADD16B ; @0: low A, @1: high A, @2: low B, @3: high B
	mov rC1, @0
	mov rC2, @1
	
	add rC1, @2
	adc rC2, @3

	;brvs ADD16B_OVERFLOW ; branch if overflow flag is set
	
.ENDMACRO

ADD16B_OVERFLOW:
	; TODO:	
	ret


;------------------------------------------------------
; mul two 16b numbers -> 32b
;------------------------------------------------------
; A * B -> C
; rC4:rC3:rC2:rC1 = @3:@2 * @1:@0
.MACRO MUL16B ; @0: low A, @1: high A, @2: low B, @3: high B
	clr	r2
	muls @3, @1
	movw rC4:rC3, r1:r0
	mul	@2, @0
	movw rC2:rC1, r1:r0
	mulsu @3, @0
	sbc	rC4, r2
	add	rC2, r0
	adc	rC3, r1
	adc	rC4, r2
	mulsu @1, @2
	sbc	rC4, r2
	add	rC2, r0
	adc	rC3, r1
	adc	rC4, r2
.ENDMACRO


;------------------------------------------------------
; mul two 16b numbers -> 16b
;------------------------------------------------------
; A * B -> C
; rC2:rC1 = @3:@2 * @1:@0
.MACRO MUL16B16 ; @0: low A, @1: high A, @2: low B, @3: high B
	mul	@2, @0
	movw rC2:rC1, r1:r0
	mul	@3, @0
	add	rC2, r0
	mul	@1, @2
	add	rC2, r0
.ENDMACRO
