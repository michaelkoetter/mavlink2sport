#ifndef SPORTDATAFRAME_H_
#define SPORTDATAFRAME_H_

#include <inttypes.h>
#include "SPort.h"
#include "SPortBus.h"

class SPortDataFrame {
public:
	SPortDataFrame(uint16_t dataTypeId = NO_DATA_ID, uint32_t = 0);
	virtual ~SPortDataFrame();

	void send(SPortBus &bus);

private:
	uint16_t 	dataTypeId;
	uint32_t 	data;
};

#endif /* SPORTDATAFRAME_H_ */
