#ifndef _DEFINITIONS_INC_
#define _DEFINITIONS_INC_


.def rTEMPA = r16
.def rTEMPB = r17
.def rCOUNTER = r18
.def rSPI_BUFFER = r19

; display routine
.def rDR_ROW_COUNTER = r20
.def rDR_COLUMN_COUNTER = r21


;------------------------------------------------------
; reserved
;------------------------------------------------------

; reserved for z pointer arithmetic
.def Z_POINTER_LOW = r30
.def Z_POINTER_HIGH = r31


;------------------------------------------------------
; misc
;------------------------------------------------------

; size of LED array in byte (one byte per LED)
.equ LED_ARRAY_SIZE = 128


#endif /* _DEFINITIONS_INC_ */
