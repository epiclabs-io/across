#ifndef _ACROSS_SPI_
#define _ACROSS_SPI_

// ACross cross-compiler SPI library

#include "ACross.h"



void initSPI();
void SPISend(uint8_t cspin, uint16_t length, uint8_t* data);
void SPIReceive(uint8_t cspin, uint16_t length, uint8_t* data);
void SPISendReceive(uint8_t cspin, uint16_t sendLength, uint8_t* sendData, uint16_t receiveLength, uint8_t* receiveData);










#endif