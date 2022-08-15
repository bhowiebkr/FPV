#include "HIDInputHandeler.h"

#include "Windows/MinWindows.h"

#include <Dbt.h>
#include <hidsdi.h>
#include <hidpi.h>


bool FHIDHandeler::ProcessMessage(HWND Hwnd, uint32 Message, WPARAM WParam, LPARAM LParam, int32& OutResult)
{
	if (RegisteredDevice == false) {
		GLog->Logf(TEXT("Register for joystick devices"));
		// Register for joystick devices
		RAWINPUTDEVICE rid[2] = {};

		rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		rid[0].usUsage = HID_USAGE_GENERIC_GAMEPAD;	// Gamepad - e.g. XBox 360 or XBox One controllers
		rid[0].dwFlags = RIDEV_INPUTSINK; // Recieve messages when in background.
		rid[0].hwndTarget = Hwnd;


		rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
		rid[1].usUsage = HID_USAGE_GENERIC_JOYSTICK; // Joystick, RC Controller, etc.	
		rid[1].dwFlags = RIDEV_INPUTSINK; // Recieve messages when in background.
		rid[1].hwndTarget = Hwnd;

		if (RegisterRawInputDevices(rid, 2, sizeof(RAWINPUTDEVICE)))
		{
			GLog->Logf(TEXT("Register for joystick devices"));
			RegisteredDevice = true;
		}
		else {
			GLog->Logf(TEXT("Register for joystick devices FAILED"));
			RegisteredDevice = false;
		}
		return false;
	}


	switch (Message)
	{
	case WM_INPUT:
	{
		// Get the buffer size
		UINT bufferSize = 0;
		GetRawInputData((HRAWINPUT)LParam, RID_INPUT, NULL, &bufferSize, sizeof(RAWINPUTHEADER));

		// Get the input size
		RAWINPUT* input = (RAWINPUT*)malloc(bufferSize);
		bool gotInput = GetRawInputData((HRAWINPUT)LParam, RID_INPUT, input, &bufferSize, sizeof(RAWINPUTHEADER)) > 0;

		// If we got input, we parse it
		if (gotInput) {
			//GLog->Logf(TEXT("Got Input"));
			ParseRawInput(input, bufferSize);
			free(input);
		}
	}

	}
	return false;
}



void FHIDHandeler::ParseRawInput(RAWINPUT* input, UINT bufferSize)
{
	// Get pre parsed data
	GetRawInputDeviceInfo(input->header.hDevice, RIDI_PREPARSEDDATA, 0, &bufferSize);
	_HIDP_PREPARSED_DATA* data = (_HIDP_PREPARSED_DATA*)malloc(bufferSize);
	bool gotPreparsedData = GetRawInputDeviceInfo(input->header.hDevice, RIDI_PREPARSEDDATA, data, &bufferSize) > 0;

	if (gotPreparsedData)
	{
		HIDP_CAPS caps;
		HidP_GetCaps(data, &caps);

		//GLog->Logf(TEXT("Values: "));
		HIDP_VALUE_CAPS* valueCaps = (HIDP_VALUE_CAPS*)malloc(caps.NumberInputValueCaps * sizeof(HIDP_VALUE_CAPS));
		HidP_GetValueCaps(HidP_Input, valueCaps, &caps.NumberInputValueCaps, data);
		for (USHORT i = 0; i < caps.NumberInputValueCaps; ++i)
		{
			ULONG value;
			HidP_GetUsageValue(HidP_Input, valueCaps[i].UsagePage, 0, valueCaps[i].Range.UsageMin, &value, data, (PCHAR)input->data.hid.bRawData, input->data.hid.dwSizeHid);
			//GLog->Logf(TEXT("%d:%5d "), i, value);
			FString Msg = FString::Printf(TEXT("Axis: %d:%5d "), i, value);
			GEngine->AddOnScreenDebugMessage(i, 0.1f, FColor::Red, Msg);
		}
		free(valueCaps);

		//GLog->Logf(TEXT("Buttons: "));
		HIDP_BUTTON_CAPS* buttonCaps = (HIDP_BUTTON_CAPS*)malloc(caps.NumberInputButtonCaps * sizeof(HIDP_BUTTON_CAPS));
		HidP_GetButtonCaps(HidP_Input, buttonCaps, &caps.NumberInputButtonCaps, data);
		for (USHORT i = 0; i < caps.NumberInputButtonCaps; ++i)
		{
			ULONG usageCount = buttonCaps->Range.UsageMax - buttonCaps->Range.UsageMin + 1;
			USAGE* usages = (USAGE*)malloc(sizeof(USAGE) * usageCount);
			HidP_GetUsages(HidP_Input, buttonCaps[i].UsagePage, 0, usages, &usageCount, data, (PCHAR)input->data.hid.bRawData, input->data.hid.dwSizeHid);
			for (ULONG usageIndex = 0; usageIndex < usageCount; ++usageIndex) {
				//printf("%d ", usages[usageIndex]);
				//GLog->Logf(TEXT("%d"), usages[usageIndex]);
				FString Msg = FString::Printf(TEXT("Button: %d "), usages[usageIndex]);
				GEngine->AddOnScreenDebugMessage(8 + i, 0.1f, FColor::Blue, Msg);
			}
			free(usages);
		}
		free(buttonCaps);
	}
	free(data);
}
