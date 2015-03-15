#include "MAVLink.h"
#include "Arduino.h"

MAVLink::MAVLink()
	: uart(MAVLINK_SERIAL) {
	MAVLINK_SERIAL.begin(MAVLINK_BAUD);
}

MAVLink::~MAVLink() {
}

void MAVLink::Process() {
	mavlink_message_t message = {};
	mavlink_status_t status = {};

	while (uart.available()) {
		uint8_t data = uart.read();
#ifdef MAVLINK_DEBUG_VERBOSE
			Serial.printf("MAVLink | <<< rcv %#04x\n", data);
#endif
		if (mavlink_parse_char(MAVLINK_COMM_0, data, &message, &status)) {
#ifdef MAVLINK_DEBUG
			Serial.printf("MAVLink | msg id: %#04x\n", message.msgid);
#endif

			for (int i = 0; i < MAVLINK_MAX_MSGPROCESSORS; i++) {
				if (processors[i] != NULL) {
					processors[i]->ProcessMessage(&message);
				}
			}
		}
	}
}

void MAVLink::AddMessageProcessor(MAVLinkMessageProcessor* processor) {
	for (int i = 0; i < MAVLINK_MAX_MSGPROCESSORS; i++) {
		if (processors[i] == NULL) {
			processors[i] = processor;
			break;
		}
	}
}
