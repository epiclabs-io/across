#ifndef _ACROSS_
#define _ACROSS_

// defines language constructs to use in order to ensure cross-compiler compatibility


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include <avr/pgmspace.h>

#define ACROSS_WRITE_REG(reg, value) (reg) = (value)

#else

#if defined(WIN32) || defined(UNIX)

#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO_MAIN

#include "VirtualHardware/Arduino.h"


//macro to use in order to write to microcontroller registers
#define ACROSS_WRITE_REG(reg, value) ACross_writeReg((reg), (value))
#define ACROSS_READ_REG(reg, value) ACross_readReg((reg), (value))


void ACross_writeReg(uint16_t regAddress, uint8_t value);
uint8_t ACross_readReg(uint16_t regAddress);


#endif // WIN32/UNIX
#endif //CONDITIONAL COMPILATION


// COMMON DEFINITIONS


#define dprintln(s) Serial.println(s)
#define dprint(s) Serial.print(s)
#define dbinprintln(b) Serial.println(b,BIN)



#endif