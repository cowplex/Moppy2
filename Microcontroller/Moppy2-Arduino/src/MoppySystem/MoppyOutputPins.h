/*
 * 
 */

#ifndef MOPPY_SRC_MOPPYOUTPUTPINS_H_
#define MOPPY_SRC_MOPPYOUTPUTPINS_H_

#include <Arduino.h>
#include <vector>
#include "MoppyOutput.h"

class MoppyOutputPins : public MoppyOutput
{
public:
    void addPin(uint8_t pin);
    uint8_t getBitCount();
protected:

private:
    std::vector<uint8_t> pinList;
};


#endif