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


#include "ACross.h"
#include <stdarg.h>

#if defined(ARDUINO) && ARDUINO >= 100

namespace ACross
{
	void init()
	{
#ifdef _DEBUG
		printf_serial_init();
#endif

	}

	void halt(uint16_t errorCode)
	{
		Serial.print(F("Halt: "));Serial.println(errorCode);
		while(1);
	}

	uint16_t getFreeRam(void)
	{

		int free_memory;
		if (reinterpret_cast<int>(__brkval) == 0) {
			// if no heap use from end of bss section
			free_memory = reinterpret_cast<int>(&free_memory)
				- reinterpret_cast<int>(&__bss_end);
		}
		else {
			// use from top of stack to heap
			free_memory = reinterpret_cast<int>(&free_memory)
				- reinterpret_cast<int>(__brkval);
		}
		return free_memory;
	}
};

#else

namespace ACross
{
	void init()
	{

	}

	void halt(uint16_t errorCode)
	{
		Serial.print("Halt: "); Serial.println(errorCode);
		getchar();
		exit(errorCode);
	}

	uint16_t getFreeRam(void)
	{
		return 1979;
	}


};

#endif


namespace ACross
{
	static const char ASSERT_LEVEL_STR[] PROGMEM = "ASSERT-FAIL";
	static const char ERROR_LEVEL_STR[] PROGMEM = "ERROR";
	static const char WARN_LEVEL_STR[] PROGMEM = "WARN";
	static const char DEBUG_LEVEL_STR[] PROGMEM = "DEBUG";
	static const char INFO_LEVEL_STR[] PROGMEM = "INFO";
	static const char TRACE_LEVEL_STR[] PROGMEM = "TRACE";
	const char* const LOG_LEVEL_TABLE[] PROGMEM = { ASSERT_LEVEL_STR, ERROR_LEVEL_STR, WARN_LEVEL_STR, DEBUG_LEVEL_STR,INFO_LEVEL_STR, TRACE_LEVEL_STR };

#ifdef ACROSS_PC
	//AVR libc allows to use %S in format strings for PROGMEM
	//this function convers this %S to %s instead, so this works correctly when cross-compiling in Windows/UNIX
	__FlashStringHelper* fixPattern(const __FlashStringHelper* pattern)
	{
		char* p = (char*)pattern;
		char* fixed = new char[strlen(p) + 1];
		char* f = fixed;

		while (*p)
		{
			*f = *p;
			if (*p == '%')
			{
				p++;
				f++;

				if (*p == 'S')
				{
					*f = 's';
					p++;
					f++;
				}
			}
			else
			{
				p++;
				f++;
			}
		}
		*f = 0;

		return ( __FlashStringHelper*)fixed;
	}
#endif

	void log(uint8_t level, PGM_P module, const __FlashStringHelper* pattern, ...)
	{
		__FlashStringHelper* fmt;
#ifdef ACROSS_PC
		fmt = fixPattern(pattern);
#else
		fmt = (__FlashStringHelper*)pattern;
#endif

	//	printf_P(PSTR("[%S]\t[%S]\t"), NATIVE_FUNCTION_PTR(LOG_LEVEL_TABLE[level]), module);

		Serial.print('[');
		Serial.print((__FlashStringHelper*)NATIVE_FUNCTION_PTR(LOG_LEVEL_TABLE[level]));
		Serial.print(F("]\t["));
		Serial.print((__FlashStringHelper*)module);
		Serial.print(F("]\t"));
		va_list args;
		va_start(args, pattern);

#ifdef ACROSS_PC
		char buffer[256];
		int i = vsprintf_s<sizeof(buffer)>(buffer, (char*)fmt, args);
		Serial.write((uint8_t*)buffer, i);

		delete (char*)fmt;
#else

		vprintf_P((const char*)fmt, args);


#endif
		va_end(args);
		Serial.println();
	}
};

