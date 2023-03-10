; Snake fabGPL Experiments 10 March 2023
; fabgl::Scene abstract class that handles sprites, timings and collision detection

#include <ez80.h>

// Define SPI pins
#define SPI_CS_PIN   2    // CS pin
#define SPI_SCK_PIN  3    // SCK pin
#define SPI_MOSI_PIN 4    // MOSI pin
#define SPI_MISO_PIN 5    // MISO pin

// Define fabGL command bytes
#define SCENE_CMD 0x50

void spi_init()
{
    // Set up SPI pins
    PD_DDR = _BV(SPI_CS_PIN) | _BV(SPI_SCK_PIN) | _BV(SPI_MOSI_PIN);
    PD_CR1 = _BV(SPI_CS_PIN) | _BV(SPI_SCK_PIN) | _BV(SPI_MOSI_PIN) | _BV(SPI_MISO_PIN);
    PD_ODR = _BV(SPI_CS_PIN) | _BV(SPI_SCK_PIN) | _BV(SPI_MOSI_PIN);

    // Enable SPI and set clock rate
    SPI_CR1 = _BV(SPI_MSTR) | _BV(SPI_SPE) | _BV(SPI_BR1) | _BV(SPI_BR0);
}

void spi_send(uint8_t byte)
{
    // Select CS
    PD_ODR &= ~_BV(SPI_CS_PIN);

    // Send byte
    SPI_DR = byte;

    // Wait for transmission to complete
    while (!(SPI_SR & _BV(SPI_TXE)));

    // Deselect CS
    PD_ODR |= _BV(SPI_CS_PIN);
}

int main()
{
    spi_init();
    spi_send(SCENE_CMD);

    return 0;
}
