#include "ACprintf.h"
namespace ACross
{
	int printf_out_serial( char c, FILE * )
	{
		Serial.write( c );
		return c;
	}
	void printf_serial_init(void)
	{
	  fdevopen( &printf_out_serial, NULL );
	}
};