#include "Arduino.h"
#include "ACRPCCLient.h"

#include <stdio.h>
VirtualSerial Serial;



void pinMode(uint8_t pin, uint8_t mode)
{
	if (!ACRPCCLient::hostLinkEnabled)
		printf("pinMode(pin = %d, mode=%d)\n", pin, mode);
	else
	{
		invoke_RPC(pinMode, pin, mode);
	}
}

void digitalWrite(uint8_t pin, uint8_t value)
{
	if (!ACRPCCLient::hostLinkEnabled)
		printf("digitalWrite(pin=%d, value=%d)\n", pin, value);
	else
	{
		invoke_RPC(digitalWrite, pin, value);
	}
}

int16_t digitalRead(uint8_t pin)
{
	if (!ACRPCCLient::hostLinkEnabled)
	{
		printf("digitalRead(pin=%d)\n", pin);
		return 0;
	}
	else
	{

		int16_t ret;
		invoke_RPC(digitalRead, pin, &ret);
		return ret;

	}
}

int16_t analogRead(uint8_t pin)
{
	if (!ACRPCCLient::hostLinkEnabled)
	{
		printf("analogRead(pin=%d)\n", pin);
		return 0;
	}
	else
	{

		int16_t ret;
		invoke_RPC(analogRead, pin, &ret);
		return ret;

	}
}

void analogReference(uint8_t mode)
{
	printf("analogReference(mode=%d)\n", mode);
}
void analogWrite(uint8_t pin, int value)
{
	if (!ACRPCCLient::hostLinkEnabled)
		printf("analogWrite(pin=%d, value=%d)\n", pin, value);
	else
	{
		invoke_RPC(analogWrite, pin, value);
	}
}

void delay(uint32_t milliseconds)
{
	uint32_t wait = millis() + milliseconds;

	while ((int32_t)(wait - millis()) > 0);
}


//all this does is take the "millis" from the OS at startup time and consider that the starting value
//so that we can return millis() as 0 when the program was launched.
class MillisClass
{
	static uint32_t initialMillis;
	static uint32_t raw_millis()
	{

		#if defined(WIN32)
				return GetTickCount();
		#else
				struct timeval t;
				gettimeofday(&t, NULL);
				return t.tv_sec * 1000 + t.tv_usec / 1000;
		#endif

	}
public:
	MillisClass()
	{
		initialMillis = raw_millis();
	}


	static uint32_t millis()
	{
		return raw_millis() - initialMillis;
	}

}millisClass;

uint32_t MillisClass::initialMillis;



uint32_t millis()
{
	return MillisClass::millis();
}




