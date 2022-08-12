#include "RAWController.h"


void FRAWControllerModule::StartupModule()
{
	// register our handler
	FWindowsApplication* Application = GetApplication();

	if (Application != nullptr)
	{

		// Add the Handeler
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


IMPLEMENT_MODULE(FRAWControllerModule, RAWController)