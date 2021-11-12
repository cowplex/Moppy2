/*
 * 
 */

#include "MoppyOutputShift.h"

// Num Bits is the number of active bits. Does not have to be divisible by 8.
MoppyOutputShift::MoppyOutputShift(uint8_t numBits, uint8_t latchPin) : 
	latch(latchPin), bits(numBits), bytes(numBits/8+1)
{
	data = new uint8_t[bytes]();

	pinMode(latch, OUTPUT);
	SPI.begin();
	SPI.beginTransaction(SPISettings(16000000, LSBFIRST, SPI_MODE0));
}

uint8_t MoppyOutputShift::getBitCount()
{
	return bits;
}

uint8_t MoppyOutputShift::getByteCount()
{
	return bytes;
}

void MoppyOutputShift::write(uint8_t *d)
{
	if(memcmp(data, d, bytes)) // If we have new data
	{
		memcpy(&data, &d, bytes); // update tracking

		digitalWrite(latch, LOW);

		// Shift bit array out
		SPI.transfer(data, bytes);

		// Latch high - will update shift register output to data just latched in
		digitalWrite(latch, HIGH);
	}
}