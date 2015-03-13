#include "VFASSensor.h"

VFASSensor::VFASSensor()
	: SPortSensor(VFAS_DEFAULT_ID), pollSeq(0), voltage(0), current(0) {
}

VFASSensor::~VFASSensor() {
}

unsigned int VFASSensor::getCurrent() const {
	return current;
}

void VFASSensor::setCurrent(unsigned int current) {
	this->current = current;
}

float VFASSensor::getVoltage() const {
	return voltage;
}

void VFASSensor::setVoltage(float voltage) {
	this->voltage = voltage;
}

bool VFASSensor::DoPoll(SPortData_t* data) {
	switch (pollSeq++ % 2) {
	case 0:
		data->dataTypeId = VFAS_FIRST_ID;
		data->data = voltage * 100;
		break;
	case 1:
		data->dataTypeId = CURR_FIRST_ID;
		data->data = current;
		break;
	}
	return true;
}
