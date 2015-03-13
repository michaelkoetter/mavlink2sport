#include "SPortSensor.h"

SPortSensor::SPortSensor(SPortPhyID phyId)
	: phyId(phyId) {

}

SPortSensor::~SPortSensor() {
}

bool SPortSensor::Poll(SPortPhyID phyId, SPortData_t* data) {
	if (phyId == this->phyId) return DoPoll(data);
	return false;
}
