#ifndef MAVLINKMESSAGEPROCESSOR_H_
#define MAVLINKMESSAGEPROCESSOR_H_

#include "mavlink/common/mavlink.h"

class MAVLinkMessageProcessor {
public:
	MAVLinkMessageProcessor();
	virtual ~MAVLinkMessageProcessor();

	virtual void ProcessMessage(mavlink_message_t *message) = 0;
};

#endif /* MAVLINKMESSAGEPROCESSOR_H_ */
