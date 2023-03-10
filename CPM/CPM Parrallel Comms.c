#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/devio.h>

#define DEVICE "/dev/lpt0"  // Parallel port device name
#define BUFFER_SIZE 20      // Size of the receive buffer

int main(void)
{
    int fd, n;
    char buf[BUFFER_SIZE];
    struct devget dg;
    struct devparam dp;

    // Open parallel port device
    fd = open(DEVICE, O_RDWR);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }

    // Get parallel port parameters
    ioctl(fd, DIOCGGET, &dg);
    dp = dg.dp;

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

    // Close parallel port device
    close(fd);

    return 0;
}
