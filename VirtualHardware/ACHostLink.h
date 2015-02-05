#pragma once

#include "AConfig.h"
#include "Serial.h"
#include <inttypes.h>
#include "Messages.h"






class ACHostLink
{

public:
	static bool hostLinkEnabled;
	static void begin();

	static void invoke(uint16_t message, uint8_t numParms, const uint16_t* parmLengths, const uint8_t* qualifiers ...);



private:
	static void sendMessage(uint16_t message, uint16_t length, char* data);
	static void receiveMessage();



};

