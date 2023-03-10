; Snake fabGPL Experiments 10 March 2023
; fabgl::SoundGenerator to generate sound and music

#include <ez80.h>

#define SPI_CS_PIN 0 // Replace with actual CS pin connected to ESP32
#define SPI_CLOCK_FREQ 1000000 // Replace with actual SPI clock frequency

void spi_init() {
    SPCR = 0x53; // Enable SPI as Master, set clock phase/polarity, set MSB first
    SPSR = 0x00; // Disable SPI 2x speed
    SPBRG = (F_CPU / (2 * SPI_CLOCK_FREQ)) - 1; // Set SPI clock frequency
}

void spi_write(uint8_t data) {
    while ((SPSR & (1 << SPIF)) == 0); // Wait until previous transfer is complete
    SPDR = data; // Write data to SPI buffer
}

void fabgl_sound_generator() {
    spi_init();
    // Send command to ESP32 to initialize SoundGenerator
    spi_write(0xFF); // Start of Command
    spi_write(0x0F); // Command ID for SoundGenerator
    spi_write(0x01); // SoundGenerator enable
    spi_write(0x00); // Placeholder for future use
    spi_write(0x00); // Placeholder for future use
    spi_write(0xFF); // End of Command
}

int main() {
    fabgl_sound_generator();
    return 0;
}
