#pragma once

#include "Modules/ModuleManager.h"
#include "HIDHandeler.h"
#include "IInputDeviceModule.h"
#include "IInputDevice.h"
#include "GenericPlatform/GenericApplicationMessageHandler.h"


/**
* See this one on a Kinect plugin:
* https://github.com/lion03/UE4-K4W-Plugin/blob/Kinect4Windows-V2-Plugin-4.2/Engine/Plugins/KinectV2/Source/KinectV2/Public/IKinectV2Plugin.h
* https://github.com/getnamo/myo-ue4/blob/master/Source/MyoPlugin/Private/FMyoInputDevice.h
* 
* /



/**
* The public interface to this module. In most cases, this interface is only public to sibling modules
* within this plugin. 
*/
class FRAWControllerPlugin : public IInputDeviceModule
{
	
	// This function is called by *Application.cpp after startup to instantiate the modules InputDevice
	virtual TSharedPtr< class IInputDevice > CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override;

	TSharedPtr< class IRAWControllerInput > RawInputDevice;

public:

	TSharedPtr< class IRAWControllerInput >& GetRawInputDevice() { return RawInputDevice; }


	// Startup/Shutdown the modules. 
	virtual void StartupModule() override;

	
	/* Loads the module and returns it. If it's already loaded it returns the exisinting loaded one. 
	*/
	static inline FRAWControllerPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked<FRAWControllerPlugin>("RAWController");
	}

	/*
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("RAWController");
	}

protected:
	// Gets the application from the slate
	FWindowsApplication* GetApplication() const;

private:
	FControllerHandeler Handler;

};