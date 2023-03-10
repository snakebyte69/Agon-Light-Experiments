; Snake fabGPL Experiments 10 March 2023
; fabgl::DS3231, Real Time Clock driver which uses the thread safe fabgl::I2C library

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ez8.h"
#include "spi.h"
#include "fabgl.h"

#define DS3231_I2C_ADDR 0x68

void setup_spi()
{
    spi_initialize(1, SPI_MODE_0, 1000000);  // Initialize SPI with frequency of 1 MHz
}

void setup_i2c()
{
    fabgl::I2C i2c;
    i2c.begin();
}

void get_time()
{
    fabgl::I2C i2c;
    i2c.begin();

    uint8_t seconds, minutes, hours, day, date, month, year;

    // Read time from DS3231 RTC
    i2c.read(DS3231_I2C_ADDR, 0x00, &seconds, 1);
    i2c.read(DS3231_I2C_ADDR, 0x01, &minutes, 1);
    i2c.read(DS3231_I2C_ADDR, 0x02, &hours, 1);
    i2c.read(DS3231_I2C_ADDR, 0x03, &day, 1);
    i2c.read(DS3231_I2C_ADDR, 0x04, &date, 1);
    i2c.read(DS3231_I2C_ADDR, 0x05, &month, 1);
    i2c.read(DS3231_I2C_ADDR, 0x06, &year, 1);

    // Print time
    printf("Current time: %02x:%02x:%02x %02x/%02x/20%02x\n",
           hours, minutes, seconds, date, month, year);
}

int main()
{
    setup_spi();
    setup_i2c();

    // Send "DS3231" command to ESP32 chip
    spi_select(1);
    spi_send_byte('D');
    spi_send_byte('S');
    spi_send_byte('3');
    spi_send_byte('2');
    spi_send_byte('3');
    spi_send_byte('1');
    spi_unselect(1);

    // Wait for response from ESP32 chip
    sleep(1);

    // Read time from DS3231 RTC and print it
    get_time();

    return 0;
}
