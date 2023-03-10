#include <stdio.h>
#include <cpm.h>

// Define the S-100 bus device address
#define DEVICE_ADDRESS 0x10

// Define the size of the receive buffer
#define BUFFER_SIZE 20

int main() {
    // Set up the S-100 bus port and data direction registers
    _asm
        ld a, 0x3F ; Set all bits of the port to output
        out (0xF0), a
        ld a, 0x00 ; Set all bits of the data direction register to output
        out (0xF2), a
    _endasm;

    // Send message to device
    char message[BUFFER_SIZE] = "Hello, device!";
    _asm
        ld hl, message
        ld c, DEVICE_ADDRESS
        call send_message
    _endasm;

    // Receive response from device
    char response[BUFFER_SIZE];
    _asm
        ld hl, response
        ld c, DEVICE_ADDRESS
        call receive_response
    _endasm;

    // Print response on console
    printf("Response: %s\n", response);

    return 0;
}

// Subroutine to send a message to the S-100 bus device
void send_message(char* message, char device_address) {
    _asm
        push bc
        push de

        ; Set the DMA address to the message buffer
        ld hl, (#message)
        call bios_setdma

        ; Send the message
        ld b, BUFFER_SIZE
        ld d, c
        call bios_s100_io

        pop de
        pop bc
    _endasm;
}

// Subroutine to receive a response from the S-100 bus device
void receive_response(char* response, char device_address) {
    _asm
        push bc
        push de

        ; Set the DMA address to the response buffer
        ld hl, (#response)
        call bios_setdma

        ; Receive the response
        ld b, BUFFER_SIZE
        ld d, c
        call bios_s100_io

        pop de
        pop bc
    _endasm;
}
