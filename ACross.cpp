#include "ACross.h"

#if defined(ARDUINO) && ARDUINO >= 100

void AC_halt(uint16_t errorCode)
{
	Serial.print("Halt: ");Serial.println(errorCode);
	while(1);
}

#else

void AC_halt(uint16_t errorCode)
{
	Serial.print("Halt: "); Serial.println(errorCode);
	getchar();
	exit(errorCode);
}


#endif



