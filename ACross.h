#ifndef _ACROSS_
#define _ACROSS_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include <avr/pgmspace.h>



#else

#if defined(WIN32) || defined(UNIX)

#define __AVR_ATmega328p__
#define __AVR_ATmega328P__


#include "VirtualHardware/Arduino.h"


#endif // WIN32/UNIX
#endif //CONDITIONAL COMPILATION


// COMMON DEFINITIONS


#define dprintln(s) Serial.println(s)
#define dprint(s) Serial.print(s)
#define dbinprintln(b) Serial.println(b,BIN)



#endif