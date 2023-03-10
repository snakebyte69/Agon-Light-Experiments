; Snake fabGPL Experiments 10 March 2023
; fabgl::ILI9341Controller, device driver for ILI9341 based TFT displays

#include <stdio.h>
#include <stdlib.h>
#include "ez80.h"
#include "spi.h"
#include "fabgl.h"

#define ILI9341_CONTROLLER 0x10

int main() {
    // Initialize the SPI interface
    spi_begin();
    spi_set_speed_hz(10000000);
    spi_set_mode(SPI_MODE_0);

    // Send the "ILI9341Controller" command to the ESP32 chip
    uint8_t command = ILI9341_CONTROLLER;
    spi_write(&command, 1);

    // Wait for the response from the ESP32 chip
    while(!spi_is_rx_ready());

    // Read the response from the ESP32 chip
    uint8_t response = spi_read();

    // Print the response to the console
    printf("Received response: 0x%x\n", response);

    // End the SPI interface
    spi_end();

    return 0;
}
