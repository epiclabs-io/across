
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
