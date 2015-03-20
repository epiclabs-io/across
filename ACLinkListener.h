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
