; Snake fabGPL Experiments 10 March 2023
; fabgl::InputBox to generate simple UI wizards

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "spi.h" // assume this is a header file that provides SPI functions for CP/M
#include "fabgl.h" // assume this is the header file that provides fabGL commands

int main() {
    // initialize SPI
    spi_init();

    // create an InputBox object
    fabgl::InputBox inputBox;

    // set the properties of the InputBox
    inputBox.setMessage("Enter your name:");
    inputBox.setMaxLength(20);
    inputBox.setDefaultText("John Doe");

    // send the InputBox command over SPI to the ESP32 chip
    uint8_t buffer[32]; // assume a buffer of 32 bytes is enough for the command
    uint8_t *ptr = buffer;

    // serialize the command object into a buffer
    ptr = fabgl::serializeCommand(ptr, &inputBox);

    // send the buffer over SPI
    spi_write(buffer, ptr - buffer);

    // receive the response from the ESP32 chip over SPI
    spi_read(buffer, 32); // assume a response of maximum 32 bytes

    // deserialize the response into a command object
    fabgl::Command *command = fabgl::deserializeCommand(buffer);

    // check if the response is an InputBoxResult
    if (command->type == fabgl::CommandType::InputBoxResult) {
        // cast the response to InputBoxResult
        fabgl::InputBoxResult *result = (fabgl::InputBoxResult*) command;

        // print the result
        printf("User entered: %s\n", result->getText());
    } else {
        printf("Error: received unexpected command type\n");
    }

    // free the command object
    delete command;

    return 0;
}
