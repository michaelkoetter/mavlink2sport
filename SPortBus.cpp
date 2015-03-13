#include "SPortBus.h"
#include "SPort.h"

#include "Arduino.h"

SPortBus::SPortBus()
	: uart(Serial1), checksum(0) {

	Serial1.begin(SPORT_BAUD);

	UART0_C1 = 0xA0; // Single wire mode
	UART0_C3 = 0x10; // Tx invert
	UART0_S2 = 0x10; // Rx invert
}

SPortBus::~SPortBus() {
}


void SPortBus::Process() {
	uint8_t data = 0;

	while (uart.available()) {
		if (data == POLL_FRAME) {
			// next: sensor PhyId
			data = uart.read();
#ifdef SPORT_DEBUG
			Serial.printf("SPort | poll PhyID: %#04x\n", data);
#endif
		} else {
			data = uart.read(); // swallow everything else...
		}
	}
}

void SPortBus::Send(SPortData_t& data) {
	UART0_C3 |= 32;	// UART transmit


	Write(data.header);
	Write((uint8_t*) &data.dataTypeId, 2);
	Write((uint8_t*) &data.data, 4);
	data.checksum = checksum & 0x00FF;
	Write(data.checksum);

	checksum = 0;
	uart.flush();
	UART0_C3 ^= 32;	// UART receive

#ifdef SPORT_DEBUG
	Serial.printf("SPort | >>> sent data id: %#06x data: %#010x (%d) checksum: %#04x\n",
			data.dataTypeId, data.data, data.data, data.checksum);
#endif
}

size_t SPortBus::Write(uint8_t byte) {
	size_t s = 0;
	if (byte == POLL_FRAME || byte == BYTESTUFF) {
		// byte-stuffing...
		uart.write(BYTESTUFF);
		s+= uart.write(byte ^ STUFF_MASK);
	} else {
		s+= uart.write(byte);
	}

	checksum += byte;
	checksum += checksum >> 8;
	checksum &= 0x00FF;

	return s;
}

size_t SPortBus::Write(uint8_t* buffer, size_t len) {
	size_t written = 0;
	for (size_t i = 0; i < len; i++) {
		written += Write(buffer[i]);
	}
	return written;
}
