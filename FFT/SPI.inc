
/* enable SPI, set as master, set clock rate fck/16 */
SPI_MASTER_INIT:
	; MSTR: set as master
	; SPI2X: fosc/2
	; SPE: SPI enable
	; SPIE: SPI Interrupt Enable
	ldi rTEMPA, (1<<SPE)|(1<<MSTR)|(1<<SPI2X)|(1<<SPIE)
	out SPCR, rTEMPA

	ret

/* wait for message transmitted */
SPI_WAIT_FOR_TRANSMIT:
	in rTEMPA, SPSR
	sbrs rTEMPA, SPIF
		rjmp SPI_WAIT_FOR_TRANSMIT

	ret
