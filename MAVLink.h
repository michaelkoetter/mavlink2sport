#ifndef MAVLINK_H_
#define MAVLINK_H_

#include "mavlink/common/mavlink.h"
#include "Stream.h"
#include "MAVLinkMessageProcessor.h"

#define MAVLINK_DEBUG			1
// #define MAVLINK_DEBUG_VERBOSE	1

#define MAVLINK_SERIAL			Serial2
#define MAVLINK_BAUD			57600

#define MAVLINK_MAX_MSGPROCESSORS			20

class MAVLink {
public:
	MAVLink();
	virtual ~MAVLink();

	void Process();
	void AddMessageProcessor(MAVLinkMessageProcessor *processor);

private:
	Stream			&uart;
	MAVLinkMessageProcessor *processors[MAVLINK_MAX_MSGPROCESSORS] = {};

};

#endif /* MAVLINK_H_ */
