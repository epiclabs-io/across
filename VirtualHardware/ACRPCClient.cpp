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


#include "ACRPCCLient.h"
#include "ACLinkClient.h"


bool ACRPCCLient::hostLinkEnabled = false;


void ACRPCCLient::begin()
{
	hostLinkEnabled = true;

	ACLinkClient::begin((uint32_t)115200,AConfig::HostlinkSerialPort);

}





void ACRPCCLient::invoke(uint16_t command, uint8_t numParms, const uint16_t* parmLengths, const uint8_t* qualifiers, ...)
{
	va_list args;
	va_list rec;
	va_start(args, qualifiers);
	va_copy(rec, args);
	
	uint16_t dataLength=0;

	for (int i = 0; i < numParms; i++)
	{
		if (qualifiers[i] & AH_IN)
		{
			uint16_t length = parmLengths[i];

			if (qualifiers[i] & AH_REF)
			{
				uint8_t* src = va_arg(args, uint8_t*);
				
				if (length == 0)
					length = va_arg(args, uint16_t);

				memcpy(ACLinkClient::txBuffer.data + dataLength, src, length);
			}
			else
			{
				memcpy(ACLinkClient::txBuffer.data + dataLength, args, length);
				args += ((length + sizeof(int) - 1) & ~(sizeof(int) - 1));

			}

			dataLength += length;
		}
		else
			if (qualifiers[i] & AH_REF)
			{
				va_arg(args, uint8_t*);
				if (parmLengths[i] == 0)
					va_arg(args, uint16_t);
			}
			else
				for (int j = 0; j < parmLengths[i]; j++)
					va_arg(args, uint8_t);



	}


	ACLinkClient::request(command,dataLength);


	uint16_t p = 0;
	for (int i = 0; i < numParms; i++)
	{
		if (qualifiers[i] == AH_OUT)
		{
			uint8_t* dst = va_arg(rec, uint8_t*);
			uint16_t length = parmLengths[i];
			if (length == 0)
				length = va_arg(rec, uint16_t);

			memcpy(dst, ACLinkClient::rxBuffer.data + p, length);
			p += length;
		}
		else
			if (qualifiers[i] & AH_REF)
			{
			va_arg(rec, uint8_t*);
				if (parmLengths[i] == 0)
					va_arg(rec, uint16_t);
			}
			else
			{
				rec += ((parmLengths[i] + sizeof(int) - 1) & ~(sizeof(int) - 1));

			}
	}

	va_end(args);
	va_end(rec);
}

