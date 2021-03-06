// ACross cross-compile development toolkit
// Author: Javier Peletier <jm@friendev.com>
// Summary: ACross allows you to build your Arduino projects using Visual Studio.
// Your Arduino code is cross - compiled and runs in your PC, which enables
// step - by - step debugging
//
// Copyright (c) 2015 All Rights Reserved, http://friendev.com
//
// This source is subject to the GPLv2 license.
// Please see the License.txt file for more information.
// All other rights reserved.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "ACLinkClient.h"


CSerial ACLinkClient::link;

ACLinkMessage ACLinkClient::txBuffer;
ACLinkMessage ACLinkClient::rxBuffer;

uint8_t ACLinkClient::localSequenceNumber = 0;
uint8_t ACLinkClient::remoteSequenceNumber = 0;

void ACLinkClient::begin(uint32_t baudrate, LPCTSTR port)
{

	link.Open(port, 0, 0, true);
	link.SetupReadTimeouts(CSerial::EReadTimeoutBlocking);
	link.Setup(CSerial::EBaudrate(baudrate),
		CSerial::EDataBits(8),
		CSerial::EParity(NOPARITY),
		CSerial::EStopBits(ONESTOPBIT));

}



bool ACLinkClient::serialRead(uint16_t length, uint8_t* data)
{

	return ERROR_SUCCESS != link.Read(data, length,0,0,ACLINK_TIMEOUT);
		

}
void ACLinkClient::serialWrite(uint16_t length, uint8_t* data)
{
	link.Write(data, length);

}

void ACLinkClient::emptyBuffer()
{
	uint32_t emptyTimer = millis() + ACLINK_EMPTY_TIMEOUT;

	while ((int32_t)(millis() - emptyTimer) < 0)
	{
		link.Purge();
	}
}

void ACLinkClient::request(uint16_t command, uint16_t dataLength)
{
	uint16_t packetLength = sizeof(ACLinkMessageHeader) + dataLength;
	
	txBuffer.header.command = command;
	txBuffer.header.dataLength = dataLength;
	txBuffer.header.sequenceNumber = localSequenceNumber++;
	txBuffer.header.dataChecksum = 0;
	txBuffer.header.headerChecksum = 0;

	txBuffer.header.dataChecksum = ACLink_checksum(packetLength, (uint8_t*)&txBuffer);
	txBuffer.header.headerChecksum = ACLink_checksum(sizeof(ACLinkMessageHeader), (uint8_t*)&txBuffer.header);

	uint8_t attempts = ACLINK_MAX_RETRIES;
	
	do
	{
		serialWrite(packetLength, (uint8_t*)&txBuffer);

		//char b;
		//while (1)
		//{
		//	serialRead(1, (uint8_t*)&b);
		//	cout << b;
		//}

		if (!serialRead(sizeof(ACLinkMessageHeader), (uint8_t*)&rxBuffer.header))
		{
			if (0 == ACLink_checksum(sizeof(ACLinkMessageHeader), (uint8_t*)&rxBuffer.header)
				&& rxBuffer.header.command == ACLINK_MSG_OK)
			{
				if (rxBuffer.header.dataLength > ACLINK_BUFFER_SIZE)
				{
					ACross::halt(9); //irrecoverable
				}
				else
				{
					if (!serialRead(rxBuffer.header.dataLength, rxBuffer.data))
					{
						rxBuffer.header.headerChecksum = 0;
						if (0 == ACLink_checksum(sizeof(ACLinkMessageHeader) + rxBuffer.header.dataLength, (uint8_t*)&rxBuffer))
							return; // ok!
					}
				}
			}
		}
		
		//timeout or NACK

		cout << "resend!";

		emptyBuffer();


	} while (attempts--);


	// link timed out or non-recoverable error.
	ACross::halt(7); // error codes to be defined.

}
