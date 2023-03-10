; Snake fabGPL Experiments 10 March 2023
; fabgl::Canvas, that provides a set of drawing primitives (lines, rectangles, text...)

#include <ez80.h>
#include <stdint.h>
#include <stdio.h>

#define SPI_BASE 0xF0D000    // Address of SPI peripheral
#define SPI_CLK_DIV 3        // SPI clock divider

void spi_init() {
    // Set up SPI pins
    OUT_B(PB, 3);   // Set SS as output
    OUT_B(PB, 4);   // Set MOSI as output
    OUT_B(PB, 5);   // Set MISO as input
    OUT_B(PB, 6);   // Set SCLK as output

    // Configure SPI control registers
    WR_REG8(SPI_BASE + 0x02, 0x40);   // CPOL = 0, CPHA = 0
    WR_REG8(SPI_BASE + 0x03, 0x07);   // Master mode, Fosc/8
}

void spi_send(uint8_t data) {
    while (RD_REG8(SPI_BASE + 0x00) & 0x80);   // Wait for TX buffer to be empty
    WR_REG8(SPI_BASE + 0x01, data);             // Write data to TX buffer
    while (!(RD_REG8(SPI_BASE + 0x00) & 0x80)); // Wait for TX to complete
    RD_REG8(SPI_BASE + 0x01);                   // Read dummy data from RX buffer
}

void fabgl_canvas_command() {
    // Construct command packet
    uint8_t command[5] = {0x5A, 0x5A, 0x00, 0x00, 0x01};

    // Send command packet over SPI
    OUT_B(PB, 3) = 0;           // Set SS low to select ESP32
    for (int i = 0; i < 5; i++) {
        spi_send(command[i]);   // Send command byte over SPI
    }
    OUT_B(PB, 3) = 1;           // Set SS high to deselect ESP32
}

int main() {
    spi_init();           // Initialize SPI peripheral
    fabgl_canvas_command();// Send "Canvas" command to ESP32 via SPI
    return 0;
}
