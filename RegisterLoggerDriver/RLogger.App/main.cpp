#include <Windows.h>
#include <iostream>

#include "../RLogger.Lib/RLoggerCommon.h"

int main(int argc, char* argv[]) 
{

	HANDLE hDevice = CreateFile(
		"\\\\.\\RLogger", 
		FILE_SHARE_WRITE, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		0,
		NULL
	);

	if (hDevice == INVALID_HANDLE_VALUE) 
	{
		std::cout << "[ERROR]: driver is not running!\n";
		return 1;
	}

	if (argc == 3 && strcmp(argv[1], "setpid") == 0) 
	{
		DWORD returned;
		ULONG pid = atoi(argv[2]);

		if (DeviceIoControl(hDevice, IOCTL_RLOGGER_SET_TARGET_PID, &pid, sizeof(pid), NULL, 0, &returned, NULL))
		{
			std::cout << "[INFO]: Success\n";
			return 0;
		}
		else 
		{
			std::cout << "[ERROR]: An error has occurred\n";
			return 1;
		}
	}

	if ((argc == 2) && (strcmp(argv[1], "stop") == 0)) 
	{
		DWORD returned;

		if (DeviceIoControl(hDevice, IOCTL_RLOGGER_STOP_LOGGING, NULL, 0, NULL, 0, &returned, NULL)) 
		{
			std::cout << "[INFO]: Success\n";
			return 0;
		}
		else 
		{
			std::cout << "[ERROR]: An error has occurred\n";
			return 1;
		}
	}

	std::cout << "[ERROR]: use pattern:\n" << "./APPNAME setpid PID\n" << "./APPNAME stop\n";
	return 1;
}