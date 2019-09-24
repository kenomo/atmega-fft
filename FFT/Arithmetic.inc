
;------------------------------------------------------
; arithmetic
;------------------------------------------------------

; TODO: twos complement saturation arithmetic...
; A + B -> C
.MACRO ADD16B ; @0: low A, @1: high A, @2: low B, @3: high B
	mov r16L, @0
	mov r16H, @1
	
	add r16L, @2
	adc r16H, @3

	brcs SET_16B_SATURATION
.ENDMACRO

SET_16B_SATURATION:
	ldi r16L, 0b11111111
	ldi r16H, 0b11111111
	ret