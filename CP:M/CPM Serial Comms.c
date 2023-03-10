#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#define DEVICE "/dev/ttyS1" // Serial port device name
#define BUFFER_SIZE 20      // Size of the receive buffer

int main(void)
{
    int fd, n;
    char buf[BUFFER_SIZE];
    struct termios tio;

    // Open serial port device
    fd = open(DEVICE, O_RDWR | O_NOCTTY);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }

    // Set serial port parameters
    tcgetattr(fd, &tio);
    tio.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    tio.c_iflag = 0;
    tio.c_oflag = 0;
    tio.c_lflag = 0;
    tcsetattr(fd, TCSANOW, &tio);

    // Send message to device
    n = write(fd, "Hello, device!", 14);
    if (n < 0)
    {
        perror("write");
        exit(1);
    }

    // Receive response from device
    n = read(fd, buf, BUFFER_SIZE-1);
    if (n < 0)
    {
        perror("read");
        exit(1);
    }
    buf[n] = '\0';

    // Print response on console
    printf("Response from device: %s\n", buf);

    // Close serial port device
    close(fd);

    return 0;
}
