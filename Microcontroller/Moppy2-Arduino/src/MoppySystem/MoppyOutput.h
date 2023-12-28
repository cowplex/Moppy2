/*
 *
 */

#ifndef MOPPY_SRC_MOPPYOUTPUT_H_
#define MOPPY_SRC_MOPPYOUTPUT_H_

#include <Arduino.h>
#include "../MoppyMessageConsumer.h"
#include "MoppyTimer.h"

class MoppyOutput
{
public:
    virtual uint8_t getBitCount();
    virtual uint8_t getByteCount();
    virtual void write(uint8_t *d);
protected:

private:

};

#endif
