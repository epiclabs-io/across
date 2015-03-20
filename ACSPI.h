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

#ifndef _ACROSS_SPI_
#define _ACROSS_SPI_

// ACross cross-compiler SPI library
#include "ACross.h"



namespace ACross
{
	class SPI
	{
		public:
		static void init();
		static void send(uint8_t cspin, uint16_t length, uint8_t* data);
		static void send(uint8_t cspin, uint16_t length1, uint8_t* data1, uint16_t length2, uint8_t* data2);
		static void receive(uint8_t cspin, uint16_t length, uint8_t* data);
		static void sendReceive(uint8_t cspin, uint16_t sendLength, uint8_t* sendData, uint16_t receiveLength, uint8_t* receiveData);

	};
};







#endif