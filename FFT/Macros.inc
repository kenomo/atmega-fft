
.MACRO SPI_WRITE
	out SPDR, @0
.ENDMACRO

.MACRO SHIFT_REGISTER_WRITE
	sbi PORTD, 2 ; set STCP storage clock pulse high and to ->
	cbi PORTD, 2 ; low
.ENDMACRO
