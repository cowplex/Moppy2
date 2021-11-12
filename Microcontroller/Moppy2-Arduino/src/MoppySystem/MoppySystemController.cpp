/*
 * 
 */

#include "MoppySystemController.h"

std::vector<MoppyMessageConsumer *> MoppySystemController::devices;
std::vector<MoppyOutput *> MoppySystemController::outputs;
std::vector<uint8_t> MoppySystemController::device_bits;
std::vector<uint8_t> MoppySystemController::output_bits;

MoppySystemController::MoppySystemController()
{
    //
}
void MoppySystemController::addDevice(MoppyMessageConsumer *messageConsumer)
{
    devices.push_back(messageConsumer);
    //device_bits.push_back(messageConsumer->);
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
