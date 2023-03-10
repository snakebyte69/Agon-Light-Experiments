; Snake fabGPL Experiments
; fabgl::VGA2Controller, device driver for VGA 2 colors bitmapped output (low RAM requirements, CPU intensive)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define ESP32_CS_PIN  1  // Change this to the CS pin connected to the ESP32

void spi_init(void) {
    // TODO: Configure the SPI hardware registers as necessary for eZ80
}

void spi_send_byte(uint8_t data) {
    // TODO: Send a byte of data over SPI to the ESP32
}

void send_vga2_command(void) {
    uint8_t command[5] = {0xAA, 0x55, 0x01, 0x02, 0x00};  // VGA2Controller command
    for (int i = 0; i < 5; i++) {
        spi_send_byte(command[i]);
    }
}

int main(void) {
    spi_init();
    // Enable ESP32 CS pin
    // ...
    send_vga2_command();
    // Disable ESP32 CS pin
    // ...
    return 0;
}
