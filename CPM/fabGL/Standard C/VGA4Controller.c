; Snake fabGPL Experiments 
; fabgl::VGA4Controller, device driver for VGA 4 colors bitmapped output (low RAM requirements, CPU intensive)

#include <ez80.h>
#include <spi.h>

#define ESP32_CS_PORT PORTB
#define ESP32_CS_PIN  0x08

int main(void) {
    // Configure SPI
    spiInit(0, SPI_CLK_DIV_16, SPI_MODE_MASTER | SPI_MODE_CPOL0_CPHA0);

    // Set CS pin as output and high
    OUT(ESP32_CS_PORT) &= ~ESP32_CS_PIN;
    DDR(ESP32_CS_PORT) |= ESP32_CS_PIN;
    OUT(ESP32_CS_PORT) |= ESP32_CS_PIN;

    // Send "VGA4Controller" command
    char command[16] = "VGA4Controller";
    spiTransfer(0, (uint8_t*)command, NULL, 15, 1);

    // Deselect CS
    OUT(ESP32_CS_PORT) |= ESP32_CS_PIN;

    return 0;
}
