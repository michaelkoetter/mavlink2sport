#ifndef SPORT_H_
#define SPORT_H_

#include "inttypes.h"

/*
 * FrSky S.Port protocol
 *
 * Protocol info and IDs gathered from the following sources:
 *
 *   https://code.google.com/p/telemetry-convert/wiki/FrSkySPortProtocol
 *   https://www.ordinoscope.net/static/frsky-arduino/FrskySP/doc/html/index.html
 */

//#define SPORT_DEBUG 			1
//#define SPORT_DEBUG_VERBOSE		1

// indicates receiver polling a frame
#define POLL_FRAME				0x7E

// byte-stuffing "escapes" 0x7E so it doesn't appear on the bus unless the receiver is polling
#define BYTESTUFF				0x7D
#define STUFF_MASK				0x20

// start of a data frame
#define DATA_FRAME              0x10



// data type IDs
#define ALT_FIRST_ID            0x0100
#define ALT_LAST_ID             0x010f
#define VARIO_FIRST_ID          0x0110
#define VARIO_LAST_ID           0x011f
#define CURR_FIRST_ID           0x0200
#define CURR_LAST_ID            0x020f
#define VFAS_FIRST_ID           0x0210
#define VFAS_LAST_ID            0x021f
#define CELLS_FIRST_ID          0x0300
#define CELLS_LAST_ID           0x030f
#define T1_FIRST_ID             0x0400
#define T1_LAST_ID              0x040f
#define T2_FIRST_ID             0x0410
#define T2_LAST_ID              0x041f
#define RPM_FIRST_ID            0x0500
#define RPM_LAST_ID             0x050f
#define FUEL_FIRST_ID           0x0600
#define FUEL_LAST_ID            0x060f
#define ACCX_FIRST_ID           0x0700
#define ACCX_LAST_ID            0x070f
#define ACCY_FIRST_ID           0x0710
#define ACCY_LAST_ID            0x071f
#define ACCZ_FIRST_ID           0x0720
#define ACCZ_LAST_ID            0x072f
#define GPS_LONG_LATI_FIRST_ID  0x0800
#define GPS_LONG_LATI_LAST_ID   0x080f
#define GPS_ALT_FIRST_ID        0x0820
#define GPS_ALT_LAST_ID         0x082f
#define GPS_SPEED_FIRST_ID      0x0830
#define GPS_SPEED_LAST_ID       0x083f
#define GPS_COURS_FIRST_ID      0x0840
#define GPS_COURS_LAST_ID       0x084f
#define GPS_TIME_DATE_FIRST_ID  0x0850
#define GPS_TIME_DATE_LAST_ID   0x085f
#define A3_FIRST_ID             0x0900
#define A3_LAST_ID              0x090f
#define A4_FIRST_ID             0x0910
#define A4_LAST_ID              0x091f
#define AIR_SPEED_FIRST_ID      0x0a00
#define AIR_SPEED_LAST_ID       0x0a0f
#define RSSI_ID                 0xf101
#define ADC1_ID                 0xf102
#define ADC2_ID                 0xf103
#define BATT_ID                 0xf104
#define SWR_ID                  0xf105
#define XJT_VERSION_ID          0xf106
#define NO_DATA_ID				0x0000

// sensor "physical id" + checksum
enum SPortPhyID {
	ID0 = 0x00,  ID1 = 0xA1,  ID2 = 0x22,  ID3 = 0x83,  ID4 = 0xE4,  ID5 = 0x45,  ID6 = 0xC6,
	ID7 = 0x67,  ID8 = 0x48,  ID9 = 0xE9, ID10 = 0x6A, ID11 = 0xCB, ID12 = 0xAC, ID13 = 0x0D,
	ID14 = 0x8E, ID15 = 0x2F, ID16 = 0xD0, ID17 = 0x71, ID18 = 0xF2, ID19 = 0x53, ID20 = 0x34,
	ID21 = 0x95, ID22 = 0x16, ID23 = 0xB7, ID24 = 0x98, ID25 = 0x39, ID26 = 0xBA, ID27 = 0x1B
};

struct SPortData_t {
	uint8_t		header;
	uint16_t 	dataTypeId;
	uint32_t 	data;
	uint8_t		checksum;
};

#endif /* SPORT_H_ */
