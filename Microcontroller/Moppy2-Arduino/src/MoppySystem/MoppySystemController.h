/*
 * 
 */

#ifndef MOPPY_SRC_MOPPYSYSTEMCONTROLLER_H_
#define MOPPY_SRC_MOPPYSYSTEMCONTROLLER_H_

#include <Arduino.h>
#include <vector>
#include "../MoppyMessageConsumer.h"
#include "../MoppyConfig.h"
#include "MoppyTimer.h"
#include "MoppyOutput.h"

class MoppySystemController : public MoppyMessageConsumer 
{
public:
	MoppySystemController();
	void addDevice(MoppyMessageConsumer *messageConsumer);
	void addOutput(MoppyOutput *output);
	void begin();
	void handleSystemMessage(uint8_t command, uint8_t payload[]);
	void handleDeviceMessage(uint8_t subAddress, uint8_t command, uint8_t payload[]);
protected:

private:
	//MoppyMessageConsumer *devices;
	static std::vector<MoppyMessageConsumer *> devices;
	static std::vector<MoppyOutput *> outputs;
	static std::vector<uint8_t> device_bits;
	static std::vector<uint8_t> output_bits;
	static void update();
};

#endif 