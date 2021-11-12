/*
 * 
 */

#ifndef MOPPY_SRC_MOPPYOUTPUTSHIFT_H_
#define MOPPY_SRC_MOPPYOUTPUTSHIFT_H_

#include <Arduino.h>
#include <SPI.h>
//#include <vector>
#include "MoppyOutput.h"

class MoppyOutputShift : public MoppyOutput
{
public:
	MoppyOutputShift(uint8_t numBits, uint8_t latchPin);
	uint8_t getBitCount();
	uint8_t getByteCount();
	void write(uint8_t *d);
protected:

private:
	const uint8_t latch;
	const uint8_t bits, bytes;
	uint8_t * data;
};


#endif