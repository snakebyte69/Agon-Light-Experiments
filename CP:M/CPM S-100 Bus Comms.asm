; This program communicates with a device via the S-100 bus on a Microbee CP/M

; Define constants
.equ BDOS, 5 ; CP/M BDOS function
.equ C_READ, 2 ; CP/M console input function
.equ C_WRITE, 9 ; CP/M console output function
.equ SIO_PORT, 1FEh ; S-100 I/O port for SIO

; Define variables
.org 100h ; Set starting address
message: db 'Hello, device!' ; Message to send to device
buffer: ds 20 ; Receive buffer

; Define main program
start:
    call send_message ; Send message to device
    call receive_response ; Receive response from device
    call print_response ; Print response on console
    ret ; End program

; Send message to device
send_message:
    ld hl, message ; Load message address into HL
    call send_sio ; Call function to send message
    ret ; Return from function

; Receive response from device
receive_response:
    ld hl, buffer ; Load buffer address into HL
    call receive_sio ; Call function to receive response
    ret ; Return from function

; Print response on console
print_response:
    ld hl, buffer ; Load buffer address into HL
    call print_string ; Call function to print response
    ret ; Return from function

; Send data to SIO device
send_sio:
    push af ; Save AF
    ld a, (hl) ; Load A with next character
    or a ; Test if end of message
    jp z, send_done ; Jump if end of message
    out (SIO_PORT), a ; Send character to SIO
    inc hl ; Increment buffer pointer
    jr send_sio ; Loop for next character
send_done:
    pop af ; Restore AF
    ret ; Return from function

; Receive data from SIO device
receive_sio:
    push af ; Save AF
    ld hl, buffer ; Load HL with buffer address
receive_loop:
    in a, (SIO_PORT) ; Receive character from SIO
    ld (hl), a ; Store character in buffer
    inc hl ; Increment buffer pointer
    cp CR ; Test for carriage return
    jp z, receive_done ; Jump if carriage return
    jr receive_loop ; Loop for next character
receive_done:
    pop af ; Restore AF
    ret ; Return from function

; Print string on console
print_string:
    push bc ; Save BC
    ld b, 0 ; Load B with 0
    ld c, C_WRITE ; Load C with console output function
print_loop:
    ld a, (hl) ; Load A with next character
    or a ; Test if end of message
    jp z, print_done ; Jump if end of message
    call BDOS ; Call BDOS function to print character
    inc hl ; Increment buffer pointer
    jr print_loop ; Loop for next character
print_done:
    pop bc ; Restore BC
    ret ; Return from function
