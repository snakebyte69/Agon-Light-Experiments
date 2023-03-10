; Include the BIOS equates
#include "biosequates.asm"

; Define the S-100 bus device address
#define DEVICE_ADDRESS 0x10

; Define the size of the receive buffer
#define BUFFER_SIZE 20

section .text

    ; Define the program entry point
    org 0x0100

    ; Initialize the stack pointer
    ld sp, 0xFFFE

    ; Initialize the BIOS vectors
    ld hl, BIOS_RESET
    ld (hl), jp
    ld hl, BIOS_CPM_JUMP
    ld (hl), jp
    ld hl, BIOS_CONOUT
    ld (hl), jp
    ld hl, BIOS_CONIN
    ld (hl), jp
    ld hl, BIOS_LSTOUT
    ld (hl), jp
    ld hl, BIOS_LISTST
    ld (hl), jp
    ld hl, BIOS_SETDMA
    ld (hl), jp
    ld hl, BIOS_SENSEIO
    ld (hl), jp
    ld hl, BIOS_SENSEDEV
    ld (hl), jp
    ld hl, BIOS_DISK_IO
    ld (hl), jp
    ld hl, BIOS_CLOCK
    ld (hl), jp
    ld hl, BIOS_SYSTEM_IO
    ld (hl), jp
    ld hl, BIOS_MEMORY_IO
    ld (hl), jp
    ld hl, BIOS_S100_IO
    ld (hl), jp

    ; Set up the S-100 bus port and data direction registers
    ld a, 0x3F ; Set all bits of the port to output
    out (0xF0), a
    ld a, 0x00 ; Set all bits of the data direction register to output
    out (0xF2), a

    ; Send message to device
    ld hl, message
    ld c, DEVICE_ADDRESS
    call send_message

    ; Receive response from device
    ld hl, response
    ld c, DEVICE_ADDRESS
    call receive_response

    ; Print response on console
    ld hl, response
    call bios_conout_string

    ; Exit program
    jp 0x0000

; Subroutine to send a message to the S-100 bus device
send_message:
    push bc
    push de

    ; Set the DMA address to the message buffer
    ld hl, message
    call bios_setdma

    ; Send the message
    ld b, BUFFER_SIZE
    ld d, c
    call bios_s100_io

    pop de
    pop bc
    ret

; Subroutine to receive a response from the S-100 bus device
receive_response:
    push bc
    push de

    ; Set the DMA address to the response buffer
    ld hl, response
    call bios_setdma

    ; Receive the response
    ld b, BUFFER_SIZE
    ld d, c
    call bios_s100_io

    pop de
    pop bc
    ret

; Define the message and response buffers
section .bss
    message: res BUFFER_SIZE
    response: res BUFFER
