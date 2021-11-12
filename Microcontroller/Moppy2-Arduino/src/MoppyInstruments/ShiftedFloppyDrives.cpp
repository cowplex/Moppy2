/*
 * ShiftedFloppyDrives.cpp
 *
 * Output for controlling floppy drives via shifter(s).
 */
#include "ShiftedFloppyDrives.h"
#include "MoppyInstrument.h"
namespace instruments 
{

// Required for the icache loops
//uint64_t ShiftedFloppyDrives::tick_count = 0;
FloppyDrive ShiftedFloppyDrives::drives[DRIVE_COUNT];

void ShiftedFloppyDrives::setup()
{
    // Zero-initialize floppy array
    memset(drives, 0, DRIVE_COUNT * sizeof(FloppyDrive));

    // Initialize shift register outputs
    pinMode(LATCH_PIN, OUTPUT);
    SPI.begin();
    SPI.beginTransaction(SPISettings(16000000, LSBFIRST, SPI_MODE0)); // We're never ending this, hopefully that's okay...

    // Setup timer to handle interrupts for floppy driving. Resolution in microseconds.
    MoppyTimer::initialize(TIMER_RESOLUTION, tick);

    // With all pins setup, let's do a first run reset
    delay(50); // Wait a bit for safety
    resetAll();
    delay(500); // Wait a half second for safety

    // If MoppyConfig wants a startup sound, play the startupSound on the
    // first drive.
    if (PLAY_STARTUP_SOUND)
    {
        startupSound(0);
        delay(500);
        resetAll();
    }
}

// Play startup sound to confirm drive functionality
void ShiftedFloppyDrives::startupSound(byte driveIndex)
{
    unsigned int chargeNotes[] = { 31, 36, 38, 43, 0 };

    byte i = 0;
    unsigned long lastRun = 0;
    while (i < 5)
    {
        if (millis() - 200 > lastRun)
        {
            lastRun = millis();
            drives[driveIndex].note = chargeNotes[i++];
            drives[driveIndex].period = notePeriods[drives[driveIndex].note];
        }
    }
}

//
//// Message Handlers
//

void ShiftedFloppyDrives::sys_reset()
{
    resetAll();
}

void ShiftedFloppyDrives::sys_sequenceStop()
{
    haltAllDrives();
}

void ShiftedFloppyDrives::dev_reset(uint8_t subAddress)
{
    if (subAddress == 0x00)
        resetAll();
    else
        reset(subAddress);
}

void ShiftedFloppyDrives::dev_noteOn(uint8_t subAddress, uint8_t payload[]) 
{
    if (payload[0] <= MAX_FLOPPY_NOTE)
    {
        if(!subAddress) // 0 subaddress turns on any free drive. Fail if no drives free.
        { 
            for(subAddress = MIN_SUB_ADDRESS; drives[subAddress- MIN_SUB_ADDRESS].period && subAddress <= MAX_SUB_ADDRESS; ++subAddress) { }
            if(subAddress > MAX_SUB_ADDRESS)
                return;
        }
        subAddress -= MIN_SUB_ADDRESS;
        drives[subAddress].note = payload[0];
        drives[subAddress].period = notePeriods[drives[subAddress].note];
    }
};
void ShiftedFloppyDrives::dev_noteOff(uint8_t subAddress, uint8_t payload[])
{
    if(subAddress)
    {
        subAddress -= MIN_SUB_ADDRESS;
        if(payload[0] == drives[subAddress].note)
        {
            drives[subAddress].note = drives[subAddress].period = 0;
        }
    }
    else // 0 subaddress turns off any drive playing that note
    { 
        for(uint8_t i = MIN_SUB_ADDRESS; i <= MAX_SUB_ADDRESS; ++i)
        {
            dev_noteOff(i, payload);
        }
    }
};
void ShiftedFloppyDrives::dev_bendPitch(uint8_t subAddress, uint8_t payload[])
{
    // A value from -8192 to 8191 representing the pitch deflection
    int16_t bendDeflection = payload[0] << 8 | payload[1];

    subAddress -= MIN_SUB_ADDRESS;

    // A whole octave of bend would double the frequency (halve the the period) of notes
    // Calculate bend based on BEND_OCTAVES from MoppyInstrument.h and percentage of deflection
    drives[subAddress].period = notePeriods[drives[subAddress].note] / pow(2.0, BEND_OCTAVES * (bendDeflection / (float)8192));
};

void ShiftedFloppyDrives::deviceMessage(uint8_t subAddress, uint8_t command, uint8_t payload[])
{
    switch (command)
    {
    case NETBYTE_DEV_SETMOVEMENT:
        setMovement(subAddress - MIN_SUB_ADDRESS, payload[0] == 0); // MIDI bytes only go to 127, so * 2
        break;
    }
}

void ShiftedFloppyDrives::setMovement(byte driveIndex, bool movementEnabled)
{
    drives[driveIndex].nomovement = movementEnabled;
}

//
//// Floppy driving functions
//

/*
Called by the timer interrupt at the specified resolution.  Because this is called extremely often,
it's crucial that any computations here be kept to a minimum!

Additionally, the ICACHE_RAM_ATTR helps avoid crashes with WiFi libraries, but may increase speed generally anyway
 */
#pragma GCC push_options
#pragma GCC optimize("Ofast") // Required to unroll this loop, but useful to try to keep this speedy
#ifdef ARDUINO_ARCH_ESP8266
void ICACHE_RAM_ATTR ShiftedFloppyDrives::tick()
#elif ARDUINO_ARCH_ESP32
void IRAM_ATTR ShiftedFloppyDrives::tick()
#else
void ShiftedFloppyDrives::tick()
#endif
{
    static uint8_t last_out[DRIVE_BYTES];
    uint8_t out[DRIVE_BYTES];
    memset(out, 0, DRIVE_BYTES);

    /*
    For each drive, count the number of
    ticks that pass, and toggle the pin if the current period is reached.
    */

    // Global tick counter for number of microseconds elapsed.
    //tick_count += TIMER_RESOLUTION;

    for (int d = 0; d < DRIVE_COUNT; d++)
    {
        // Check if note is playing, check if a direction change is needed, and update position
        if(drives[d].period)// && tick_count % drives[d].period <= (TIMER_RESOLUTION * 2))
        {
            drives[d].ticks += 2 * TIMER_RESOLUTION;

            if(drives[d].ticks > drives[d].period)
            {
                drives[d].ticks -= drives[d].period;
                if(drives[d].position >= (drives[d].nomovement ? MAX_POS_NOMOVEMENT : MAX_POS))
                    drives[d].direction = 1;
                else if(drives[d].position <= (drives[d].nomovement ? MIN_POS_NOMOVEMENT : 0))
                    drives[d].direction = 0;
                drives[d].position += drives[d].direction == 0 ? 1 : -1;
            }

            if(drives[d].note == 0 && drives[d].period && drives[d].position == 0) // Drive done resetting
                drives[d].period = 0;
        }
        else if(drives[d].ticks)
        {
            drives[d].ticks = 0;
        }

        // Build output array. Step and position are adjacent pairs of bits
        // Bit 0: Drive 0 step; Bit 1: Drive 0 direction; Bit 2: Drive 1 step; etc.
        // Each byte holds up to 4 drives worth of direction/step pairs.
        out[d/4] += ((drives[d].position & 1) + (drives[d].direction << 1)) << (d * 2);
    }

    if(memcmp(last_out, out, DRIVE_BYTES)) // If we have new data
    {
        memcpy(&last_out, &out, DRIVE_BYTES); // update tracking
    
        // Latch low
        #ifdef ARDUINO_AVR_UNO
        PORTD &= B11101111;
        #else
        digitalWrite(LATCH_PIN, LOW);
        #endif

        // Shift bit array out
        SPI.transfer(out, DRIVE_BYTES);

        // Latch high - will update shift register output to data just latched in
        #ifdef ARDUINO_AVR_UNO
        PORTD |= B00010000;
        #else
        digitalWrite(LATCH_PIN, HIGH);
        #endif
    }
}
#pragma GCC pop_options

//
//// UTILITY FUNCTIONS
//

// Immediately stops all drives
void ShiftedFloppyDrives::haltAllDrives()
{
    for (uint8_t d = 0; d < DRIVE_COUNT; d++)
    {
        drives[d].period  = drives[d].note = 0;
    }
}

// For a given floppy number, runs the read-head all the way back to 0.
// Does not block
void ShiftedFloppyDrives::reset(uint8_t d)
{
    d -= MIN_SUB_ADDRESS;
    //drives[d].direction = 1;
    drives[d].nomovement = 0; // Turn movement on
    drives[d].note = 0; // No note
    drives[d].position = MAX_POS; // Set position to MAX
    drives[d].period = resetPeriod; // Period ON with no note will reset drive
}

// Resets all the drives simultaneously. Blocks until done.
void ShiftedFloppyDrives::resetAll()
{
    uint8_t d;

    // Stop all drives and put into reset mode
    haltAllDrives();
    for (d = MIN_SUB_ADDRESS; d <= MAX_SUB_ADDRESS; d++)
    {
        reset(d);
    }

    // Wait until all drives are reset
    d = 0;
    while(d < DRIVE_COUNT)
    {
        if(drives[d].position)
            d = 0;
        else    
            ++d;
        delay(5);
    }
}
} // namespace instruments