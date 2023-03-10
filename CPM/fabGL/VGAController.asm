; Initialize SPI port
LD A, 0b00000100  ; Enable SPI
OUT (0x01), A     ; Write to control register
LD A, 0b00000011  ; Set SPI clock speed to 1MHz
OUT (0x02), A     ; Write to clock register

; Initialize FabGL command
LD HL, cmd_vga ; Load address of command buffer
LD DE, spi_buffer ; Load address of SPI buffer
LD BC, cmd_length ; Load command buffer length

; Send command via SPI
ld a, (bc)
ld b, 0
ld c, a
ld a, (de)
rst 0x38          ; Send byte via SPI
inc bc
inc de
djnz $-7         ; Loop for the rest of the bytes

; Exit program
RET

; Command buffer for fabgl::VGAController
cmd_vga:
.DB 0x00, 0x00     ; Command code for fabgl::VGAController
.DB 0x00, 0x00     ; X-coordinate of top-left corner of display
.DB 0x00, 0x00     ; Y-coordinate of top-left corner of display
.DB 0x00, 0x00     ; Width of display in pixels
.DB 0x00, 0x00     ; Height of display in pixels
.DB 0x00           ; End of command buffer

; Length of command buffer
cmd_length:
.DB $ - cmd_vga

; SPI buffer for sending command
spi_buffer:
.DB 0x00
