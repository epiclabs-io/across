// ACross cross-compile development toolkit
// Author: Javier Peletier <jm@friendev.com>
// Summary: ACross allows you to build your Arduino projects using Visual Studio.
// Your Arduino code is cross - compiled and runs in your PC, which enables
// step - by - step debugging
//
// Copyright (c) 2015 All Rights Reserved, http://friendev.com
//
// This source is subject to the GPLv2 license.
// Please see the License.txt file for more information.
// All other rights reserved.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#ifndef _ACROSS_
#define _ACROSS_

// defines language constructs to use in order to ensure cross-compiler compatibility


#if defined(ARDUINO) && ARDUINO >= 100

#define ACROSS_ARDUINO

#include "Arduino.h"
#include <avr/pgmspace.h>
#include "ACprintf.h"

#define NATIVE_FUNCTION_PTR(ptr) pgm_read_word(&(ptr))

		extern int  __bss_end;
		extern int* __brkval;

#define vprintf_P(fmt,...) vfprintf_P(stdout,(fmt),##__VA_ARGS__)

#define NOINLINE __attribute__((noinline))
#define ALWAYSINLINE __attribute__((always_inline))  //e.g. static inline  void readValue()

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


namespace ACross
{

	
	void init();
	void halt(uint16_t errorCode);
	uint16_t getFreeRam(void);
	void log(uint8_t level, PGM_P module, const __FlashStringHelper* pattern, ...);




};

#endif