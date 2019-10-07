
USART_INIT:

	; set baud rate
	ldi rTEMPA, 0x00
	sts UBRR0H, rTEMPA
	ldi rTEMPA, 4
	sts UBRR0L, rTEMPA

	ldi rTEMPA, (1<<U2X0)
	sts UCSR0A, rTEMPA

	; enable transmitter
	ldi rTEMPA, (1<<TXEN0)
	sts UCSR0B, rTEMPA

	; set frame format: 8 bit data, 1 stop bit
	ldi rTEMPA, (1<<UCSZ00)|(1<<UCSZ01)
	sts UCSR0C, rTEMPA

	ret


USART_TRANSMIT:

	; wait for empty transmit buffer
	SKBS UCSR0A, UDRE0, rTEMPB
	; UDRE0: USART Data Register Empty
	rjmp USART_TRANSMIT

	; put data into buffer, sends the data
	sts UDR0, rTEMPA

	ret