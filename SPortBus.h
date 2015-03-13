#ifndef SPORTBUS_H_
#define SPORTBUS_H_

#define SPORT_BAUD 57600

#include "Stream.h"
#include "SPortSensor.h"

class SPortBus {
public:
	SPortBus();
	virtual ~SPortBus();

	void Process();
	void Send(SPortData_t &data);

private:
	size_t Write(uint8_t byte);
	size_t Write(uint8_t *buffer, size_t len);

	Stream		&uart;
	short		checksum;
};

#endif /* SPORTBUS_H_ */
