#ifndef VFASSENSOR_H_
#define VFASSENSOR_H_

#include "SPortSensor.h"

#define VFAS_DEFAULT_ID SPortPhyID::ID2

class VFASSensor : public SPortSensor {
public:
	VFASSensor();
	virtual ~VFASSensor();
	unsigned int getCurrent() const;
	void setCurrent(unsigned int current);
	float getVoltage() const;
	void setVoltage(float voltage);

protected:
	virtual bool DoPoll(SPortData_t *data);

private:
	uint32_t		pollSeq;

	float			voltage;
	unsigned int	current;
};

#endif /* VFASSENSOR_H_ */
