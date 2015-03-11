#include "mavlink2sport.h"


#define MAVLinkSerial Serial2

mavlink_message_t msg;
mavlink_status_t status;

void setup()
{
	MAVLinkSerial.begin(57600);
}

void loop()
{
	while (MAVLinkSerial.available()) {
		uint8_t c = MAVLinkSerial.read();
		if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
			handle_mavlink_msg(&msg);
		}
	}
}

void handle_mavlink_msg(mavlink_message_t *msg) {

}
