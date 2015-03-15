#ifndef MAVLINK_H_
#define MAVLINK_H_

#include "mavlink/common/mavlink.h"
#include "Stream.h"

#define MAVLINK_DEBUG			1
// #define MAVLINK_DEBUG_VERBOSE	1

#define MAVLINK_SERIAL			Serial2
#define MAVLINK_BAUD			57600


class MAVLink {
public:
	MAVLink();
	virtual ~MAVLink();

	void Process();

private:
	Stream			&uart;
};

#endif /* MAVLINK_H_ */
