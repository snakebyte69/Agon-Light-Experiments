; Snake fabGPL Experiments 10 March 2023
; fabgl::Terminal, that emulates an ANSI/VT100/VT102/etc and up terminal (look at vttest score)

#include <stdint.h>
#include <cpm.h>
#include <ez80.h>

// SPI communication constants
#define SPI_MASTER_SS 0x80    // SS bit on eZ80
#define SPI_FREQUENCY 100000 // SPI frequency in Hz

// fabGL Terminal command
const uint8_t terminal_command[] = {0x55, 0x54, 0x0B, 0x01, 0x05};

void init_spi() {
    // Set SS and MOSI as output pins
    EZ80_PBDR |= (1 << 7) | (1 << 5);
    // Set SCLK as input pin
    EZ80_PBDDR &= ~(1 << 6);
    // Enable SPI master mode
    EZ80_PEDR &= ~(1 << 6);
    // Set SPI clock frequency
    EZ80_SPCR = (1 << 7) | (1 << 0);
    EZ80_SPCR &= ~(1 << 1);
    EZ80_SPSR = 0;
    EZ80_SPR = ((F_CPU / SPI_FREQUENCY) >> 1) - 1;
}

void spi_send(const uint8_t* data, uint8_t length) {
    uint8_t i;
    for (i = 0; i < length; i++) {
        // Write data to SPI register
        EZ80_SPDR = data[i];
        // Wait for transfer to complete
        while (!(EZ80_SPSR & (1 << 7)));
    }
}

int main() {
    // Initialize SPI communication
    init_spi();
    // Send Terminal command
    spi_send(terminal_command, sizeof(terminal_command));
    return 0;
}
