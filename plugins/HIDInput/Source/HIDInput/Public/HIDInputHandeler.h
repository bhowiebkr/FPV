#pragma once

#include "Windows/WindowsApplication.h"


class FHIDHandeler : public IWindowsMessageHandler
{
public:
	virtual bool ProcessMessage(HWND Hwnd, uint32 Message, WPARAM WParam, LPARAM LParam, int32& OutResult) override;

private:
	void ParseRawInput(RAWINPUT* input, UINT bufferSize);
	bool RegisteredDevice = false;
};