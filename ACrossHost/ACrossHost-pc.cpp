#if !defined(ARDUINO)



#include <stdio.h>
#include <tchar.h>

#include <ACross\ACross.h>

#include <ACross\VirtualHardware\AConfig.h>
#include <ACross\VirtualHardware\ACRPCCLient.h>


#include "ACrossHost.ino"

int _tmain(int argc, _TCHAR* argv[])
{
	AConfig::VirtualSerialPort = _T("\\\\.\\COM36");




	setup();

	while (1)
		loop();

	return 0;
}

#endif