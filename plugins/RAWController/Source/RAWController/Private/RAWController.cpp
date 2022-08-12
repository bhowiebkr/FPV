#include "RAWController.h"
#include "IInputDeviceModule.h"
#include "IInputDevice.h"




#define LOCTEXT_NAMESPACE "FRAWControllerPlugin"


TSharedPtr<class IInputDevice> FRAWControllerPlugin::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	return TSharedPtr<class IInputDevice>();
}

void FRAWControllerPlugin::StartupModule()
{
	// register our handler
	FWindowsApplication* Application = GetApplication();

	if (Application != nullptr)
	{

		// Add the Handeler
		Application->AddMessageHandler(Handler);
	}
}

void FRAWControllerPlugin::ShutdownModule()
{
	// unregister our handler
	FWindowsApplication* Application = GetApplication();

	if (Application != nullptr)
	{
		Application->RemoveMessageHandler(Handler);
	}
}

FWindowsApplication* FRAWControllerPlugin::GetApplication() const
{
	if (!FSlateApplication::IsInitialized())
	{
		GLog->Logf(TEXT("not initialized"));

		return nullptr;
	}

	GLog->Logf(TEXT("initialized"));
	return (FWindowsApplication*)FSlateApplication::Get().GetPlatformApplication().Get();
}


IRAWControllerInput::IRAWControllerInput(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
}



IMPLEMENT_MODULE(FRAWControllerPlugin, RAWController)

#undef LOCTEXT_NAMESPACE