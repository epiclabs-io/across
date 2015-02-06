#include "ACLinkListener.h"


ACLinkMessage ACLinkListener::buffer;

uint8_t ACLinkListener::sequenceNumber = 0xFF;

void ACLinkListener::begin(uint32_t baudrate)
{

	Serial.begin(baudrate);
	Serial.setTimeout(20000);

}


bool ACLinkListener::serialRead(uint16_t length, uint8_t* data)
{
	return length != Serial.readBytes((char*)data, length);
}

void ACLinkListener::emptyBuffer()
{
	uint32_t emptyTimer = millis() + ACLINK_EMPTY_TIMEOUT;

	while ((int32_t)(millis() - emptyTimer) < 0)
	{
		Serial.flush();
		if (Serial.available())
			Serial.read();
	}
}

uint8_t ACLinkListener::listen()
{
	ACLinkMessageHeader header;

	uint8_t attempts = 5;
	do
	{
		
		if (serialRead(sizeof(ACLinkMessageHeader), (uint8_t*)&header))
		{
			return 0xFF;
		}
		
		//if (rand() % 8 == 0)
		//{
		//	header.command ^= 0x01;
		//}
		
		if (0 == ACLink_checksum(0, sizeof(ACLinkMessageHeader), (uint8_t*)&header))
		{
			
			if (header.dataLength > ACLINK_BUFFER_SIZE)
			{
				return 0;
			}

			if (header.sequenceNumber == sequenceNumber)
			{
				emptyBuffer();
				
				reply();
				continue;
			}
			buffer.header = header;

			
			if (serialRead(header.dataLength, buffer.data))
			{
				return 0;
			}

			buffer.header.headerChecksum = 0;

			//if (rand() % 8 == 0)
			//{
			//	buffer.data[0] ^= 0x01;
			//}

			if (0 == ACLink_checksum(0, sizeof(ACLinkMessageHeader) + header.dataLength, (uint8_t*)&buffer))
			{
				sequenceNumber = header.sequenceNumber;
				return 1; //ok!
			}
			//cout << "data";
			
		}
		
		buffer.header.command = ACLINK_MSG_ERROR;
		//cout << " checksum error";
		reply(0);

		emptyBuffer();

	} while (attempts--);


	// too many errors.
	

	return 0;

}


void ACLinkListener::reply()
{
	uint16_t packetLength = buffer.header.dataLength + sizeof(ACLinkMessageHeader);
	buffer.header.dataChecksum = 0;
	buffer.header.headerChecksum = 0;
	buffer.header.dataChecksum = ACLink_checksum(0, packetLength, (uint8_t*)&buffer);
	buffer.header.headerChecksum = ACLink_checksum(0, sizeof(ACLinkMessageHeader), (uint8_t*)&buffer.header);


	Serial.write((uint8_t*)&buffer, packetLength);



}

void ACLinkListener::reply(uint16_t dataLength)
{
	buffer.header.dataLength = dataLength;
	reply();
}

