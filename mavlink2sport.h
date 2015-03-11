#ifndef _mavlink2sport_H_
#define _mavlink2sport_H_
#include "Arduino.h"

#include "mavlink/common/mavlink.h"

#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();

void handle_mavlink_msg(mavlink_message_t *msg);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* _mavlink2sport_H_ */
