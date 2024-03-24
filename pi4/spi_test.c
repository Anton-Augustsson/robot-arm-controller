#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define SPI_DEVICE "/dev/spidev0.0"
#define BUF_LEN 32

int main() {
    int fd;
    uint8_t out_buf[BUF_LEN] = {1}; // Initialize output buffer with zeros
    uint8_t in_buf[BUF_LEN] = {0};  // Initialize input buffer with zeros
    struct spi_ioc_transfer trx = {
        .tx_buf = (unsigned long)out_buf,
        .rx_buf = (unsigned long)in_buf,
        .len = BUF_LEN,
        .delay_usecs = 0,
        .speed_hz = 1000000,
        .bits_per_word = 8,
    };

    // Open SPI device
    fd = open(SPI_DEVICE, O_RDWR);
    if (fd < 0) {
        perror("Error opening SPI device");
        return 1;
    }

    // Perform SPI transfer
    if (ioctl(fd, SPI_IOC_MESSAGE(1), &trx) < 0) {
        perror("Error performing SPI transfer");
        close(fd);
        return 1;
    }

    // Print received data
    printf("Received data from SPI:\n");
    for (int i = 0; i < BUF_LEN; ++i) {
        printf("%02x ", in_buf[i]);
    }
    printf("\n");

    // Close SPI device
    close(fd);

    return 0;
}

