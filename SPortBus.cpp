#include "SPortBus.h"
#include "SPortDataFrame.h"
#include "SPort.h"

#include "Arduino.h"

SPortBus::SPortBus(Stream &uart)
	: uart(uart) {
}

SPortBus::~SPortBus() {
}


void SPortBus::Process() {
	uint8_t data = 0;

	while (available()) {
		if (data == POLL_FRAME) {
			// next: sensor PhyId
			data = read();
#ifdef SPORT_DEBUG
			Serial.printf("SPort | poll PhyID: %#04x\n", data);
#endif
			if (data == SPortPhyID::ID2) {
				SPortDataFrame vfas(VFAS_FIRST_ID, 1230);
				vfas.Send(*this);
			}
		} else if (data == DATA_FRAME) {
			SPortDataFrame dataFrame;
			dataFrame.Receive(*this);
		} else {
			data = read();
		}
	}
}

void SPortBus::ResetChecksum(uint8_t header) {
	checksum = 0;
	UpdateChecksum(header);
}

uint8_t SPortBus::GetChecksum() {
	return 0xFF - (checksum & 0x00FF);
}

size_t SPortBus::write(const uint8_t* buffer, size_t size) {
	size_t written = 0;
	for (unsigned int i = 0; i < size; i++) {
		written += write(buffer[i]);
	}

	return written;
}

int SPortBus::UpdateChecksum(int byte) {
	if (byte < 0) return byte;

	checksum += (byte & 0x00FF);
	checksum += checksum >> 8;
	checksum &= 0x00FF;

	return byte;
}

int SPortBus::available() {
	return uart.available();
}

int SPortBus::read() {
	// TODO un-escape 0x7E
	return UpdateChecksum(uart.read());
}

int SPortBus::peek() {
	return uart.peek();
}

void SPortBus::flush() {
	uart.flush();
}

size_t SPortBus::write(uint8_t b) {
#ifdef SPORT_DEBUG
	Serial.printf("SPort | >>> write: %#04x\n", b);
#endif

	// we need to escape 0x7E so it doesn't appear on the bus
	size_t s = 0;
	if (b == 0x7E) {
		s+= uart.write(0x7D);
		s+= uart.write(0x5E);
	} else if (b == 0x7D) {
		s+= uart.write(0x7D);
		s+= uart.write(0x5D);
	} else {
		s+= uart.write(b);
	}

	UpdateChecksum(b);
	return s;
}

