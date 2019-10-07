#ifndef _DEFINITIONS_INC_
#define _DEFINITIONS_INC_

;------------------------------------------------------
; register labels
;------------------------------------------------------
.def rTEMPA = r16
.def rTEMPB = r17


; display routine
.def rSPI_BUFFER = r19
.def rROW_COUNTER = r20
.def rCOLUMN_COUNTER = r21


; FFT
.def rBIN_COUNTER = r18
.def rSUM_COUNTER = r19

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

; first FFT bin
.equ FFT_FIRST_BIN = 1

; last FFT bin
.equ FFT_LAST_BIN = 17

; FFT scaling factor
.equ FFT_SCALING_FACTOR = 2

; FFT vertical bins
.equ FFT_POWER_8 = 125
.equ FFT_POWER_7 = 110
.equ FFT_POWER_6 = 95
.equ FFT_POWER_5 = 80
.equ FFT_POWER_4 = 65
.equ FFT_POWER_3 = 50
.equ FFT_POWER_2 = 35
.equ FFT_POWER_1 = 20


#endif /* _DEFINITIONS_INC_ */
