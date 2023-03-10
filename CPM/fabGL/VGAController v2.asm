; Set org address to 100h
  org 100h

; Setup SPI port and select the ESP32 device
  ld a, 0FFh ; Set initial value for output port
  out (8), a ; Write to SPI control register to enable chip select
  ld a, 0EFh ; Set chip select for the ESP32
  out (8), a ; Write to SPI control register to select ESP32

; Send VGAController command to ESP32
  ld a, 2 ; Length of command (2 bytes)
  out (9), a ; Write to SPI data register to send length
  ld hl, VGAController ; Load address of VGA8Controller command
  ld de, VGAControllerBuffer ; Load address of buffer to store command
  ld bc, 2 ; Copy 2 bytes from command to buffer
  ldir ; Copy command to buffer
  ld a, 0 ; Set length to 0 to indicate end of transmission
  out (9), a ; Write to SPI data register to send length

; Disable chip select and end program
  ld a, 0FFh ; Set all output pins to high (disable chip select)
  out (8), a ; Write to SPI control register to disable chip select
  ret ; End program

; VGAController command bytes
  VGAController:
    db 0x10, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  VGAControllerBuffer:
    db 0, 0 ; Buffer to store command and length bytes
