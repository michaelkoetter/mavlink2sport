#include "mavlink2sport.h"

#include "SPortBus.h"

#define MAVLINK2SPORT_DEBUG 1

SPortBus bus(Serial1);

void setup()
{
#ifdef MAVLINK2SPORT_DEBUG
	Serial.begin(9600);
	Serial.println("MAVLink2SPort | setup() ...");
#endif

	Serial1.begin(SPORT_BAUD);
	UART0_C1 = 0xA0; // Single wire mode
	UART0_C3 = 0x10; // Tx invert
	UART0_S2 = 0x10; // Rx invert


#ifdef MAVLINK2SPORT_DEBUG
	Serial.println("MAVLink2SPort | setup() done");
#endif
}

void loop()
{
	bus.Process();
}
