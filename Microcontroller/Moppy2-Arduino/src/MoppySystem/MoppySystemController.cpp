/*
 * 
 */

#include "MoppySystemController.h"

std::vector<MoppyInstrument *> MoppySystemController::devices;
std::vector<MoppyOutput *> MoppySystemController::outputs;
std::vector<uint8_t> MoppySystemController::device_bits;
std::vector<uint8_t> MoppySystemController::output_bits;
std::vector<uint8_t *> MoppySystemController::device_bytes;

MoppySystemController::MoppySystemController()
{
	//
}
void MoppySystemController::addDevice(MoppyInstrument *instrument)
{
	devices.push_back(instrument);
	device_bits.push_back(instrument->getBits());
	device_bytes.push_back(instrument->getOut());
}
void MoppySystemController::addOutput(MoppyOutput *output)
{
	outputs.push_back(output);
	output_bits.push_back(output->getBitCount());
}
void MoppySystemController::begin()
{
	MoppyTimer::initialize(TIMER_RESOLUTION, update);
	for(uint8_t i = 0; i < devices.size(); ++i)
		devices[i]->setup();
}

void MoppySystemController::handleSystemMessage(uint8_t command, uint8_t payload[])
{
	for(uint8_t i = 0; i < devices.size(); ++i)
		devices[i]->handleSystemMessage(command, payload);
}
void MoppySystemController::handleDeviceMessage(uint8_t subAddress, uint8_t command, uint8_t payload[])
{
	for(uint8_t i = 0; i < devices.size(); ++i)
		devices[i]->handleDeviceMessage(subAddress, command, payload);
}

void MoppySystemController::update()
{
	for(uint8_t i = 0; i < devices.size(); ++i)
	    devices[i]->tick();
}
