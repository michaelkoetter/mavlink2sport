#include "mavlink2sport.h"

#include "SPortBus.h"
#include "VFASSensor.h"
#include "MAVLink.h"
#include "SystemStatusProcessor.h"

#define MAVLINK2SPORT_DEBUG 1

VFASSensor vfas;
SPortBus bus;

MAVLink mavlink;
SystemStatusProcessor sys_status(vfas);

void setup()
{
#ifdef MAVLINK2SPORT_DEBUG
	Serial.begin(9600);
	Serial.println("MAVLink2SPort | setup() ...");
#endif

	bus.AttachSensor(VFAS_DEFAULT_ID, vfas);
	mavlink.AddMessageProcessor(&sys_status);

#ifdef MAVLINK2SPORT_DEBUG
	Serial.println("MAVLink2SPort | setup() done");
#endif
}

void loop()
{
	mavlink.Process();
	bus.Process();
}
