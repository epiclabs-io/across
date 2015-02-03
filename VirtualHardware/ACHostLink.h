#pragma once

#include "AConfig.h"
#include "Serial.h"
#include <inttypes.h>
#include "Messages.h"

class ACHostLink
{

public:

	static void begin();

	static void pinMode(uint8_t pin, uint8_t mode);
	static void digitalWrite(uint8_t pin, uint8_t value);

private:
	static void sendMessage(uint16_t message, uint16_t length, char* data);
	static void readMessage();


};

