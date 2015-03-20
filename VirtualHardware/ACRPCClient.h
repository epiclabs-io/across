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

#pragma once

#include "AConfig.h"
#include "Serial.h"
#include <inttypes.h>
#include "Messages.h"






class ACRPCCLient
{

public:
	static bool hostLinkEnabled;
	static void begin();

	static void invoke(uint16_t command, uint8_t numParms, const uint16_t* parmLengths, const uint8_t* qualifiers ...);



private:


};

