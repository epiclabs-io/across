#pragma once

#include "AConfig.h"
#include "Serial.h"
#include <inttypes.h>
#include "Messages.h"


static const uint8_t AH_IN = 0x01;
static const uint8_t AH_REF = 0x4;
static const uint8_t AH_OUT = 0x02 | AH_REF;
static const uint8_t AH_INOUT = AH_OUT | AH_IN;



class ACHostLink
{

public:

	static void begin();

	static void pinMode(uint8_t pin, uint8_t mode);
	static void digitalWrite(uint8_t pin, uint8_t value);
	static int16_t digitalRead(uint8_t pin);
	static void analogWrite(uint8_t pin, int16_t value);
	static int16_t analogRead(uint8_t pin);



private:
	static void sendMessage(uint16_t message, uint16_t length, char* data);
	static void receiveMessage();

	static void invoke(uint16_t message, uint8_t numParms, uint16_t* parmLengths, uint8_t* qualifiers ...);


};

