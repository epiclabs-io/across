#pragma once

#include "AConfig.h"
#include "Serial.h"
#include <inttypes.h>
#include "Messages.h"






class ACRPCCLient
{

public:
	static bool hostLinkEnabled;
	static void begin();

	static void invoke(uint16_t command, uint8_t numParms, const uint16_t* parmLengths, const uint8_t* qualifiers ...);



private:


};

