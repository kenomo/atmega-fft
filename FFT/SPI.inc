
/* Enable SPI, Master, set clock rate fck/16 */
SPI_MASTER_INIT:
	; MSTR: set as master
	; SPI2X: fosc/2
	; SPE: SPI enable
	ldi rTEMP, (1<<SPE)|(1<<MSTR)|(1<<SPI2X)
	out SPCR, rTEMP

	ret


/* Wait for message transmitted */
SPI_WAIT_FOR_TRANSMIT:
	in rTEMP, SPSR
	sbrs rTEMP, SPIF
		rjmp SPI_WAIT_FOR_TRANSMIT

	ret
