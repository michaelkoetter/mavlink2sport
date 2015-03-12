#ifndef SPORTDATAFRAME_H_
#define SPORTDATAFRAME_H_

#include <inttypes.h>
#include "SPort.h"
#include "SPortBus.h"
#include "Stream.h"

class SPortDataFrame {
public:
	SPortDataFrame(uint16_t dataTypeId = NO_DATA_ID, uint32_t = 0);
	virtual ~SPortDataFrame();

	void Send(SPortBus &bus);
	bool Receive(SPortBus &bus);

private:
	uint16_t 	dataTypeId;
	uint32_t 	data;

	bool		valid;
};

#endif /* SPORTDATAFRAME_H_ */
