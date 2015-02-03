#include "ACHostLink.h"
#include <stdio.h>

CSerial link;
bool hostLinkEnabled = false;
uint8_t buffer[100];

uint16_t message;
uint16_t messageLength;

void ACHostLink::begin()
{
	hostLinkEnabled = true;

	link.Open(AConfig::HostlinkSerialPort, 0, 0, false);
	link.SetupReadTimeouts(CSerial::EReadTimeoutBlocking);
	link.Setup(CSerial::EBaudrate(115200),
		CSerial::EDataBits(8),
		CSerial::EParity(NOPARITY),
		CSerial::EStopBits(ONESTOPBIT));

}
void ACHostLink::readMessage()
{
	link.Read(&message, sizeof(message));
	link.Read(&messageLength, sizeof(messageLength));
	link.Read(buffer, messageLength);



	
}



void ACHostLink::sendMessage(uint16_t message, uint16_t length, char* data)
{
	link.Write(&message, sizeof(message));
	link.Write(&length, sizeof(length));
	link.Write(data, length);
}

void ACHostLink::pinMode(uint8_t pin, uint8_t mode)
{
	if (!hostLinkEnabled)
		printf("pinMode(pin = %d, mode=%d)\n", pin, mode);
	else
	{
		pinMode_m m;
		m.mode = mode;
		m.pin = pin;
		sendMessage(MSG_pinMode, sizeof(m), (char*)&m);
		readMessage();
	}

}

void ACHostLink::digitalWrite(uint8_t pin, uint8_t value)
{
	if (!hostLinkEnabled)
		printf("digitalWrite(pin=%d, value=%d)\n", pin, value);
	{
		digitalWrite_m m;
		m.pin = pin;
		m.value = value;
		sendMessage(MSG_digitalWrite, sizeof(m),(char*)&m);
		readMessage();
	}
}