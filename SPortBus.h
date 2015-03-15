#ifndef SPORTBUS_H_
#define SPORTBUS_H_

#define SPORT_BAUD 57600

#include "Stream.h"
#include "SPortSensor.h"

#define SPORT_SENSORS				28
#define SPORT_SENSOR_INDEX(phyId)	(phyId & 0x1F)

class SPortBus {
public:
	SPortBus();
	virtual ~SPortBus();

	void Process();
	void AttachSensor(SPortPhyID phyId, SPortSensor &sensor);

private:
	void PollSensor(uint8_t phyId);
	void Send(SPortData_t &data);
	size_t Write(uint8_t byte);
	size_t Write(uint8_t *buffer, size_t len);

	Stream		&uart;
	short		checksum;
	SPortSensor	*sensors[SPORT_SENSORS] = {};
};

#endif /* SPORTBUS_H_ */
