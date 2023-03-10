#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/spi/spidev.h>

#define SPI_DEVICE "/dev/spidev0.0"  // SPI device node
#define SPI_MODE SPI_MODE_0          // SPI mode
#define SPI_BITS_PER_WORD 8          // Number of bits per word
#define SPI_SPEED_HZ 1000000         // SPI clock speed in Hz

int main() {
    int spi_fd;
    uint8_t tx_data[3] = {0x12, 0x34, 0x56};  // Data to send
    uint8_t rx_data[3];                       // Data to receive

    // Open the SPI device
    spi_fd = open(SPI_DEVICE, O_RDWR);
    if (spi_fd < 0) {
        perror("Error opening SPI device");
        exit(1);
    }

    // Set SPI mode
    if (ioctl(spi_fd, SPI_IOC_WR_MODE, &SPI_MODE) < 0) {
        perror("Error setting SPI mode");
        exit(1);
    }

    // Set number of bits per word
    if (ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &SPI_BITS_PER_WORD) < 0) {
        perror("Error setting bits per word");
        exit(1);
    }

    // Set SPI clock speed
    if (ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &SPI_SPEED_HZ) < 0) {
        perror("Error setting SPI clock speed");
        exit(1);
    }

    // Send data over SPI
    struct spi_ioc_transfer transfer = {
        .tx_buf = (unsigned long)tx_data,
        .rx_buf = (unsigned long)rx_data,
        .len = sizeof(tx_data),
        .speed_hz = SPI_SPEED_HZ,
        .bits_per_word = SPI_BITS_PER_WORD
    };
    if (ioctl(spi_fd, SPI_IOC_MESSAGE(1), &transfer) < 0) {
        perror("Error sending SPI message");
        exit(1);
    }

    // Print received data
    printf("Received: 0x%02X 0x%02X 0x%02X\n", rx_data[0], rx_data[1], rx_data[2]);

    // Close the SPI device
    close(spi_fd);

    return 0;
}
