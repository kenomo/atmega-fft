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

.def rEXPR = r20
.def rEXPI = r21

.def rTEMPCL = r22
.def rTEMPCH = r23
.def rTEMPDL = r24
.def rTEMPDH = r25

.def pEVENL = r26
.def pEVENH = r27
.def pODDL = r28
.def pODDH = r29


; arithmetic
.def rC1 = r12
.def rC2 = r13
.def rC3 = r14
.def rC4 = r15


;------------------------------------------------------
; misc
;------------------------------------------------------

; size of LED array in byte (one byte per LED)
.equ LED_ARRAY_SIZE = 128

; size of FFT points
.equ FFT_POINT_SIZE = 128

#endif /* _DEFINITIONS_INC_ */
