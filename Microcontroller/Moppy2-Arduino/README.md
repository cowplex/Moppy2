# Moppy2-Arduino
Device implementation for Moppy2 for microcontrollers that support the Arduino **framework**.  Currently, the following boards are officially supported:
- **Arduino [Uno\*]** (via the Arduino IDE or PlatformIO)
- **ESP8266** (via PlatformIO)
- **ESP32** (via PlatformIO)

\* Most "Arduino" boards are extremely similar and should work fine, though if you're using PlatformIO you may need to modify `platformio.ini` to match your board-type.

# Shifted Floppies Rewrite
This fork contains a fairly comprehensive rewrite of the Shifted Floppy class, with an eye toward using Moppy with ESP microcontrollers. The previous implementation was capable of driving 8 drives using two shift registers - the step bits were output to one register and the direction bits to a second. Both were implemented in code using two 8-bit variables.

This implementation is currently capable of driving up to 256 drives at once. The outputs from the shift registers have been rearranged so that the step and direction bits for a particular floppy are adjacent. In addition, minor changes have been made with the goal of making the drive bank more easily playable live with a MIDI keyboard. The handling of note off events has been tweaked to only respond if that drive is currently playing that note, which allows slurring of notes without the previous key release stopping the drive. Also inplemented is a "0-channel" where note-on signals will be distributed to any drive not playing a note, thereby enabling simultaneous notes while playing live up to the number of drives in the array.