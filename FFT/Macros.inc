
.MACRO SPI_WRITE
	out SPDR, @0
.ENDMACRO

.MACRO SHIFT_REGISTER_WRITE
	sbi PORTD, 2 ; set STCP storage clock pulse high and to ->
	cbi PORTD, 2 ; low
.ENDMACRO

/* 
.MACRO SETPINOUT ;
	ldi rTEMP, (1<<@1)
	out @0, rTEMP
.ENDMACRO

.MACRO SETPININ ;
	ldi rTEMP, (1<<@1)
	in @0, rTEMP
.ENDMACRO
*/

/*
.MACRO rTEMPeq0 ;
	ldi rTEMP, 0x00
.ENDMACRO


.MACRO rTEMPeq1 ;
	ldi rTEMP, 0xFF
.ENDMACRO
*/