#include "ACross.h"

#if defined(ARDUINO) && ARDUINO >= 100

NOINLINE void SerialPrint_P(PGM_P str) 
{
	for (uint8_t c; (c = pgm_read_byte(str)); str++) 
		Serial.write(c);
}

NOINLINE void SerialPrintln_P(PGM_P str) 
{
	SerialPrint_P(str);
	Serial.println();
}
//------------------------------------------------------------------------------
/** Return the number of bytes currently free in RAM. */
int FreeRam(void) {
	extern int  __bss_end;
	extern int* __brkval;
	int free_memory;
	if (reinterpret_cast<int>(__brkval) == 0) {
		// if no heap use from end of bss section
		free_memory = reinterpret_cast<int>(&free_memory)
			- reinterpret_cast<int>(&__bss_end);
	}
	else {
		// use from top of stack to heap
		free_memory = reinterpret_cast<int>(&free_memory)
			- reinterpret_cast<int>(__brkval);
	}
	return free_memory;
}

#endif

void printFreeRam()
{
	PgmPrint("Free RAM:");
	dprint(FreeRam()); 
	
	Serial.println();

}

