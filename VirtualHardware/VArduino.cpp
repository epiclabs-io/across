#include "VArduino.h"
#include "ACHostLink.h"
#include <stdio.h>
VirtualSerial Serial;



void pinMode(uint8_t pin, uint8_t mode)
{
	ACHostLink::pinMode(pin, mode);
}

void digitalWrite(uint8_t pin, uint8_t value)
{
	ACHostLink::digitalWrite(pin, value);
}

int16_t digitalRead(uint8_t pin)
{
	printf("digitalRead(pin=%d)\n", pin);
	return 0;
}

int16_t analogRead(uint8_t pin)
{
	printf("analogRead(pin=%d)\n", pin);
	return 0;
}

void analogReference(uint8_t mode)
{
	printf("analogReference(mode=%d)\n", mode);
}
void analogWrite(uint8_t pin, int value)
{
	printf("analogWrite(pin=%d, value=%d)\n", pin, value);
}

//------------------------------------------------------------------------------
/** Return the number of bytes currently free in RAM. */
int FreeRam(void) {
	
	return 1979; //return whatever
}

