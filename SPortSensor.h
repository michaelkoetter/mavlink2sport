#ifndef SPORTSENSOR_H_
#define SPORTSENSOR_H_

#include "SPort.h"

class SPortSensor {
public:
	SPortSensor();
	virtual ~SPortSensor();

	virtual bool Poll(SPortData_t *data) = 0;
};

#endif /* SPORTSENSOR_H_ */
