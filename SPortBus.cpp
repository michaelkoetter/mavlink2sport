#include "SPortBus.h"
#include "SPort.h"

#include "Arduino.h"

SPortBus::SPortBus()
	: uart(SPORT_SERIAL), checksum(0) {

	SPORT_SERIAL.begin(SPORT_BAUD);
	SPORT_SERIAL_INIT()
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
			PollSensor(data);
		} else {
			data = uart.read(); // swallow everything else...
		}
	}
}

void SPortBus::Send(SPortData_t& data) {
	SPORT_SERIAL_BEGIN_TX()

	Write(data.header);
	Write((uint8_t*) &data.dataTypeId, 2);
	Write((uint8_t*) &data.data, 4);
	data.checksum = 0xFF - checksum;
	Write(data.checksum);

	checksum = 0;
	uart.flush();

	SPORT_SERIAL_END_TX()

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

#ifdef SPORT_DEBUG_VERBOSE
	Serial.printf("SPort | >>> sent %#04x\n", byte);
#endif

	return s;
}

void SPortBus::AttachSensor(SPortPhyID phyId, SPortSensor& sensor) {
	int index = SPORT_SENSOR_INDEX(phyId);
	if (index < SPORT_SENSORS) {
		sensors[index] = &sensor;
	}
}

size_t SPortBus::Write(uint8_t* buffer, size_t len) {
	size_t written = 0;
	for (size_t i = 0; i < len; i++) {
		written += Write(buffer[i]);
	}
	return written;
}

void SPortBus::PollSensor(uint8_t phyId) {
	int index = SPORT_SENSOR_INDEX(phyId);
	if (index < SPORT_SENSORS) {
		SPortSensor *sensor = sensors[index];
		if (sensor != NULL) {
			SPortData_t dataFrame = { DATA_FRAME, 0 };
			if (sensor->Poll(&dataFrame)) {
				Send(dataFrame);
			}
		}
	}
}
