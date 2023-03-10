; Define the SPI pins on the ESP32
SPI_SCLK equ 18
SPI_MOSI equ 23
SPI_CS equ 5

; Initialize the SPI interface
LD HL, SPI_SCLK  ; Load the SCLK pin number
LD B, 0x01      ; Set the SPI clock speed to 1 MHz
CALL init_spi

; Initialize the SSD1306 controller
LD HL, 0x78     ; Set the SSD1306 controller address to 0x78 (default)
LD B, 0x80      ; Set the control byte to indicate a command (0x80)
LD C, 0xAE      ; Send the command to turn off the display
CALL send_spi

; Send the display data
LD HL, 0x40     ; Set the SSD1306 display data address to 0x40 (default)
LD B, 0x40      ; Set the control byte to indicate data (0x40)
LD C, 0xFF      ; Send the first pixel data (white)
CALL send_spi
LD C, 0x00      ; Send the second pixel data (black)
CALL send_spi
; Repeat for all the pixels in the display

; Initialize the SPI interface
init_spi:
  LD A, 0x01    ; Set the SPI interface to mode 0,0 (CPOL=0, CPHA=0)
  LD (0xFFFE), A ; Write to the ESP32 SPI mode register
  LD A, 0x0F    ; Enable the SPI peripheral and set the clock divider to 15
  LD (0xFFFC), A ; Write to the ESP32 SPI control register
  RET

; Send an SPI command or data byte
send_spi:
  LD E, A       ; Save the byte to send in register E
  LD A, B       ; Load the control byte into register A
  OUT (SPI_CS), A ; Set the SPI chip select line
  LD A, E       ; Load the byte to send into register A
  OUT (SPI_MOSI), A ; Send the byte via the SPI MOSI line
  IN A, (SPI_MISO) ; Read the byte from the SPI MISO line (discard it)
  OUT (SPI_CS), 0 ; Clear the SPI chip select line
  RET
