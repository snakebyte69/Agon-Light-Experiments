; Snake fabGPL Experiments 10 March 2023
; fabgl::VIA6522, VIA 6522 emulator

#include <ez80.h>
#include <stdio.h>
#include <string.h>
#include "fabgl.h"

// SPI configuration
#define SPI_CS 1 // chip select line
#define SPI_CLOCK_DIV 4 // clock divider (8 MHz / 4 = 2 MHz)

// VIA configuration
#define VIA_ADDRESS 0x6000 // base address of the VIA
#define VIA_IRQ_LINE 1 // IRQ line to use

// Define a buffer to hold the received data
#define BUFFER_SIZE 1024
static uint8_t buffer[BUFFER_SIZE];

int main()
{
    // Initialize the SPI interface
    spi_init(SPI_CLOCK_DIV, SPI_MODE_0, SPI_CS);
    
    // Initialize the VIA6522
    fabgl::VIA6522 via(VIA_ADDRESS);
    via.initialize();
    via.setIRQLine(VIA_IRQ_LINE);

    // Enable interrupts
    __asm__("ei");

    while (1)
    {
        // Wait for an interrupt
        __asm__("halt");

        // Check which interrupt line caused the interrupt
        uint8_t interruptLine = via.getInterruptLine();

        // Handle the interrupt
        if (interruptLine == VIA_IRQ_LINE)
        {
            // Handle VIA6522 interrupt
            // ...
        }
    }

    return 0;
}
