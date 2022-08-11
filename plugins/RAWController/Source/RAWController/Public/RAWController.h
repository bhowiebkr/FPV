// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "CoreTypes.h"
#include "Containers/UnrealString.h"
#include "Windows/WindowsApplication.h"


class FControllerHandeler : public IWindowsMessageHandler
{
public:
	virtual bool ProcessMessage(HWND Hwnd, uint32 Message, WPARAM WParam, LPARAM LParam, int32& OutResult) override;
	FString GetMessageName(uint32 Message);

	void ParseRawInput(RAWINPUT* input, UINT bufferSize);

	bool RegisteredDevice = false;
};



class FRAWControllerModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	FWindowsApplication* GetApplication() const;

private:
	FControllerHandeler Handler;

};
