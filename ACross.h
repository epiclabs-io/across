#ifndef _WARDUINO_
#define _WARDUINO_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include <avr/pgmspace.h>

#define NATIVE_FUNCTION_PTR(ptr) pgm_read_word(&(ptr))
#define PGM_STR_PTR(ptr) (PGM_P)pgm_read_word(&(ptr))
#define pgm_read_wordRef(x) pgm_read_word(&(x))

/** Store and print a string in flash memory.*/
#define PgmPrint(x) SerialPrint_P(PSTR(x))
/** Store and print a string in flash memory followed by a CR/LF.*/
#define PgmPrintln(x) SerialPrintln_P(PSTR(x))
/** Defined so doxygen works for function definitions. */
#define NOINLINE __attribute__((noinline))
#define ALWAYSINLINE __attribute__((always_inline))  //e.g. static inline  void readValue()

//------------------------------------------------------------------------------
/**
* %Print a string in flash memory to the serial port.
*
* \param[in] str Pointer to string stored in flash memory.
*/
NOINLINE void SerialPrint_P(PGM_P str);
//------------------------------------------------------------------------------
/**
* %Print a string in flash memory followed by a CR/LF.
*
* \param[in] str Pointer to string stored in flash memory.
*/
NOINLINE void SerialPrintln_P(PGM_P str);
//------------------------------------------------------------------------------
/** Return the number of bytes currently free in RAM. */
int FreeRam(void);
#define waitChar() while (!Serial.available())

#else

#if defined(WIN32) || defined(UNIX)

#include "VirtualHardware/VArduino.h"

#include <iostream>

using namespace std;

#define PgmPrint(s) Serial.print(s)
#define PgmPrintln(s) Serial.println(s)
#define SerialPrintln_P(s) PgmPrintln((s))
#define SerialPrint_P(s) PgmPrint((s))
#define sprintf sprintf_s


#define PROGMEM
#define PGM_P char*
#define NATIVE_FUNCTION_PTR(ptr) ptr
#define PGM_STR_PTR(ptr) ptr


#define NOINLINE
#define ALWAYSINLINE
#define A1 0
#define waitChar() Serial.waitAvailable(INFINITE);
#define strncmp_P strncmp
#define strcmp_P strcmp

#endif // WIN32/UNIX
#endif //CONDITIONAL COMPILATION


// COMMON DEFINITIONS


#define dprintln(s) Serial.println(s)
#define dprint(s) Serial.print(s)
#define dbinprintln(b) Serial.println(b,BIN)
void printFreeRam();




#endif