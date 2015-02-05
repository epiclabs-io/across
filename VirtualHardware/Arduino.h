#ifndef _VARDUINO_
#define _VARDUINO_



#if defined(WIN32)

#include <Windows.h>
#include <inttypes.h>
#define millis() GetTickCount()

#else
#include <sys/time.h>
#include <unistd.h>

uint32_t millis()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec / 1000;
}

#endif

#if defined(WIN32) || defined(UNIX)
	#include <iostream>

#include "avr/io.h"


using namespace std;

#define bit(b) (1UL << (b))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define true 0x1
#define false 0x0

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

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

#define __inline__
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define NOINLINE
#define ALWAYSINLINE

#define waitChar() Serial.waitAvailable(INFINITE);
#define strncmp_P strncmp
#define strcmp_P strcmp


#include "VirtualSerial.h"

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t value);
int16_t digitalRead(uint8_t pin);
int16_t analogRead(uint8_t pin);
void analogReference(uint8_t mode);
void analogWrite(uint8_t pin, int value);
void delay(uint32_t milliseconds);

int FreeRam(void);

extern VirtualSerial Serial;

#include "pins_arduino.h"


#endif
#endif
