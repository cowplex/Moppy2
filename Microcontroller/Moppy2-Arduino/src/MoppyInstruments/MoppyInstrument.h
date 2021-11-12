/*
 * MoppyInstrument.h
 * Stores useful constants for MoppyInstrument implementations
 */

#ifndef MOPPY_SRC_MOPPYINSTRUMENTS_MOPPYINSTRUMENT_H_
#define MOPPY_SRC_MOPPYINSTRUMENTS_MOPPYINSTRUMENT_H_

#include "../MoppyMessageConsumer.h"
#include "../MoppyConfig.h"
#include <Arduino.h>

#define STEPPER_STEPDIR 0
#define STEPPER_QUAD 1

// Number of octaves to bend notes by at full-deflection (MIDI pitch bending is weird).
// Described as cents/cents-in-an-octave
#define BEND_OCTAVES 200/(float)1200

/*
 * Number of microseconds in a timer-tick for setting timer resolution
 * and calculating noteTicks.  Smaller values here will trigger interrupts more often,
 * which might interfere with other processes but will result in more accurate frequency
 * reproduction.
 */
//#ifdef ARDUINO_ARCH_AVR
//#define TIMER_RESOLUTION 40
//#elif ARDUINO_ARCH_ESP8266 || ARDUINO_ARCH_ESP32
//#define TIMER_RESOLUTION 20 // 50 kHz - Higher resolution for the faster processor
//#endif

// In some cases a pulse will only happen every-other tick (e.g. if the tick is
// toggling a pin on and off and pulses happen on rising signal) so to simplify
// the already ugly arrays below, multiply the RESOLUTION by 2 here.
#define DOUBLE_T_RESOLUTION (TIMER_RESOLUTION*2)

// Frequency at which a drive resets itself
const unsigned int resetPeriod = 10000; // 100 hz, or G2 + 35 cents

// The period of notes in microseconds
const unsigned int notePeriods[128] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  61162, 57737, 54496, 51414, 48544, 45809, 43253, 40816, 38521, 36364, 34317, 32394, //C0 - B0
  30581, 28860, 27241, 25714, 24272, 22910, 21622, 20408, 19264, 18182, 17161, 16197, //C1 - B1
  15288, 14430, 13620, 12857, 12134, 11453, 10811, 10204, 9631, 9091, 8581, 8099, //C2 - B2
  7645, 7216, 6811, 6428, 6068, 5727, 5405, 5102, 4816, 4545, 4290, 4050, //C3 - B3
  3822, 3608, 3405, 3214, 3034, 2863, 2703, 2551, 2408, 2273, 2145, 2025, //C4 - B4
  1911, 1804, 1703, 1607, 1517, 1432, 1351, 1276, 1204, 1136, 1073, 1012, //C5 - B5
  956, 902, 851, 804, 758, 716, 676, 638, 602, 568, 536, 506, //C6 - B6
  478, 451, 426, 402, 379, 358, 338, 319, 301, 284, 268, 253, //C7 - B7
  239, 225, 213, 201, 190, 179, 169, 159, 150, 142, 134, 127,//C8 - B8
  0, 0, 0, 0, 0, 0, 0, 0
};

class MoppyInstrument : public MoppyMessageConsumer {
public:
    virtual void setup() = 0;
    virtual void tick() = 0;
};

struct StepperInstrument // 8 bytes (?)
{
    unsigned int position : 16; // Max steps 4096.
    unsigned int max_position : 16;
    unsigned int direction : 1;
    unsigned int note : 7;
    unsigned int period : 16;
    unsigned int ticks : 16;
    unsigned int nomovement : 1;
};

#endif /* MOPPY_SRC_MOPPYINSTRUMENTS_MOPPYINSTRUMENT_H_ */
