/*
 *
 */

#include <numeric>
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
    // Ensure we have at least as many outputs as device bits
	if(std::accumulate(device_bits.begin(), device_bits.end(), 0) > std::accumulate(output_bits.begin(), output_bits.end(), 0))
		return;

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

void ICACHE_RAM_ATTR MoppySystemController::update()
{
	for(uint8_t i = 0; i < devices.size(); ++i)
	    devices[i]->tick();

	uint8_t devd = 0;
	uint8_t devd_bit = 0;
	uint8_t outd_bit = 0;
	for(uint8_t outd = 0; outd < outputs.size(); ++outd)
	{
		outd_bit = 0;
		uint8_t * d = new uint8_t[outputs[outd]->getByteCount()];

		while(outd_bit < outputs[outd]->getBitCount())
		{
			if(devd < devices.size())
			{
				if(devd_bit >= devices[devd]->getBits())
				{
					devd_bit = 0;
					++devd;
					continue;
				}
				d[outd_bit/8] &= devices[devd]->getOut()[devd_bit] << (outd_bit % 8);
			}
			else
			{
				break;
			}
			++outd_bit;
			++devd_bit;
		}
		outputs[outd]->write(d);
	}
	//
}
