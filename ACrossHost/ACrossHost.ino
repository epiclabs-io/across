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


#include <ACross.h>
#include <ACLinkListener.h>
#include <VirtualHardware/Messages.h>
#include <ACSPI.h>







template <class T>
T& readMessage()
{
	return *(T*)ACLinkListener::buffer.data;
}

void sendMessage(uint16_t command, uint16_t length)
{
	ACLinkListener::buffer.header.command = command;
	ACLinkListener::reply(length);
}

void sendMessage(uint16_t length)
{
	sendMessage(ACLINK_MSG_OK, length);
}

void okMessage()
{
	sendMessage(0);
}


void RPC_pinMode(rpc_msg& msg)
{
	pinMode(msg.b0, msg.b1);
	okMessage();
}

void RPC_digitalWrite(rpc_msg& msg)
{
	digitalWrite(msg.b0, msg.b1);
	okMessage();
}
void RPC_analogWrite(rpc_msg& msg)
{
	analogWrite(msg.b0, msg.getValue<int16_t>(1));
}

void RPC_digitalRead(rpc_msg& msg)
{
	int16_t ret = digitalRead(msg.b0);
	msg.i0 = ret;
	sendMessage(2);
	
}

void RPC_analogRead(rpc_msg& msg)
{
	int16_t ret = analogRead(msg.b0);
	msg.i0 = ret;
	sendMessage(2);
}



void RPC_ACross_initSPI(rpc_msg& msg)
{
	ACross::SPI::init();
	okMessage();
}


void RPC_ACRoss_SPISendReceive(rpc_msg& msg)
{
	
	uint8_t cspin = msg.b0;
	uint16_t sendLength = msg.getValue<int16_t>(1);
	uint8_t* sendData = ((uint8_t*)ACLinkListener::buffer.data + 3); 
	uint16_t receiveLength = msg.getValue<int16_t>(1+2+sendLength);
	uint8_t* receiveData = ((uint8_t*)ACLinkListener::buffer.data);



	ACross::SPI::sendReceive(cspin, sendLength, sendData, receiveLength, receiveData);
	sendMessage(receiveLength);
}

void processMessage()
{
	
	

	if (ACLinkListener::buffer.header.command < ACLINK_MSG_RESERVED)
	{
		FunctionHandler f = (FunctionHandler)NATIVE_FUNCTION_PTR(functionHandlers[ACLinkListener::buffer.header.command]);
		
		f((*(rpc_msg*)ACLinkListener::buffer.data));
	}
	else
	{
		//ignore message

	}
}


void setup()
{
	ACLinkListener::begin(115200);
}

void loop()
{

	switch (ACLinkListener::listen())
	{
		case 0:	ACross::halt(11); break;
		case 1:processMessage(); break;
		case 0xFF:break;
		default:break;
	}


	/*


	if (Serial.available() >= sizeof(message)+sizeof(messageSize))
	{
		Serial.readBytes((char*)&message, sizeof(message));
		Serial.readBytes((char*)&messageSize, sizeof(messageSize));

		uint16_t dataRead = 0;
		while (dataRead < messageSize)
		{
			uint16_t c;
			if (c = Serial.available())
			{
				Serial.readBytes(buffer + dataRead, c);
				dataRead += c;
			}
		}

		processMessage();
	}
  

  */

}
