/*
 * Stepper.h
 * 
 * Stepper instrument class.
 * Supports 2-pin (step / direction) as well as 4-pin stepper output.
 */

#ifndef SRC_MOPPYINSTRUMENTS_STEPPER_H_
#define SRC_MOPPYINSTRUMENTS_STEPPER_H_

#include "../MoppyConfig.h"
#include "../MoppyNetworks/MoppyNetwork.h"
#include "MoppyInstrument.h"
#include "../MoppySystem/MoppyTimer.h"
#include <Arduino.h>
//#include <SPI.h>

namespace instruments
{
class Stepper : public MoppyInstrument
{
public:
	Stepper(uint8_t start_address, uint8_t end_address, uint16_t pos_max, uint8_t note_max, uint8_t step_type);
	void setup();
	void tick();
	uint8_t getBits();
	uint8_t * getOut();

protected:
	void sys_sequenceStop() override;
	void sys_reset() override;

	void dev_reset(uint8_t subAddress) override;
	void dev_noteOn(uint8_t subAddress, uint8_t payload[]) override;
	void dev_noteOff(uint8_t subAddress, uint8_t payload[]) override;
	void dev_bendPitch(uint8_t subAddress, uint8_t payload[]) override;
	void deviceMessage(uint8_t subAddress, uint8_t command, uint8_t payload[]);
	//void tick();

private:
	const uint8_t MAX_NOTE; // Maximum note number to attempt to play
	const uint8_t DRIVE_TYPE; // 2 or 4 output stepper
	const uint8_t MAX_POS; // Maximum position for floppy drives
	const uint8_t MAX_ADDRESS, MIN_ADDRESS;
	const uint8_t DRIVE_COUNT; // Number of drives used
	const uint8_t DRIVE_BYTES; // Number for bytes needed
	StepperInstrument *drives; // Drive struct array
	uint8_t *out;

	//void tick();
	void resetAll();
	void shiftBits();
	void haltAllDrives();
	void reset(byte driveNum);
	void startupSound(byte driveIndex);
	void setMovement(byte driveIndex, bool movementEnabled);
};
} // namespace instruments

#endif /* SRC_MOPPYINSTRUMENTS_STEPPER_H_ */