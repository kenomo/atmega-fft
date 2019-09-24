#ifndef _DEFINITIONS_INC_
#define _DEFINITIONS_INC_

;------------------------------------------------------
; register labels
;------------------------------------------------------
.def rTEMPA = r16
.def rTEMPB = r17


; display routine
.def rCOUNTER = r18
.def rSPI_BUFFER = r19
.def rDR_ROW_COUNTER = r20
.def rDR_COLUMN_COUNTER = r21


; FFT
.def rBIN_COUNTER = r18
.def rM_COUNTER = r19

.def rEXPR = r4
.def rEXPI = r5

; arithmetic
; out
.def ra16L = r12
.def ra16H = r13
.def rb16L = r14
.def rb16H = r15
.def rC1 = r12
.def rC2 = r13
.def rC3 = r14
.def rC4 = r15

; in
.def rA16L = r20
.def rA16H = r21
.def rB16L = r22
.def rB16H = r23


;------------------------------------------------------
; misc
;------------------------------------------------------

; size of LED array in byte (one byte per LED)
.equ LED_ARRAY_SIZE = 128

; size of FFT points
.equ FFT_POINT_SIZE = 128

#endif /* _DEFINITIONS_INC_ */
