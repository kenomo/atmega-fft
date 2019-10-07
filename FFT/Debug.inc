

DISPLAY_ROUTINE_FILL_DEBUG:

	; set z pointer to last entry of sLED_ARRAY
	ldi ZL, low(sLED_ARRAY + LED_ARRAY_SIZE)
    ldi ZH, high(sLED_ARRAY + LED_ARRAY_SIZE)

	ldi rTEMPA, 128
	rcall DISPLAY_ROUTINE_FILL_DISPLAY

	; set z pointer to first entry of sLED_ARRAY
	ldi ZL, low(sLED_ARRAY)
    ldi ZH, high(sLED_ARRAY)

	ldi rTEMPA, 0x00
	std Z + 0, rTEMPA
	std Z + 4, rTEMPA
	std Z + 8, rTEMPA
	std Z + 10, rTEMPA
	std Z + 11, rTEMPA
	std Z + 20, rTEMPA
	std Z + 22, rTEMPA
	std Z + 23, rTEMPA
	std Z + 25, rTEMPA
	std Z + 26, rTEMPA
	std Z + 28, rTEMPA
	std Z + 30, rTEMPA
	std Z + 31, rTEMPA
	std Z + 33, rTEMPA
	std Z + 35, rTEMPA
	std Z + 38, rTEMPA
	std Z + 42, rTEMPA
	std Z + 44, rTEMPA
	std Z + 50, rTEMPA
	std Z + 54, rTEMPA
	std Z + 60, rTEMPA
	std Z + 61, rTEMPA
	std Z + 62, rTEMPA
	std Z + 63, rTEMPA

	adiw ZH:ZL, 63

	ldi rTEMPA, 0x00
	std Z + 0, rTEMPA
	std Z + 4, rTEMPA
	std Z + 8, rTEMPA
	std Z + 10, rTEMPA
	std Z + 11, rTEMPA
	std Z + 20, rTEMPA
	std Z + 22, rTEMPA
	std Z + 23, rTEMPA
	std Z + 25, rTEMPA
	std Z + 26, rTEMPA
	std Z + 28, rTEMPA
	std Z + 30, rTEMPA
	std Z + 31, rTEMPA
	std Z + 33, rTEMPA
	std Z + 35, rTEMPA
	std Z + 38, rTEMPA
	std Z + 42, rTEMPA
	std Z + 44, rTEMPA
	std Z + 50, rTEMPA
	std Z + 54, rTEMPA
	std Z + 60, rTEMPA
	std Z + 61, rTEMPA
	std Z + 62, rTEMPA
	std Z + 63, rTEMPA
	
	ret


DISPLAY_ROUTINE_FILL_DISPLAY:

	ldi rTEMPA, 0xFF
	st -Z, rTEMPA

	dec rTEMPA

	cpi rTEMPA, 0x00 ; compare register immediate
	brne DISPLAY_ROUTINE_FILL_DISPLAY ; if rTEMPA not equal to 0x00 jump to ...

	ret


