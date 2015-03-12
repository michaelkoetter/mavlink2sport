#ifndef SPORTBUS_H_
#define SPORTBUS_H_

#define SPORT_BAUD 57600

#include "Stream.h"
#include "SPortSensor.h"

class SPortBus : public Stream {
public:
	SPortBus(Stream &uart);
	virtual ~SPortBus();

	virtual int available();
	virtual int read();
	virtual int peek();
	virtual void flush();
	virtual size_t write(uint8_t b);
	virtual size_t write(const uint8_t *buffer, size_t size);

	void Process();

	void ResetChecksum(uint8_t header = 0);
	uint8_t GetChecksum();

private:
	int UpdateChecksum(int byte);

	Stream	&uart;
	short	checksum;

};

#endif /* SPORTBUS_H_ */
