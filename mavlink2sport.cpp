#include "mavlink2sport.h"

#include "SPortBus.h"
#include "VFASSensor.h"

#define MAVLINK2SPORT_DEBUG 1

VFASSensor vfas;
SPortBus bus;

void setup()
{
#ifdef MAVLINK2SPORT_DEBUG
	Serial.begin(9600);
	Serial.println("MAVLink2SPort | setup() ...");
#endif



#ifdef MAVLINK2SPORT_DEBUG
	Serial.println("MAVLink2SPort | setup() done");
#endif
}

void loop()
{
	bus.Process();
}
