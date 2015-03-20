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
#include <ACSPI.h>
#include "EtherFlow.h"

uint32_t waitTimer;
uint8_t state = LOW;


static const uint8_t cspin = 10;


void setup()
{

	Serial.begin(115200);
	Serial.println("hello");

	waitTimer = millis();

	pinMode(4, OUTPUT);

	//EtherFlow::begin(10);

	Serial.println("howdy!");

}


void loop()
{
	//return;
	
	if (millis() > waitTimer + 1000)
	{
		digitalWrite(4, state = (state == LOW ? HIGH : LOW));

		Serial.print("A0="); Serial.println(analogRead(14));

		waitTimer = millis();
	}
	



}
