#include "ACross.h"

#if defined(ARDUINO) && ARDUINO >= 100

void ACross::halt(uint16_t errorCode)
{
	Serial.print("Halt: ");Serial.println(errorCode);
	while(1);
}

#else

namespace ACross
{

	void halt(uint16_t errorCode)
	{
		Serial.print("Halt: "); Serial.println(errorCode);
		getchar();
		exit(errorCode);
	}

};

#endif



