; Snake fabGPL Experiments 10 March 2023
; fabgl::VIA6522, VIA 6522 emulator

VIA6522

; Set org to 100h for CP/M
org 100h

; Define constants for SPI registers
SPIDATA equ 8000h
SPICON equ 8002h
SPISTS equ 8004h

; Define constants for fabGL commands
VIA6522 equ 22h

; Setup SPI
ld a, 0h            ; Set up SPI control register
out (SPICON), a      ;   (master, mode 0, no interrupts)
ld a, 2h            ; Enable SPI
out (SPISTS), a

; Send command to ESP32
ld a, VIA6522 ; Load command into accumulator
out (SPIDATA), a     ; Send command via SPI

; Disable SPI
ld a, 0h            ; Disable SPI
out (SPISTS), a

; End of program
rst 0h              ; Return to CP/M