FFT_FILL_SRAM:
	
	ldi ZL, low(sFFT_POINTS)
    ldi ZH, high(sFFT_POINTS)

	ldi rTEMPA, 52
	st Z+, rTEMPA
	ldi rTEMPA, 86
	st Z+, rTEMPA
	ldi rTEMPA, 104
	st Z+, rTEMPA
	ldi rTEMPA, 101
	st Z+, rTEMPA
	ldi rTEMPA, 127
	st Z+, rTEMPA
	ldi rTEMPA, 109
	st Z+, rTEMPA
	ldi rTEMPA, 87
	st Z+, rTEMPA
	ldi rTEMPA, 92
	st Z+, rTEMPA
	ldi rTEMPA, 70
	st Z+, rTEMPA
	ldi rTEMPA, 44
	st Z+, rTEMPA
	ldi rTEMPA, 5
	st Z+, rTEMPA
	ldi rTEMPA, -12
	st Z+, rTEMPA
	ldi rTEMPA, -48
	st Z+, rTEMPA
	ldi rTEMPA, -5
	st Z+, rTEMPA
	ldi rTEMPA, -1
	st Z+, rTEMPA
	ldi rTEMPA, 3
	st Z+, rTEMPA
	ldi rTEMPA, 35
	st Z+, rTEMPA
	ldi rTEMPA, 77
	st Z+, rTEMPA
	ldi rTEMPA, 41
	st Z+, rTEMPA
	ldi rTEMPA, 51
	st Z+, rTEMPA
	ldi rTEMPA, 71
	st Z+, rTEMPA
	ldi rTEMPA, 53
	st Z+, rTEMPA
	ldi rTEMPA, 40
	st Z+, rTEMPA
	ldi rTEMPA, 20
	st Z+, rTEMPA
	ldi rTEMPA, 10
	st Z+, rTEMPA
	ldi rTEMPA, -18
	st Z+, rTEMPA
	ldi rTEMPA, -49
	st Z+, rTEMPA
	ldi rTEMPA, -86
	st Z+, rTEMPA
	ldi rTEMPA, -86
	st Z+, rTEMPA
	ldi rTEMPA, -52
	st Z+, rTEMPA
	ldi rTEMPA, -71
	st Z+, rTEMPA
	ldi rTEMPA, -33
	st Z+, rTEMPA
	ldi rTEMPA, -28
	st Z+, rTEMPA
	ldi rTEMPA, -14
	st Z+, rTEMPA
	ldi rTEMPA, 33
	st Z+, rTEMPA
	ldi rTEMPA, 34
	st Z+, rTEMPA
	ldi rTEMPA, 92
	st Z+, rTEMPA
	ldi rTEMPA, 53
	st Z+, rTEMPA
	ldi rTEMPA, 95
	st Z+, rTEMPA
	ldi rTEMPA, 58
	st Z+, rTEMPA
	ldi rTEMPA, 40
	st Z+, rTEMPA
	ldi rTEMPA, -27
	st Z+, rTEMPA
	ldi rTEMPA, -11
	st Z+, rTEMPA
	ldi rTEMPA, -49
	st Z+, rTEMPA
	ldi rTEMPA, -23
	st Z+, rTEMPA
	ldi rTEMPA, -53
	st Z+, rTEMPA
	ldi rTEMPA, -49
	st Z+, rTEMPA
	ldi rTEMPA, -76
	st Z+, rTEMPA
	ldi rTEMPA, -41
	st Z+, rTEMPA
	ldi rTEMPA, -69
	st Z+, rTEMPA
	ldi rTEMPA, -44
	st Z+, rTEMPA
	ldi rTEMPA, -40
	st Z+, rTEMPA
	ldi rTEMPA, -73
	st Z+, rTEMPA
	ldi rTEMPA, -78
	st Z+, rTEMPA
	ldi rTEMPA, -51
	st Z+, rTEMPA
	ldi rTEMPA, -52
	st Z+, rTEMPA
	ldi rTEMPA, -52
	st Z+, rTEMPA
	ldi rTEMPA, -49
	st Z+, rTEMPA
	ldi rTEMPA, -60
	st Z+, rTEMPA
	ldi rTEMPA, -29
	st Z+, rTEMPA
	ldi rTEMPA, -44
	st Z+, rTEMPA
	ldi rTEMPA, -39
	st Z+, rTEMPA
	ldi rTEMPA, -14
	st Z+, rTEMPA
	ldi rTEMPA, -20
	st Z+, rTEMPA
	ldi rTEMPA, 22
	st Z+, rTEMPA
	ldi rTEMPA, 51
	st Z+, rTEMPA
	ldi rTEMPA, 6
	st Z+, rTEMPA
	ldi rTEMPA, 15
	st Z+, rTEMPA
	ldi rTEMPA, 42
	st Z+, rTEMPA
	ldi rTEMPA, 60
	st Z+, rTEMPA
	ldi rTEMPA, 69
	st Z+, rTEMPA
	ldi rTEMPA, 64
	st Z+, rTEMPA
	ldi rTEMPA, 37
	st Z+, rTEMPA
	ldi rTEMPA, 32
	st Z+, rTEMPA
	ldi rTEMPA, 57
	st Z+, rTEMPA
	ldi rTEMPA, 39
	st Z+, rTEMPA
	ldi rTEMPA, 79
	st Z+, rTEMPA
	ldi rTEMPA, 41
	st Z+, rTEMPA
	ldi rTEMPA, 70
	st Z+, rTEMPA
	ldi rTEMPA, 62
	st Z+, rTEMPA
	ldi rTEMPA, 47
	st Z+, rTEMPA
	ldi rTEMPA, 40
	st Z+, rTEMPA
	ldi rTEMPA, 42
	st Z+, rTEMPA
	ldi rTEMPA, 50
	st Z+, rTEMPA
	ldi rTEMPA, 46
	st Z+, rTEMPA
	ldi rTEMPA, -20
	st Z+, rTEMPA
	ldi rTEMPA, -33
	st Z+, rTEMPA
	ldi rTEMPA, -33
	st Z+, rTEMPA
	ldi rTEMPA, -80
	st Z+, rTEMPA
	ldi rTEMPA, -44
	st Z+, rTEMPA
	ldi rTEMPA, -75
	st Z+, rTEMPA
	ldi rTEMPA, -28
	st Z+, rTEMPA
	ldi rTEMPA, 4
	st Z+, rTEMPA
	ldi rTEMPA, -14
	st Z+, rTEMPA
	ldi rTEMPA, -18
	st Z+, rTEMPA
	ldi rTEMPA, 57
	st Z+, rTEMPA
	ldi rTEMPA, 36
	st Z+, rTEMPA
	ldi rTEMPA, 54
	st Z+, rTEMPA
	ldi rTEMPA, 56
	st Z+, rTEMPA
	ldi rTEMPA, 41
	st Z+, rTEMPA
	ldi rTEMPA, 41
	st Z+, rTEMPA
	ldi rTEMPA, 35
	st Z+, rTEMPA
	ldi rTEMPA, 16
	st Z+, rTEMPA
	ldi rTEMPA, -12
	st Z+, rTEMPA
	ldi rTEMPA, -33
	st Z+, rTEMPA
	ldi rTEMPA, -38
	st Z+, rTEMPA
	ldi rTEMPA, -77
	st Z+, rTEMPA
	ldi rTEMPA, -60
	st Z+, rTEMPA
	ldi rTEMPA, -82
	st Z+, rTEMPA
	ldi rTEMPA, -57
	st Z+, rTEMPA
	ldi rTEMPA, -36
	st Z+, rTEMPA
	ldi rTEMPA, -23
	st Z+, rTEMPA
	ldi rTEMPA, -21
	st Z+, rTEMPA
	ldi rTEMPA, 13
	st Z+, rTEMPA
	ldi rTEMPA, 30
	st Z+, rTEMPA
	ldi rTEMPA, 17
	st Z+, rTEMPA
	ldi rTEMPA, -16
	st Z+, rTEMPA
	ldi rTEMPA, -15
	st Z+, rTEMPA
	ldi rTEMPA, -49
	st Z+, rTEMPA
	ldi rTEMPA, -74
	st Z+, rTEMPA
	ldi rTEMPA, -81
	st Z+, rTEMPA
	ldi rTEMPA, -128
	st Z+, rTEMPA
	ldi rTEMPA, -110
	st Z+, rTEMPA
	ldi rTEMPA, -77
	st Z+, rTEMPA
	ldi rTEMPA, -80
	st Z+, rTEMPA
	ldi rTEMPA, -77
	st Z+, rTEMPA
	ldi rTEMPA, -24
	st Z+, rTEMPA
	ldi rTEMPA, -24
	st Z+, rTEMPA

	ret