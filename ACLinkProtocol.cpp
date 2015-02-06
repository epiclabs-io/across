#include "ACLinkProtocol.h"

uint8_t ACLink_checksum(uint8_t chk, uint16_t length, uint8_t* data)
{
	while (length--)
		chk ^= *data++;

	return chk;
}