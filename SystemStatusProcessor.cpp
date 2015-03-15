/*
 * SystemStatusProcessor.cpp
 *
 *  Created on: 15.03.2015
 *      Author: Michael
 */

#include "SystemStatusProcessor.h"

SystemStatusProcessor::SystemStatusProcessor(VFASSensor& vfas)
	: vfas(vfas) {
}

SystemStatusProcessor::~SystemStatusProcessor() {
}

void SystemStatusProcessor::ProcessMessage(mavlink_message_t* message) {
	if (message->msgid == MAVLINK_MSG_ID_SYS_STATUS) {
		mavlink_sys_status_t sys_status;
		mavlink_msg_sys_status_decode(message, &sys_status);

		vfas.setVoltage(sys_status.voltage_battery / 1000);
		vfas.setCurrent(sys_status.current_battery / 100);
	}
}
