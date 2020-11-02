#pragma once
#include "CommonIncludes.hpp"
#include <devguid.h>
#include <SetupAPI.h>

#pragma comment (lib, "Setupapi.lib")

class arduino
{
private:

	HANDLE arduino_handle = NULL;

public:

	bool Found_Arduino = false;

	arduino();

	arduino(LPCSTR device_name);

	~arduino();

	bool attach(LPCSTR device_name);

	bool detach();

	bool scan_devices(LPCSTR device_name, LPSTR lp_out);

	bool send_data(const char* buffer, DWORD buffer_size);
};