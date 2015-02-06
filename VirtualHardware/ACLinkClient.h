#ifndef _ACROSS_LINK_
#define _ACROSS_LINK_

#include "../ACross.h"
#include "../ACLinkProtocol.h"
#include "Serial.h"



class ACLinkClient
{
public:
	static ACLinkMessage txBuffer;
	static ACLinkMessage rxBuffer;


	static void begin(uint32_t baudrate, LPCTSTR port);


	static void request(uint16_t command, uint16_t dataLength);

private:

	static bool serialRead(uint16_t length, uint8_t* data);
	static void serialWrite(uint16_t length, uint8_t* data);
	
	static void emptyBuffer();


	static uint8_t localSequenceNumber;
	static uint8_t remoteSequenceNumber;


private:
	static CSerial link;


};

#endif
