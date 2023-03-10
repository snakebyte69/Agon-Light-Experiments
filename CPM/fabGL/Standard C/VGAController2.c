// Snake fabGPL Experiments
// fabgl::VGAController, device driver for VGA bitmapped output

#include <stdio.h>
#include <stdlib.h>
#include "ez80.h"
#include "spi.h"
#include "fabgl.h"

// Define the SPI settings
#define SPI_CLOCK_DIVIDER 2
#define SPI_MODE 0
#define SPI_MSB_FIRST 1

int main()
{
    // Initialize the SPI interface
    spi_init(SPI_CLOCK_DIVIDER, SPI_MODE, SPI_MSB_FIRST);

    // Initialize the fabGL VGAController
    fabgl::VGAController vgaController;

    // Send the VGAController command to the ESP32 via SPI
    spi_transfer(0x01);
    spi_transfer(0x00);
    spi_transfer(0x00);
    spi_transfer(0x00);

    // Wait for the transfer to complete
    while (!spi_is_tx_complete());

    // Print a message indicating the VGAController command was sent
    printf("Sent VGAController command to ESP32 via SPI\n");

    return 0;
}
