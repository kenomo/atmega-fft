
;------------------------------------------------------
; arithmetic
;------------------------------------------------------


;------------------------------------------------------
; explode 8b signed to 16b signed
;------------------------------------------------------
; @0 low
; @1 high
.MACRO EXPLODE8b16b
    ldi @1, 127
    cp @1, @0
    sbc @1, @1
.ENDMACRO


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

	; TODO: add saturation, twos complement saturation arithmetic...

.ENDMACRO

/*
; add two 16B numbers
ldi rA16L, 0x12
ldi rA16H, 0x23
ldi rB16L, 0x34
ldi rB16H, 0x45

ADD16B rA16L, rA16H, rB16L, rB16H
*/


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

/*
; mul two 16B numbers
ldi rA16L, 0xF4
ldi rA16H, 0x01
ldi rB16L, 0x0C
ldi rB16H, 0xFE

MUL16B rA16L, rA16H, rB16L, rB16H
*/


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