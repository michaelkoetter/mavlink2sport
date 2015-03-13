#ifndef SPORTSENSOR_H_
#define SPORTSENSOR_H_

#include "SPort.h"

class SPortSensor {
public:
	SPortSensor(SPortPhyID phyId);
	virtual ~SPortSensor();

	virtual bool Poll(SPortPhyID phyId, SPortData_t *data);

protected:
	virtual bool DoPoll(SPortData_t *data) = 0;

private:
	SPortPhyID		phyId;
};

#endif /* SPORTSENSOR_H_ */
