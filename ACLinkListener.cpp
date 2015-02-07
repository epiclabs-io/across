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

	uint8_t attempts = ACLINK_MAX_RETRIES;
	do
	{
		
		if (serialRead(sizeof(ACLinkMessageHeader), (uint8_t*)&header))
		{
			//timeout
			return 0xFF; // let the outer loop retry
		}
		
		//if (rand() % 8 == 0)
		//{
		//	header.command ^= 0x01;
		//}
		
		if (0 == ACLink_checksum(sizeof(ACLinkMessageHeader), (uint8_t*)&header))
		{
			
			if (header.dataLength > ACLINK_BUFFER_SIZE)
			{
				return 0; //irrecoverable
			}

			if (header.sequenceNumber == sequenceNumber)
			{
				//duplicate request
				emptyBuffer();
				
				reply(); // resend last reply
				continue;
			}

			//at this point we're sure this is not a duplicate request, 
			//so it is safe to overwrite our buffer.

			buffer.header = header;

		
			if (serialRead(header.dataLength, buffer.data))
			{
				//timeout
				return 0xFF; // let the outer loop reply
			}

			buffer.header.headerChecksum = 0;

			//if (rand() % 8 == 0)
			//{
			//	buffer.data[0] ^= 0x01;
			//}

			if (0 == ACLink_checksum(sizeof(ACLinkMessageHeader) + header.dataLength, (uint8_t*)&buffer))
			{
				sequenceNumber = header.sequenceNumber;
				return 1; //ok!
			}
			//cout << "data";
			
		}
		
		//we're here due to checksum error
		//create a new header for the error reply so as not
		//to overwrite the last buffer.

		ACLinkMessageHeader errorHeader;
		errorHeader.command = ACLINK_MSG_ERROR;
		errorHeader.dataLength = 0;
		reply(errorHeader, NULL);
		//cout << " checksum error";

		emptyBuffer();

	} while (attempts--);


	// too many errors.
	

	return 0;

}

void ACLinkListener::reply(ACLinkMessageHeader& header, uint8_t* data)
{
	uint16_t packetLength = header.dataLength + sizeof(ACLinkMessageHeader);
	header.dataChecksum = 0;
	header.headerChecksum = 0;
	header.dataChecksum = ACLink_checksum(sizeof(ACLinkMessageHeader), (uint8_t*)&header) ^ ACLink_checksum(header.dataLength,data);
	header.headerChecksum = ACLink_checksum(sizeof(ACLinkMessageHeader), (uint8_t*)&header);


	Serial.write((uint8_t*)&header, sizeof(ACLinkMessageHeader));
	Serial.write(data, header.dataLength);
}

void ACLinkListener::reply()
{
	reply(buffer.header, buffer.data);
}

void ACLinkListener::reply(uint16_t dataLength)
{
	buffer.header.dataLength = dataLength;
	reply();
}

