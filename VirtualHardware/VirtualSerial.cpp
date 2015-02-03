#include "VirtualSerial.h"


void VirtualSerial::OnEvent(EEvent eEvent, EError eError)
{
	
	if (eEvent = EEvent::EEventRecv)
	{
		lock();


		//cout << available();
		DWORD dwBytesRead = 0;
		unsigned char c;

		// Read data from the COM-port
		do
		{
			Read(&c, 1, &dwBytesRead);
			if (dwBytesRead > 0)
			{
				cout << c;
				store_char(c, &rx_buffer);
			}

		} while (dwBytesRead > 0);

		SetEvent(ghReadEvent);

		unlock();


	}
}


DWORD WINAPI VirtualSerial::consoleThreadProc(LPVOID lpArg)
{
// Route the method to the actual object
	VirtualSerial* pThis = reinterpret_cast<VirtualSerial*>(lpArg);
	return pThis->consoleThreadProc();
}



DWORD VirtualSerial::consoleThreadProc(void)
{
	char c;


	do
	{
		c = getchar();
		lock();
		store_char(c, &rx_buffer);

		SetEvent(ghReadEvent);
		unlock();

	} while (1);



	return 0;
}


int VirtualSerial::available(void)
{
	unsigned int ret;
	lock();
	ret = (unsigned int)(SERIAL_BUFFER_SIZE + rx_buffer.head - rx_buffer.tail) % SERIAL_BUFFER_SIZE;
	unlock();

	return ret;


	//if (!IsOpen() || m_hFile == NULL) return(0);

	//DWORD dwErrorFlags;
	//COMSTAT ComStat;

	//ClearCommError(m_hFile, &dwErrorFlags, &ComStat);

	//return((int)ComStat.cbInQue);

}

void VirtualSerial::begin(unsigned int baudrate)
{
	rx_buffer.head = 0;
	rx_buffer.tail = 0;

	Open(AConfig::VirtualSerialPort, 0, 0, false);
	SetupReadTimeouts(CSerial::EReadTimeoutNonblocking);
	Setup(CSerial::EBaudrate(baudrate),
		CSerial::EDataBits(8),
		CSerial::EParity(NOPARITY),
		CSerial::EStopBits(ONESTOPBIT));

	ghMutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex

	if (ghMutex == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return;
	}

	ghReadEvent = CreateEvent(
		NULL,               // default security attributes
		TRUE,               // manual-reset event
		FALSE,              // initial state is nonsignaled
		TEXT("ghReadEvent")  // object name
		);
	if (ghReadEvent == NULL)
	{
		printf("CreateEvent failed (%d)\n", GetLastError());
		return;
	}

	consoleThread = CreateThread(0, 0, consoleThreadProc, LPVOID(this), 0, NULL);

	StartListener();
}

size_t VirtualSerial::write(uint8_t c)
{
	cout << c;
	return Write(&c, 1);
}

int VirtualSerial::read()
{
	lock();
	int ret;

	if (rx_buffer.head == rx_buffer.tail) {
		ret = -1;
	}
	else {
		unsigned char c = rx_buffer.buffer[rx_buffer.tail];
		rx_buffer.tail = (unsigned int)(rx_buffer.tail + 1) % SERIAL_BUFFER_SIZE;
		ret = c;
	}

	unlock();
	return ret;
}

void VirtualSerial::flush()
{

}

int VirtualSerial::peek()
{
	lock();
	int ret;
	if (rx_buffer.head == rx_buffer.tail) 
	{
		ret = -1;
	}
	else 
	{
		ret = rx_buffer.buffer[rx_buffer.tail];
	}
	unlock();
	return ret;
}


void VirtualSerial::lock()
{
	DWORD dwWaitResult;
	dwWaitResult = WaitForSingleObject(
		ghMutex,    // handle to mutex
		INFINITE);  // no time-out interval

	if (dwWaitResult != WAIT_OBJECT_0)
	{
		cout << "Mutex error - stop app";
		exit(1);
	}

}
void VirtualSerial::unlock()
{
	if (!ReleaseMutex(ghMutex))
	{
		cout << "error releasing Mutex - stop app";
		exit(2);
	}
}

int VirtualSerial::_timedRead(unsigned long timeout, bool peekData)
{

	int i = waitAvailable(timeout);

	if (i != 0)
		return peekData ? peek() : read();
	else
		return -1;

}

int VirtualSerial::waitAvailable(unsigned long timeout)
{
	unsigned int av;
	
	do
	{

		lock();
		av = (unsigned int)(SERIAL_BUFFER_SIZE + rx_buffer.head - rx_buffer.tail) % SERIAL_BUFFER_SIZE;

		if (av == 0)
		{
			cout << "\nwaiting...";

			ResetEvent(ghReadEvent);
			unlock();


			DWORD dwWaitResult;

			//printf("Thread %d waiting for data received event...\n", GetCurrentThreadId());

			dwWaitResult = WaitForSingleObject(
				ghReadEvent, // event handle
				timeout);    // indefinite wait

			switch (dwWaitResult)
			{
				// Event object was signaled
			case WAIT_OBJECT_0:
				//
				// TODO: Read from the shared buffer
				//
				//printf("Thread %d reading from buffer\n",
				//GetCurrentThreadId());
				break;

			case WAIT_TIMEOUT:
				return -1; break;

				// An error occurred
			default:
				printf("Wait error (%d)\n", GetLastError());
				return -1;
			}



		}
	
	}while (av==0);

	unlock();
	return av;


}