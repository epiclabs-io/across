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
	static const char INFO_LEVEL_STR[] PROGMEM = "INFO";
	static const char DEBUG_LEVEL_STR[] PROGMEM = "DEBUG";
	static const char TRACE_LEVEL_STR[] PROGMEM = "TRACE";
	const char* const LOG_LEVEL_TABLE[] PROGMEM = { ASSERT_LEVEL_STR, ERROR_LEVEL_STR, WARN_LEVEL_STR, INFO_LEVEL_STR, DEBUG_LEVEL_STR, TRACE_LEVEL_STR };
	
	void log(uint8_t level, PGM_P module, const __FlashStringHelper* pattern, ...)
	{
		
		Serial.print('[');
		Serial.print((__FlashStringHelper*)NATIVE_FUNCTION_PTR(LOG_LEVEL_TABLE[level]));
		Serial.print(F("]\t["));
		Serial.print((__FlashStringHelper*)module);
		Serial.print(F("]\t"));

		va_list args;
		va_start(args, pattern);
		vprintf_P((const char*)pattern, args);
		va_end(args);

		Serial.println();
	}
};

