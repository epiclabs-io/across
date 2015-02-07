#ifndef _ACROSS_LINKLISTENER_
#define _ACROSS_LINKLISTENER_

#include "ACross.h"
#include "ACLinkProtocol.h"

class ACLinkListener
{
public:
	static ACLinkMessage buffer;


	static void begin(uint32_t baudrate);
	static bool serialRead(uint16_t length, uint8_t* data);
	static uint8_t listen();
	static void reply();
	static void reply(uint16_t dataLength);
	static void reply(ACLinkMessageHeader& header, uint8_t* data);

private:

	
	static void emptyBuffer();


	static uint8_t sequenceNumber;
	


};

#endif
