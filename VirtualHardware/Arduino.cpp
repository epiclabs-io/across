#include "Arduino.h"
#include "ACHostLink.h"

#include <stdio.h>
VirtualSerial Serial;



void pinMode(uint8_t pin, uint8_t mode)
{
	if (!ACHostLink::hostLinkEnabled)
		printf("pinMode(pin = %d, mode=%d)\n", pin, mode);
	else
	{
		invoke_RPC(pinMode, pin, mode);
	}
}

void digitalWrite(uint8_t pin, uint8_t value)
{
	if (!ACHostLink::hostLinkEnabled)
		printf("digitalWrite(pin=%d, value=%d)\n", pin, value);
	else
	{
		invoke_RPC(digitalWrite, pin, value);
	}
}

int16_t digitalRead(uint8_t pin)
{
	if (!ACHostLink::hostLinkEnabled)
		printf("digitalRead(pin=%d)\n", pin);
	else
	{

		int16_t ret;
		invoke_RPC(digitalRead, pin, &ret);
		return ret;

	}
}

int16_t analogRead(uint8_t pin)
{
	if (!ACHostLink::hostLinkEnabled)
		printf("analogRead(pin=%d)\n", pin);
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
	if (!ACHostLink::hostLinkEnabled)
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

void ACross_writeReg(uint16_t regAddress, uint8_t value)
{
	if (!ACHostLink::hostLinkEnabled)
		printf("ACross_writeReg(regAddress=%d, value=%d)\n", regAddress, value);
	else
	{
		invoke_RPC(ACross_writeReg8, regAddress, value);
	}


}

uint8_t ACross_readReg(uint16_t regAddress)
{
	if (!ACHostLink::hostLinkEnabled)
		printf("ACross_readReg(regAddress=%d)\n", regAddress);
	else
	{
		uint8_t ret;
		invoke_RPC(ACross_readReg8, regAddress, &ret);

		return ret;
	}
}
