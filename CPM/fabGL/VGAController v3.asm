; Snake fabGPL Experiments 10 March 2023
; fabgl::VGAController, device driver for VGA bitmapped output

; Set org to 100h for CP/M
	org 100h

	; Initialize the SPI interface
	ld a, 4		; Set SPI speed to Fosc/4 (1 MHz at 4 MHz clock)
	out (7), a	; Send control byte to SPI port
	ld a, 64	; Set SPI control byte for master mode, MSB first, enable SPI
	out (7), a	; Send control byte to SPI port

	; Send the VGAController command
	ld a, 0x80	; VGAController command code
	out (7), a	; Send command code to SPI port

	; Wait for transfer to complete
wait:
	in a, (6)	; Read status register from SPI port
	and 0x80	; Mask out all but transfer complete bit
	jr nz, wait	; Wait until transfer is complete

	; End of program
	ret
