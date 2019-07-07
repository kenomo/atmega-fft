

/* Enable SPI, Master, set clock rate fck/16 */
SPI_MASTER_INIT:
	ldi rTEMP, (1<<SPE)|(1<<MSTR)|(1<<SPR0)
	out SPCR, rTEMP

	ret

/* Wait for message transmitted */
SPI_WAIT_FOR_TRANSMIT:
	in rTEMP, SPSR
	sbrs rTEMP, SPIF
		rjmp SPI_WAIT_FOR_TRANSMIT

	ret
