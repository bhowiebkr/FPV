#include "RAWController.h"
#include "IInputDeviceModule.h"
#include "IInputDevice.h"

#define LOCTEXT_NAMESPACE "FRAWControllerPlugin"

const FGamepadKeyNames::Type FRawInputKeyNames::HIDController_Axis1("HIDController_Axis1");
const FKey FRawInputKeys::HIDController_Axis1(FRawInputKeyNames::HIDController_Axis1);


TSharedPtr<class IInputDevice> FRAWControllerPlugin::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	return TSharedPtr<class IInputDevice>();


}

void FRAWControllerPlugin::StartupModule()
{
	const FName NAME_GenericUSBController(TEXT("HIDController"));

	// Generic USB Controllers (Wheel, Flightstick etc.)
	EKeys::AddMenuCategoryDisplayInfo(NAME_GenericUSBController, LOCTEXT("HIDControllerSubCateogry", "HIDController"), TEXT("GraphEditor.KeyEvent_16x"));


	EKeys::AddKey(FKeyDetails(FRawInputKeys::HIDController_Axis1, LOCTEXT("GenericUSBController_Axis1", "GenericUSBController Axis 1"), FKeyDetails::GamepadKey, NAME_GenericUSBController));



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