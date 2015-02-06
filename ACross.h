#ifndef _ACROSS_
#define _ACROSS_

// defines language constructs to use in order to ensure cross-compiler compatibility


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include <avr/pgmspace.h>

#define NATIVE_FUNCTION_PTR(ptr) pgm_read_word(&(ptr))

#else

#if defined(WIN32) || defined(UNIX)

#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO_MAIN

#include "VirtualHardware/Arduino.h"




#endif // WIN32/UNIX
#endif //CONDITIONAL COMPILATION


// COMMON DEFINITIONS


#define dprintln(s) Serial.println(s)
#define dprint(s) Serial.print(s)
#define dbinprintln(b) Serial.println(b,BIN)

void AC_halt(uint16_t errorCode);


#endif