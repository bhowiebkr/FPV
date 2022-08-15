#pragma once

#include "IInputDevice.h"

/**
* Type definition for shared pointers to instances of FMessageEndpoint.
*/
typedef TSharedPtr<class FHIDInputDevice> FHIDInputDevicePtr;

/**
* Type definition for shared references to instances of FMessageEndpoint.
*/
typedef TSharedRef<class FHIDInputDevice> FHIDInputDeviceRef;

class FHIDInputDevice : public IInputDevice, public TSharedFromThis<FHIDInputDevice>
{
public:
	/** Tick the interface (e.g. check for new controllers) */
	virtual void Tick(float DeltaTime) override;

	/** Poll for controller state and send events if needed */
	virtual void SendControllerEvents() override;

	void ParseEvents();

	virtual ~FHIDInputDevice();

private:
	friend class HIDInputPlugin;


};