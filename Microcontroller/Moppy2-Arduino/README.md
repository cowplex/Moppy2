# Flexible Rewrite - Work in preogress - Not yet functional
This branch contains a nearly complete refactor of Moppy. The goal here is to be able to use any combination and number of instruments with any combination and number of output methods. That is, it should be possible to have one microcontroller controlling, (for example) a bank of 12 3.5" floppies, four NEMA stepper motors, two hard drives, and a bank of precussion solenoids and it should be able to split those instruments across microcontroller output pins and shift registers.

This is currently a work in progress, and the code WILL NOT WORK.

# Moppy2-Arduino
Device implementation for Moppy2 for microcontrollers that support the Arduino **framework**.  Currently, the following boards are officially supported:
- **Arduino [Uno\*]** (via the Arduino IDE or PlatformIO)
- **ESP8266** (via PlatformIO)
- **ESP32** (via PlatformIO)

\* Most "Arduino" boards are extremely similar and should work fine, though if you're using PlatformIO you may need to modify `platformio.ini` to match your board-type.