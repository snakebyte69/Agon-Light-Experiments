; Snake fabGPL Experiments
; fabgl::VGA8Controller, device driver for VGA 8 colors bitmapped output (low RAM requirements, CPU intensive)

#include <stdio.h>
#include <stdlib.h>
#include <ez80.h>

#define SPI_SCK_PIN  23
#define SPI_MOSI_PIN 22
#define SPI_MISO_PIN 19
#define SPI_SS_PIN   18

#define CMD_VGA8CONTROLLER 0x10

void setup_spi() {
    // Set up SPI pins
    pinMode(SPI_SCK_PIN, OUTPUT);
    pinMode(SPI_MOSI_PIN, OUTPUT);
    pinMode(SPI_MISO_PIN, INPUT);
    pinMode(SPI_SS_PIN, OUTPUT);

    // Set up SPI control register
    outp(0xBF21, 0x50); // CPOL=0, CPHA=0, MSB first
    outp(0xBF22, 0x00); // 8 bits per transfer
    outp(0xBF23, 0x00); // Disable interrupt, SPI enabled
}

void spi_send(uint8_t command) {
    // Select slave device
    digitalWrite(SPI_SS_PIN, LOW);

    // Send command byte
    outp(0xBF20, command);

    // Wait for transfer to complete
    while ((inp(0xBF23) & 0x02) == 0);

    // Deselect slave device
    digitalWrite(SPI_SS_PIN, HIGH);
}

int main() {
    setup_spi();
    spi_send(CMD_VGA8CONTROLLER);
    return 0;
}
