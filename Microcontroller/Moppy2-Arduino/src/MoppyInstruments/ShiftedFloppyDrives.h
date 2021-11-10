/*
 * ShiftedFloppyDrives.h
 * Floppy drives connected to shift register(s)
 */

#ifndef SRC_MOPPYINSTRUMENTS_FLOPPYDRIVES_H_
#define SRC_MOPPYINSTRUMENTS_FLOPPYDRIVES_H_

#include "../MoppyConfig.h"
#include "../MoppyNetworks/MoppyNetwork.h"
#include "MoppyInstrument.h"
#include "MoppyTimer.h"
#include <Arduino.h>
#include <SPI.h>
namespace instruments {
class ShiftedFloppyDrives : public MoppyInstrument {
public:
    void setup();
    static const int LATCH_PIN = D1; //RCLK

protected:
    void sys_sequenceStop() override;
    void sys_reset() override;

    void dev_reset(uint8_t subAddress) override;
    void dev_noteOn(uint8_t subAddress, uint8_t payload[]) override;
    void dev_noteOff(uint8_t subAddress, uint8_t payload[]) override;
    void dev_bendPitch(uint8_t subAddress, uint8_t payload[]) override;
    void deviceMessage(uint8_t subAddress, uint8_t command, uint8_t payload[]);

private:
    // Maximum note number to attempt to play on floppy drives.  It's possible higher notes may work,
    // but they may also cause instability.
    static const uint8_t MAX_FLOPPY_NOTE = 71;

    static const uint8_t MAX_POS = 158; // Maximum position for floppy drives
    static const uint8_t MAX_POS_NOMOVEMENT = 81;
    static const uint8_t MIN_POS_NOMOVEMENT = 79;
    static const uint8_t DRIVE_COUNT = MAX_SUB_ADDRESS - MIN_SUB_ADDRESS + 1; // Number of drives used
    static const uint8_t DRIVE_BYTES = DRIVE_COUNT / 4 + 1; // Number for bytes needed
    static FloppyDrive drives[DRIVE_COUNT]; // Drive struct array
    //static uint64_t tick_count;

    static void tick();
    static void resetAll();
    static void togglePin(byte driveIndex);
    static void shiftBits();
    static void haltAllDrives();
    static void reset(byte driveNum);
    static void blinkLED();
    static void startupSound(byte driveIndex);
    static void setMovement(byte driveIndex, bool movementEnabled);
};
} // namespace instruments

#endif /* SRC_MOPPYINSTRUMENTS_FLOPPYDRIVES_H_ */