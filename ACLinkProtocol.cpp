#include "ACLinkProtocol.h"

uint8_t ACLink_checksum(uint16_t length, uint8_t* data)
{
	uint8_t chk = 0;
	while (length--)
		chk ^= *data++;

	return chk;
}