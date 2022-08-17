#pragma once

#include "Windows/WindowsApplication.h"


class FHIDHandeler : public IWindowsMessageHandler
{
public:
	virtual bool ProcessMessage(HWND Hwnd, uint32 Message, WPARAM WParam, LPARAM LParam, int32& OutResult) override;

	ULONG axis[8] = {0};
	bool button[16] = {false};

private:
	void ParseRawInput(RAWINPUT* input, UINT bufferSize);
	void PrintRawInput();
	bool RegisteredDevice = false;
};