#include "SPort.h"
#include "SPortDataFrame.h"
#include "Arduino.h"

SPortDataFrame::SPortDataFrame(uint16_t dataTypeId, uint32_t data)
	: dataTypeId(dataTypeId), data(data), valid(true) {
}

SPortDataFrame::~SPortDataFrame() {
}

void SPortDataFrame::Send(SPortBus &bus) {
	bus.ResetChecksum();

	UART0_C3 |= 32;

	bus.write(DATA_FRAME);
	bus.write((uint8_t*) &dataTypeId, 2);
	bus.write((uint8_t*) &data, 4);

	uint8_t busChecksum = bus.GetChecksum();
	bus.write(busChecksum);

	bus.flush();

	UART0_C3 ^= 32;
#ifdef SPORT_DEBUG
	Serial.printf("SPort | >>> send data id: %#06x data: %#010x (%d) b.checksum: %#04x valid: %d\n",
			dataTypeId, data, data, busChecksum, valid);
#endif
}

bool SPortDataFrame::Receive(SPortBus &bus) {
	bus.ResetChecksum(DATA_FRAME);
	bus.readBytes((uint8_t*) &dataTypeId, 2);
	bus.readBytes((uint8_t*) &data, 4);

	uint8_t busChecksum = bus.GetChecksum();
	uint8_t packetChecksum = bus.read();

	valid = (packetChecksum == busChecksum);

#ifdef SPORT_DEBUG
	Serial.printf("SPort | <<< receive data id: %#06x data: %#010x (%d) p.checksum: %#04x b.checksum: %#04x valid: %d\n",
			dataTypeId, data, data, packetChecksum, busChecksum, valid);
#endif

	return true;
}
