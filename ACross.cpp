#include "ACross.h"

#if defined(ARDUINO) && ARDUINO >= 100

namespace ACross
{
	void halt(uint16_t errorCode)
	{
		Serial.print("Halt: ");Serial.println(errorCode);
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



