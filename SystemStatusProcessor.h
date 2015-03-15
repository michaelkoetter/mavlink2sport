#ifndef SYSTEMSTATUSPROCESSOR_H_
#define SYSTEMSTATUSPROCESSOR_H_

#include "MAVLinkMessageProcessor.h"
#include "VFASSensor.h"

class SystemStatusProcessor : public MAVLinkMessageProcessor {
public:
	SystemStatusProcessor(VFASSensor &vfas);
	virtual ~SystemStatusProcessor();

	virtual void ProcessMessage(mavlink_message_t *message);
private:
	VFASSensor			&vfas;
};

#endif /* SYSTEMSTATUSPROCESSOR_H_ */
