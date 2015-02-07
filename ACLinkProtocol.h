#ifndef _ACROSS_ACLINKPROTOCOL_
#define _ACROSS_ACLINKPROTOCOL_
#include "ACross.h"

static const uint16_t ACLINK_BUFFER_SIZE = 128;

#pragma pack(push,1)
struct ACLinkMessageHeader
{
	uint16_t command;
	uint16_t dataLength;
	uint8_t sequenceNumber;
	uint8_t headerChecksum;
	uint8_t dataChecksum;
};
struct ACLinkMessage
{
	ACLinkMessageHeader header;
	uint8_t data[ACLINK_BUFFER_SIZE];
};
#pragma pack(pop)

static const uint16_t ACLINK_MSG_RESERVED = 0xFF00;
static const uint16_t ACLINK_MSG_ERROR = ACLINK_MSG_RESERVED;
static const uint16_t ACLINK_MSG_OK = ACLINK_MSG_RESERVED + 1;
static const uint16_t ACLINK_MSG_RESET = 0xFFFF;

static const uint16_t ACLINK_EMPTY_TIMEOUT = 50; //ms
static const uint16_t ACLINK_TIMEOUT = 4000; //ms
static const uint8_t ACLINK_MAX_RETRIES = 4;


uint8_t ACLink_checksum(uint16_t length, uint8_t* data);

#endif