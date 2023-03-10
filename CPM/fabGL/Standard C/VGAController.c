// Snake fabGPL Experiments
// fabgl::VGAController, device driver for VGA bitmapped output

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cpm.h>

#define SPI_SS_PIN 0x80 // Use Bit 7 to control slave select (SS) pin
#define SPI_CLOCK_DIVISOR 16 // Use a 16 MHz system clock for SPI
#define SPI_WRITE 0x02 // Write opcode for SPI communication

void spi_init(void)
{
    // Initialize SPI control register
    uint8_t spcr = 0x00;
    spcr |= (1 << SPE); // Enable SPI
    spcr |= (1 << MSTR); // Set master mode
    spcr |= (1 << CPOL); // Clock polarity = 1
    spcr |= (1 << CPHA); // Clock phase = 1
    spcr |= (1 << DORD); // Data order = LSB first
    spcr |= (1 << SPR1); // Set SPI clock divisor to 16
    outp(spcr, SPCR);

    // Set SPI SS pin to high (inactive)
    outp(SPI_SS_PIN, PORTB);
}

void spi_send(uint8_t* data, size_t size)
{
    // Activate SPI SS pin
    outp(0x00, SPI_SS_PIN);

    // Send write opcode to ESP32 over SPI
    outp(SPI_WRITE, SPDR);
    while(!(inp(SPSR) & (1 << SPIF))); // Wait for SPI transfer to complete

    // Send command data to ESP32 over SPI
    for (size_t i = 0; i < size; i++) {
        outp(data[i], SPDR);
        while(!(inp(SPSR) & (1 << SPIF))); // Wait for SPI transfer to complete
    }

    // Deactivate SPI SS pin
    outp(SPI_SS_PIN, SPI_SS_PIN);
}

void send_vga_controller_command(void)
{
    uint8_t command[2] = {0x56, 0x00}; // the VGAController command
    spi_send(command, sizeof(command));
}

int main(void)
{
    spi_init();
    send_vga_controller_command();
    return 0;
}
