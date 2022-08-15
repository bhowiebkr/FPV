#include "HIDInput.h"

#include "Templates/SharedPointer.h"
#include "HIDInputDevice.h"
#include "IInputDeviceModule.h"
#include "IInputDevice.h"

#define LOCTEXT_NAMESPACE "FHIDInputPlugin"


// This function is called by *Application.cpp after startup to instantiate the modules InputDevice
inline TSharedPtr<class IInputDevice> FHIDInputPlugin::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	return TSharedPtr<class IInputDevice>();
}

void FHIDInputPlugin::StartupModule()
{
	// register our handler
	FWindowsApplication* Application = GetApplication();

	if (Application != nullptr)
	{

		// Add the Handeler
		Application->AddMessageHandler(Handler);
	}
}

FWindowsApplication* FHIDInputPlugin::GetApplication() const
{
	if (!FSlateApplication::IsInitialized())
	{
		GLog->Logf(TEXT("not initialized"));

		return nullptr;
	}

	GLog->Logf(TEXT("initialized"));
	return (FWindowsApplication*)FSlateApplication::Get().GetPlatformApplication().Get();
}

IMPLEMENT_MODULE(FHIDInputPlugin, RAWController)




#undef LOCTEXT_NAMESPACE