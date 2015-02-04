#include "ACHostLink.h"
#include <stdio.h>

CSerial link;
bool hostLinkEnabled = false;
uint8_t buffer[100];

uint16_t message;
uint16_t messageLength;


template <class T>
T& readMessage()
{
	return *(T*)buffer;
}

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
void ACHostLink::receiveMessage()
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

void ACHostLink::invoke(uint16_t message, uint8_t numParms, uint16_t* parmLengths, uint8_t* qualifiers, ...)
{
	va_list args;
	va_list rec;
	va_start(args, parmLengths);
	va_copy(rec, args);
	
	uint16_t totalLength=0;

	for (int i = 0; i < numParms; i++)
	{
		if (qualifiers[i] & AH_IN)
		{
			if (qualifiers[i] & AH_REF)
				memcpy(buffer + totalLength, va_arg(args, uint8_t*), parmLengths[i]);
			else
				for (int j = 0; j < parmLengths[i]; j++)
					buffer[totalLength + j] = va_arg(args, uint8_t);

			totalLength += parmLengths[i];
		}
		else
			if (qualifiers[i] & AH_REF)
				va_arg(args, uint8_t*);
			else
				for (int j = 0; j < parmLengths[i]; j++)
					va_arg(args, uint8_t);



	}

	link.Write(&message, sizeof(message));
	link.Write(&totalLength, sizeof(totalLength));
	link.Write(buffer, totalLength);
	link.Read(&message, sizeof(message));
	link.Read(&totalLength, sizeof(totalLength));
	link.Read(buffer, totalLength);

	uint16_t p = 0;
	for (int i = 0; i < numParms; i++)
	{
		if (qualifiers[i] & AH_OUT)
		{
			memcpy(va_arg(args, uint8_t*),buffer+p, parmLengths[i]);
			p += parmLengths[i];
		}
		else
			if (qualifiers[i] & AH_REF)
				va_arg(args, uint8_t*);
			else
				for (int j = 0; j < parmLengths[i]; j++)
					va_arg(args, uint8_t);
	}

	va_end(args);
	va_end(rec);
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
		receiveMessage();

		uint16_t lengths[2] = { sizeof(pin), sizeof(mode) };
		uint8_t qualifiers[2] = { AH_IN, AH_IN };

		invoke(MSG_pinMode, 2, lengths, qualifiers, pin, mode);


	}

}

void ACHostLink::digitalWrite(uint8_t pin, uint8_t value)
{
	if (!hostLinkEnabled)
		printf("digitalWrite(pin=%d, value=%d)\n", pin, value);
	else
	{
		digitalWrite_m m;
		m.pin = pin;
		m.value = value;
		sendMessage(MSG_digitalWrite, sizeof(m),(char*)&m);
		receiveMessage();
	}
}


int16_t ACHostLink::digitalRead(uint8_t pin)
{
	if (!hostLinkEnabled)
		printf("digitalRead(pin=%d)\n", pin);
	else
	{
		digitalRead_m m;
		m.pin = pin;
		sendMessage(MSG_digitalRead, sizeof(m), (char*)&m);
		receiveMessage();
		digitalRead_r r = readMessage<digitalRead_r>();
		return r.value;

	}

}
void ACHostLink::analogWrite(uint8_t pin, int16_t value)
{

}
int16_t ACHostLink::analogRead(uint8_t pin)
{

}