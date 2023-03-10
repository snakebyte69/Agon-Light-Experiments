; Snake fabGPL Experiments 10 March 2023
; fabgl::SSD1306Controller, device driver for SSD1306 based OLED displays

#include <stdio.h>
#include <stdlib.h>
#include <cpm.h>
#include <ez80.h>

// Define SPI pins
#define SPI_SS_PIN  PPI_CTRL_PORTB0
#define SPI_SCK_PIN PPI_CTRL_PORTB1
#define SPI_MOSI_PIN PPI_CTRL_PORTB2
#define SPI_MISO_PIN PPI_CTRL_PORTB3

// Define fabGL command codes
#define FABGL_CMD_SSD1306_CONTROLLER 0x00

int main()
{
    // Initialize SPI pins
    outp(0x00, SPI_SS_PIN);
    outp(0x02, SPI_SCK_PIN);
    outp(0x02, SPI_MOSI_PIN);
    outp(0x00, SPI_MISO_PIN);

    // Initialize SPI control register
    outp(0x40, PPI_CTRL_PORTC);

    // Send fabGL command to ESP32 via SPI
    unsigned char command = FABGL_CMD_SSD1306_CONTROLLER;
    outp(command, SPI_MOSI_PIN);
    while ((inp(PPI_STATUS) & 0x04) == 0x00);

    return 0;
}
