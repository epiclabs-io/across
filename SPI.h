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