#include "ACHostLink.h"


CSerial link;
bool ACHostLink::hostLinkEnabled = false;
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

void ACHostLink::invoke(uint16_t message, uint8_t numParms, const uint16_t* parmLengths, const uint8_t* qualifiers, ...)
{
	va_list args;
	va_list rec;
	va_start(args, qualifiers);
	va_copy(rec, args);
	
	uint16_t totalLength=0;

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

				memcpy(buffer + totalLength, src, length);
			}
			else
			{
				memcpy(buffer + totalLength, args, length);
				args += ((length + sizeof(int) - 1) & ~(sizeof(int) - 1));

			}

			totalLength += length;
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

	link.Write(&message, sizeof(message));
	link.Write(&totalLength, sizeof(totalLength));
	link.Write(buffer, totalLength);
	link.Read(&message, sizeof(message));
	link.Read(&totalLength, sizeof(totalLength));
	link.Read(buffer, totalLength);

	uint16_t p = 0;
	for (int i = 0; i < numParms; i++)
	{
		if (qualifiers[i] == AH_OUT)
		{
			uint8_t* dst = va_arg(rec, uint8_t*);
			uint16_t length = parmLengths[i];
			if (length == 0)
				length = va_arg(rec, uint16_t);

			memcpy(dst, buffer + p, length);
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

