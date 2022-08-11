// Fill out your copyright notice in the Description page of Project Settings.


#include "FPVPawn.h"

#include "Windows/MinWindows.h"
#include <Dbt.h>
#include <hidsdi.h>
#include <hidpi.h>



// Sets default values
AFPVPawn::AFPVPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a window, as we need a window precedure to recieve raw input
	WNDCLASS wnd = { 0 };

	//wnd.lpszClassName = TEXT("Raw input");
	//wnd.lpfnWndProc = WindowProcedure;
	//wnd.hInstance = GetModuleHandle(0);
	//wnd.lpfnWndProc = WindowProcedure;

	//RegisterClass(&wnd);
	//HWND hwnd = CreateWindow(wnd.lpszClassName, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, wnd.hInstance, 0);


	// Register devices
	RAWINPUTDEVICE deviceList[2];
	deviceList[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	deviceList[0].usUsage = HID_USAGE_GENERIC_GAMEPAD;
	deviceList[0].dwFlags = RIDEV_INPUTSINK;
	//deviceList[0].hwndTarget = hwnd;
	deviceList[0].hwndTarget = nullptr;
	deviceList[1] = deviceList[0];
	deviceList[1].usUsage = HID_USAGE_GENERIC_JOYSTICK;

	UINT deviceCount = sizeof(deviceList) / sizeof(*deviceList);
	RegisterRawInputDevices(deviceList, deviceCount, sizeof(RAWINPUTDEVICE));

}


// Called when the game starts or when spawned
void AFPVPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPVPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPVPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFPVPawn::GetJoystick()
{
	UINT size = 0;
	LPARAM lParam = 0;
	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER));
	RAWINPUT* input = (RAWINPUT*)malloc(size);
	bool gotInput = GetRawInputData((HRAWINPUT)lParam, RID_INPUT, input, &size, sizeof(RAWINPUTHEADER)) > 0;

	if (gotInput)
	{
		GetRawInputDeviceInfo(input->header.hDevice, RIDI_PREPARSEDDATA, 0, &size);
		
		_HIDP_PREPARSED_DATA* data = (_HIDP_PREPARSED_DATA*)malloc(size);
		
		bool gotPreparsedData = GetRawInputDeviceInfo(input->header.hDevice, RIDI_PREPARSEDDATA, data, &size) > 0;
		
		if (gotPreparsedData)
		{
			HIDP_CAPS caps;
			
			HidP_GetCaps(data, &caps);
			
			//printf("Values: ");
			HIDP_VALUE_CAPS* valueCaps = (HIDP_VALUE_CAPS*)malloc(caps.NumberInputValueCaps * sizeof(HIDP_VALUE_CAPS));
			
			HidP_GetValueCaps(HidP_Input, valueCaps, &caps.NumberInputValueCaps, data);
			for (USHORT i = 0; i < caps.NumberInputValueCaps; ++i)
			{
				ULONG value;
				HidP_GetUsageValue(HidP_Input, valueCaps[i].UsagePage, 0, valueCaps[i].Range.UsageMin, &value, data, (PCHAR)input->data.hid.bRawData, input->data.hid.dwSizeHid);
				
				const FString Msg = FString::Printf(TEXT("%d:%5d "), i, value);
				GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Orange, Msg);
			}
			
			free(valueCaps);

			printf("Buttons: ");
			HIDP_BUTTON_CAPS* buttonCaps = (HIDP_BUTTON_CAPS*)malloc(caps.NumberInputButtonCaps * sizeof(HIDP_BUTTON_CAPS));
			HidP_GetButtonCaps(HidP_Input, buttonCaps, &caps.NumberInputButtonCaps, data);
			for (USHORT i = 0; i < caps.NumberInputButtonCaps; ++i)
			{
				ULONG usageCount = buttonCaps->Range.UsageMax - buttonCaps->Range.UsageMin + 1;
				USAGE* usages = (USAGE*)malloc(sizeof(USAGE) * usageCount);
				HidP_GetUsages(HidP_Input, buttonCaps[i].UsagePage, 0, usages, &usageCount, data, (PCHAR)input->data.hid.bRawData, input->data.hid.dwSizeHid);
				for (ULONG usageIndex = 0; usageIndex < usageCount; ++usageIndex) {
					//printf("%d ", usages[usageIndex]);

					const FString Msg = FString::Printf(TEXT("%d "), usages[usageIndex]);
					GEngine->AddOnScreenDebugMessage(2, 0.1f, FColor::Orange, Msg);
				}
				free(usages);
			}
			free(buttonCaps);
		
		
		}
		free(data);

		
	}
	free(input);
}

