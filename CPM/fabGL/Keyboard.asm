; Snake fabGPL Experiments 10 March 2023
; fabgl::Keyboard, that controls a PS2 keyboard and translates scancodes to virtual keys or ASCII/ANSI codes

; Set org to 100h for CP/M
org 100h

; Define constants for SPI registers
SPIDATA equ 8000h
SPICON equ 8002h
SPISTS equ 8004h

; Define constants for fabGL commands
Keyboard equ 22h

; Setup SPI
ld a, 0h            ; Set up SPI control register
out (SPICON), a      ;   (master, mode 0, no interrupts)
ld a, 2h            ; Enable SPI
out (SPISTS), a

; Send command to ESP32
ld a, Keyboard ; Load command into accumulator
out (SPIDATA), a     ; Send command via SPI

; Disable SPI
ld a, 0h            ; Disable SPI
out (SPISTS), a

; End of program
rst 0h              ; Return to CP/M
