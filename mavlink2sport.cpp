#include "mavlink2sport.h"

#include "SPortBus.h"
#include "VFASSensor.h"
#include "MAVLink.h"

#define MAVLINK2SPORT_DEBUG 1

VFASSensor vfas;
SPortBus bus;

MAVLink mavlink;

void setup()
{
#ifdef MAVLINK2SPORT_DEBUG
	Serial.begin(9600);
	Serial.println("MAVLink2SPort | setup() ...");
#endif

	bus.AttachSensor(VFAS_DEFAULT_ID, vfas);

#ifdef MAVLINK2SPORT_DEBUG
	Serial.println("MAVLink2SPort | setup() done");
#endif
}

void loop()
{
	vfas.setVoltage(1.2);
	vfas.setCurrent(3.4);

	mavlink.Process();
	bus.Process();
}
