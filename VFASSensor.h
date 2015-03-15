#ifndef VFASSENSOR_H_
#define VFASSENSOR_H_

#include "SPortSensor.h"

#define VFAS_DEFAULT_ID SPortPhyID::ID2

class VFASSensor : public SPortSensor {
public:
	VFASSensor();
	virtual ~VFASSensor();
	float getCurrent() const;
	void setCurrent(float current);
	float getVoltage() const;
	void setVoltage(float voltage);

	virtual bool Poll(SPortData_t *data);

private:
	uint32_t		pollSeq;

	float			voltage;
	float			current;
};

#endif /* VFASSENSOR_H_ */
