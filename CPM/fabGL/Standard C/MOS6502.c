; Snake fabGPL Experiments 10 March 2023
; fabgl::MOS6502, MOS 6502 CPU emulator

#include <fabgl.h>
#include <SPI.h>
#include <MOS6502.h>

// Set up the SPI connection between the eZ80 and ESP32
SPIClass spi;
spi.begin();

// Create an instance of the MOS6502 class
MOS6502 mos6502;

// Load the MOS 6502 binary code into the emulator
unsigned char code[] = {0xA9, 0x01, 0x8D, 0x02, 0x60}; // Example code that sets accumulator to 1 and jumps to address 0x6002
mos6502.load(code, sizeof(code));

// Begin the emulation process
mos6502.run();
