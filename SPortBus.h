#ifndef SPORTBUS_H_
#define SPORTBUS_H_

#include "Stream.h"
#include "SPortSensor.h"

#define SPORT_SERIAL			Serial1
#define SPORT_BAUD 				57600

#define SPORT_SERIAL_INIT()		UART0_C1 = 0xA0; \
								UART0_C3 = 0x10; \
								UART0_S2 = 0x10;
#define SPORT_SERIAL_BEGIN_TX()	UART0_C3 |= 32;
#define SPORT_SERIAL_END_TX()	UART0_C3 ^= 32;

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
