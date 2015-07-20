#include "LPC8xx.h"
// #include "lpc8xx_gpio.h"

#include "onewire.h"
// #include "crc8.h"

// #include "delay.h"


uint32_t owPort;
uint32_t owPin;

void owInit(int port, int pin) {
	owPort = port;
	owPin = pin;
}

void owSetLow() {
	// set direction output
	GPIOSetDir(owPort, owPin, 1);
	// set low
	GPIOSetBitValue(owPort, owPin, 0);
}

void owSetHigh() {
	// set direction input (high Z) and let pull-up R bring high
	GPIOSetDir(owPort, owPin, 0);
}

int owReadInt() {
	GPIOSetDir(owPort, owPin, 0);
	return GPIOGetPinValue(owPort, owPin);
}

/**
 * Issue a read slot and return the result. The result must be read within
 * 15µs of the
 *
 * @return 0 or 1
 */
int owReadBit() {
	//GPIOSetBitValue(0,2, 0);//debug

	// The read slow starts with the bus is diven low.
	// We have 15µs from the falling edge read the bus.
	owSetLow();
	delay(1); // Must be held low for at least 1µs

	// Bring bus high again. And read within the 15µs time interval
	// (already a few µs used by by now...)
	owSetHigh();
	delay(1);

	//GPIOSetBitValue(0,2, 1); //debug
	int b = owReadInt();
	//GPIOSetBitValue(0,2, 0); //debug

	// Read slots must be a minimum of 60µs in duration with a minimum of 1µs
	// recovery time between slots. Rather than monitor bus to check for end
	// of slot, just delay for a period well exceeding the 60µs slot time.
	delayMicroseconds(65);

	//GPIOSetBitValue(0,2, 1); //debug

	return b;
}

int owReset() {
	owSetLow();
	delayMicroseconds(480);
	owSetHigh();
	delayMicroseconds(70);

	int detect = owReadInt();
	owSetHigh();

	delayMicroseconds(410);

	return ~detect;
}

void owWriteBit(int b) {

	// Write slot duration min 60µs
	owSetLow();
	if (b) {
		// having trouble getting this in the 1-15µs range. Need better delay mechanism.
		delay(1); // max 15µs, min 1µs (?)
		owSetHigh();
		delayMicroseconds(60);
	} else {
		delayMicroseconds(66);
		owSetHigh();
	}

	// Recovery time
	delayMicroseconds(5);
}
void owWriteByte(int data) {
	int i;

	// Send LSB first.

	for (i = 0; i < 8; i++) {
		owWriteBit(data & 0x01);
		data >>= 1;
	}
}

int owReadByte() {
	int i, data = 0;
	for (i = 0; i < 8; i++) {
		data >>= 1;
		data |= owReadBit() ? 0x80 : 0x00;
	}
	return data;
}


uint64_t owReadBigInt() {
	uint64_t data = 0;

	int i;
	for (i = 0; i < 8; i++) {
		data <<= 8;
		data |= owReadByte();
	}

	return data;
}

