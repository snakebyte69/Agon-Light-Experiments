; Snake fabGPL Experiments 10 March 2023
; fabgl::i8080, Intel 8080 CPU emulator

#include <stdio.h>
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/spi_master.h"

#define PIN_NUM_MISO 25
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  19
#define PIN_NUM_CS   22

void app_main(void)
{
    esp_err_t ret;
    spi_device_handle_t spi;
    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0,
    };
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 1000000,
        .mode = 0,
        .spics_io_num = PIN_NUM_CS,
        .queue_size = 1,
    };

    ret = spi_bus_initialize(1, &buscfg, 1);
    assert(ret == ESP_OK);

    ret = spi_bus_add_device(1, &devcfg, &spi);
    assert(ret == ESP_OK);

    // Send "i8080" command to eZ80 chip via SPI
    uint8_t tx_data[5] = {0x69, 0x38, 0x30, 0x38, 0x30};
    spi_transaction_t trans = {
        .length = 40,
        .tx_buffer = tx_data,
    };
    ret = spi_device_transmit(spi, &trans);
    assert(ret == ESP_OK);

    // Clean up SPI bus
    spi_bus_remove_device(spi);
    spi_bus_free(1);
}
