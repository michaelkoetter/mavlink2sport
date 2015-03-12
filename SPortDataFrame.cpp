#include "SPortDataFrame.h"

SPortDataFrame::SPortDataFrame(uint16_t dataTypeId, uint32_t data)
	: dataTypeId(dataTypeId), data(data) {
}

SPortDataFrame::~SPortDataFrame() {
}

void SPortDataFrame::send(SPortBus &bus) {
	// TODO:
	// - send data
	// - calculate checksum
}
