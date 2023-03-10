; Initialize SPI port
ld a, 0x90          ; Set up CR1 register (bits 7-4: baud rate, bit 2: master mode)
ld [spi_cr1], a

ld a, 0x02          ; Set up CR2 register (bit 1: software slave management, bit 0: SPI enable)
ld [spi_cr2], a

ld a, 0x00          ; Set up CR3 register (no interrupt)
ld [spi_cr3], a

; Send data over SPI
ld hl, tx_data      ; Load transmit data address into HL register
ld de, rx_data      ; Load receive data address into DE register
ld bc, tx_len       ; Load transmit length into BC register

ld a, 0x40          ; Set up CR1 register (bits 7-4: baud rate, bit 2: master mode, bit 6: enable transmit)
ld [spi_cr1], a

.loop:
    ld a, [hl]      ; Load next byte of transmit data into A register
    out (0x00), a   ; Send byte over SPI

    ld a, [spi_sr]  ; Wait for transmit buffer to be empty
    bit 1, a
    jr nz, .loop

    in a, (0x00)    ; Read received byte from SPI
    ld [de], a      ; Store received byte in receive buffer
    inc hl          ; Increment transmit buffer pointer
    inc de          ; Increment receive buffer pointer
    dec bc          ; Decrement transmit length
    jr nz, .loop    ; Repeat until all bytes have been sent/received

ld a, 0x00          ; Clear CR1 register (disable transmit)
ld [spi_cr1], a
