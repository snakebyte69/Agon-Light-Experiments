; Snake fabGPL Experiments 10 March 2023
; fabgl::Mouse, that controls a PS2 mouse

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "spi.h"
#include "fabgl.h"

int main(void)
{
    // Initialize SPI interface
    spi_init();

    // Initialize fabgl library
    fabgl_init();

    // Create a new Mouse object
    Mouse* mouse = new Mouse();

    // Move the cursor to position (100, 100)
    mouse->setPosition(100, 100);

    // Delete the Mouse object
    delete mouse;

    return 0;
}
