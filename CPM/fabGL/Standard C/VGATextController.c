; Snake fabGPL Experiments 10 March 2023
; fabgl::VGATextController, device driver for VGA textual output (low RAM requirements, CPU intensive)

#include <ez80.h>

// SPI registers
#define SPCR (*(volatile unsigned char *)0xFFF3)
#define SPSR (*(volatile unsigned char *)0xFFF2)
#define SPDR (*(volatile unsigned char *)0xFFF1)

// Function to send data over SPI
void spi_send(unsigned char data) {
    SPDR = data;
    while (!(SPSR & (1 << 7)));
}

int main() {
    // Set up SPI
    SPCR = (1 << 6) | (1 << 4) | (1 << 0);
    SPSR = (1 << 0);

    // Send "VGATextController" command
    spi_send('V');
    spi_send('G');
    spi_send('A');
    spi_send('T');
    spi_send('e');
    spi_send('x');
    spi_send('t');
    spi_send('C');
    spi_send('o');
    spi_send('n');
    spi_send('t');
    spi_send('r');
    spi_send('o');
    spi_send('l');
    spi_send('l');
    spi_send('e');
    spi_send('r');

    return 0;
}
