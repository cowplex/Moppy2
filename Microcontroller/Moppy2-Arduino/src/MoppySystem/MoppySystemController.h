/*
 * 
 */

#ifndef MOPPY_SRC_MOPPYSYSTEMCONTROLLER_H_
#define MOPPY_SRC_MOPPYSYSTEMCONTROLLER_H_

#include <Arduino.h>
#include <vector>
#include "../MoppyMessageConsumer.h"
#include "../MoppyConfig.h"
#include "../MoppyInstruments/MoppyInstrument.h"
#include "MoppyTimer.h"
#include "MoppyOutput.h"

class MoppySystemController : public MoppyMessageConsumer 
{
public:
	MoppySystemController();
	void addDevice(MoppyInstrument *instrument);
	void addOutput(MoppyOutput *output);
	void begin();
	void handleSystemMessage(uint8_t command, uint8_t payload[]);
	void handleDeviceMessage(uint8_t subAddress, uint8_t command, uint8_t payload[]);
protected:

private:
	//MoppyMessageConsumer *devices;
	static std::vector<MoppyInstrument *> devices; // List of instruments
	static std::vector<MoppyOutput *> outputs; // List of outputs
	static std::vector<uint8_t> device_bits; // Tracking variable for bits in each instrument
	static std::vector<uint8_t> output_bits; // Tracking variable for bits in each output
	static std::vector<uint8_t *> device_bytes; // pointer variable for each instrument's output byte array
	static void update();
};

#endif 