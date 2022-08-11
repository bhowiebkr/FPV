// Copyright Epic Games, Inc. All Rights Reserved.

#include "RAWController.h"

#define LOCTEXT_NAMESPACE "FRAWControllerModule"

void FRAWControllerModule::StartupModule()
{
	// register our handler
	FWindowsApplication* Application = GetApplication();

	if (Application != nullptr)
	{
		Application->AddMessageHandler(Handler);
	}
}

void FRAWControllerModule::ShutdownModule()
{
	// unregister our handler
	FWindowsApplication* Application = GetApplication();

	if (Application != nullptr)
	{
		Application->RemoveMessageHandler(Handler);
	}
}

FWindowsApplication* FRAWControllerModule::GetApplication() const
{
	if (!FSlateApplication::IsInitialized())
	{
		GLog->Logf(TEXT("not initialized"));

		return nullptr;
	}

	GLog->Logf(TEXT("initialized"));
	return (FWindowsApplication*)FSlateApplication::Get().GetPlatformApplication().Get();
}



bool FControllerHandeler::ProcessMessage(HWND Hwnd, uint32 Message, WPARAM WParam, LPARAM LParam, int32& OutResult)
{
	// log out some details for the received message
	GLog->Logf(TEXT("RawController: hwnd = %i, msg = %s, wParam = %i, lParam = %i"), Hwnd, *GetMessageName(Message), WParam, LParam);

	// we did not handle this message, so make sure it gets passed on to other handlers
	return false;
}

FString FControllerHandeler::GetMessageName(uint32 Message)
{
	// do a binary search over known messages
	int32 Min = 0;
	int32 Max = sizeof(WindowsMessageNames) / sizeof(*WindowsMessageNames);

	for (; Min != Max;)
	{
		int32 Index = Min + (Max - Min) / 2;
		auto& MessageName = WindowsMessageNames[Index];

		if (MessageName.Message > Message)
		{
			Max = Index;
		}
		else if (MessageName.Message < Message)
		{
			Min = Index + 1;
		}
		else
		{
			return MessageName.Name;
		}
	}

	// unknown message
	return FString::Printf(TEXT("%i"), Message);
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRAWControllerModule, RAWController)