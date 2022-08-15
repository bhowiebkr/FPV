#include "Templates/SharedPointer.h"
#include "RAWController.h"
#include "IInputDeviceModule.h"
#include "IInputDevice.h"

#define LOCTEXT_NAMESPACE "FRAWControllerPlugin"


// This function is called by *Application.cpp after startup to instantiate the modules InputDevice
inline TSharedPtr<class IInputDevice> FRAWControllerPlugin::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
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

IMPLEMENT_MODULE(FRAWControllerPlugin, RAWController)

/*
TSharedPtr< class IInputDevice > FKinectV2Plugin::CreateCustomHardwareInput()
{
TSharedPtr< FKinectV2CHI > KinectV2CHI(new FKinectV2CHI());
return KinectV2CHI;
}
*/
TSharedPtr< class IInputDevice > FRAWControllerPlugin::CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
{

	return MakeShareable(new RAWControllerDevice(InMessageHandler));

}


#undef LOCTEXT_NAMESPACE