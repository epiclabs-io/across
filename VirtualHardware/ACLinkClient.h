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
