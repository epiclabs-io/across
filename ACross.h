#ifndef _ACROSS_
#define _ACROSS_

// defines language constructs to use in order to ensure cross-compiler compatibility


#if defined(ARDUINO) && ARDUINO >= 100

#define ACROSS_ARDUINO

#include "Arduino.h"
#include <avr/pgmspace.h>

#define NATIVE_FUNCTION_PTR(ptr) pgm_read_word(&(ptr))

		extern int  __bss_end;
		extern int* __brkval;


#else

#if defined(WIN32) || defined(UNIX)

#define ACROSS_PC

#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO_MAIN
#pragma pack(1)
#include "VirtualHardware/Arduino.h"




#endif // WIN32/UNIX
#endif //CONDITIONAL COMPILATION


// COMMON DEFINITIONS

#ifdef _DEBUG
#define ACDEBUG(x) x
#else
#define ACDEBUG(x)
#endif

#define dsprintln(s) ACDEBUG(Serial.println(F(s)))
#define dsprint(s) ACDEBUG(Serial.print(F(s)))


#define dprintln(s) ACDEBUG(Serial.println(s))
#define dprint(s) ACDEBUG(Serial.print(s))


namespace ACross
{

	void halt(uint16_t errorCode);
	uint16_t getFreeRam(void);
};

#endif