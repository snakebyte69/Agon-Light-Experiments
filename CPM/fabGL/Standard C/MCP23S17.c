; Snake fabGPL Experiments 10 March 2023
; fabgl::MCP23S17, 16 bit SPI port expander

#include <stdio.h>
#include <stdint.h>
#include "driver/spi_master.h"

#define MCP23S17_CMD 0x20

spi_device_handle_t spi_dev;

void setup_spi() {
    esp_err_t ret;
    spi_bus_config_t buscfg = {
        .miso_io_num = -1,
        .mosi_io_num = 23,
        .sclk_io_num = 18,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 16
    };
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 10 * 1000 * 1000,
        .mode = 0,
        .spics_io_num = 14,
        .queue_size = 1
    };

    ret = spi_bus_initialize(HSPI_HOST, &buscfg, 1);
    ESP_ERROR_CHECK(ret);

    ret = spi_bus_add_device(HSPI_HOST, &devcfg, &spi_dev);
    ESP_ERROR_CHECK(ret);
}

void send_mcp23s17_cmd() {
    esp_err_t ret;
    spi_transaction_t t;
    uint8_t tx_data[] = {MCP23S17_CMD};

    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = tx_data;
    t.flags = SPI_TRANS_USE_TXDATA;

    ret = spi_device_transmit(spi_dev, &t);
    ESP_ERROR_CHECK(ret);
}

int main(void) {
    setup_spi();
    send_mcp23s17_cmd();

    return 0;
}
