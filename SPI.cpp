
#include "SPI.h"


#ifdef ACROSS_ARDUINO
namespace ACross
{
	void SPI::init()
	{
		pinMode(SS, OUTPUT);
		digitalWrite(SS, HIGH);
		pinMode(MOSI, OUTPUT);
		pinMode(SCK, OUTPUT);
		pinMode(MISO, INPUT);

		digitalWrite(MOSI, HIGH);
		digitalWrite(MOSI, LOW);
		digitalWrite(SCK, LOW);

		SPCR = bit(SPE) | bit(MSTR); // 8 MHz @ 16
		bitSet(SPSR, SPI2X);

	}

	static void xferSPI(byte data) 
	{
		SPDR = data;
		while (!(SPSR&(1 << SPIF)))
			;
	}

	inline static void beginSession(uint8_t cspin)
	{
		cli();
		digitalWrite(cspin, LOW);
	}

	inline static void endSession(uint8_t cspin)
	{
		digitalWrite(cspin, HIGH);
		sei();
	}

	static void sendBuffer(uint16_t length, uint8_t* data)
	{
		while (length--)
			xferSPI(*data++);
	}

	static void receiveBuffer(uint16_t length, uint8_t* data )
	{
		while (length--)
		{
			xferSPI(0x00);
			*data++ = SPDR;
		}
	}


	void SPI::send(uint8_t cspin, uint16_t length, uint8_t* data)
	{
		send(cspin,length,data,0,NULL);
	}

	void SPI::send(uint8_t cspin, uint16_t length1, uint8_t* data1, uint16_t length2, uint8_t* data2)
	{
		beginSession(cspin);

		sendBuffer(length1,data1);
		sendBuffer(length2,data2);

		endSession(cspin);
	}

	void SPI::receive(uint8_t cspin, uint16_t length, uint8_t* data)
	{
		sendReceive(cspin,0,NULL,length,data);
	}
	void SPI::sendReceive(uint8_t cspin, uint16_t sendLength, uint8_t* sendData, uint16_t receiveLength, uint8_t* receiveData)
	{
		beginSession(cspin);

		sendBuffer(sendLength,sendData);
		receiveBuffer(receiveLength, receiveData);

		endSession(cspin);
	}
};
#else

#include "VirtualHardware/ACRPCCLient.h"

namespace ACross
{
	void SPI::init()
	{
		if (!ACRPCCLient::hostLinkEnabled)
			printf("ACross_initSPI\n");
		else
		{

			invoke_RPC_NO_PARMS(ACross_initSPI);
		}
	}

	void SPI::send(uint8_t cspin, uint16_t length, uint8_t* data)
	{
		sendReceive(cspin, length, data, 0, NULL);
	}

	void SPI::send(uint8_t cspin, uint16_t length1, uint8_t* data1, uint16_t length2, uint8_t* data2)
	{
		uint8_t* buf = new uint8_t[length1 + length2];
		memcpy(buf, data1, length1);
		memcpy(buf + length1, data2, length2);
		send(cspin, length1 + length2, buf);
	}


	void SPI::receive(uint8_t cspin, uint16_t length, uint8_t* data)
	{
		sendReceive(cspin, 0, NULL, length, data);
	}

	void SPI::sendReceive(uint8_t cspin, uint16_t sendLength, uint8_t* sendData, uint16_t receiveLength, uint8_t* receiveData)
	{
		if (!ACRPCCLient::hostLinkEnabled)
			printf("ACross_SPISendReceive(cspin=%d, sendLength=%d, sendData=%p, receiveLength=%d, receiveData=%p)\n",
			cspin, sendLength, sendData, receiveLength, receiveData);
		else
		{
			invoke_RPC(ACRoss_SPISendReceive, cspin, sendLength, sendData, sendLength, receiveLength, receiveData, receiveLength);
		}
	}


}
#endif