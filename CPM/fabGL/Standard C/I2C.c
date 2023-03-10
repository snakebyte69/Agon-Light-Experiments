; Snake fabGPL Experiments 10 March 2023
; fabgl::I2C, thread safe I2C (Wire) class

#include <fabgl.h>

// Define the SPI pins to be used
#define SPI_SCK_PIN 5
#define SPI_MOSI_PIN 18
#define SPI_MISO_PIN 19
#define SPI_CS_PIN 21

// Define the I2C pins to be used
#define I2C_SDA_PIN 22
#define I2C_SCL_PIN 23

int main() {
    // Initialize the SPI communication
    FabGL_SPI spi(SPI_SCK_PIN, SPI_MOSI_PIN, SPI_MISO_PIN, SPI_CS_PIN);

    // Initialize the I2C communication on the specified pins
    FabGL_I2C i2c(I2C_SDA_PIN, I2C_SCL_PIN);

    // Example code to write to an I2C device
    uint8_t i2cAddr = 0x68; // Address of the device
    uint8_t data[] = {0x00, 0x01, 0x02}; // Data to be sent
    i2c.write(i2cAddr, data, sizeof(data));

    // Example code to read from an I2C device
    uint8_t readData[4];
    i2c.read(i2cAddr, readData, sizeof(readData));

    // Main program loop
    while (true) {
        // Do something here
    }

    return 0;
}
