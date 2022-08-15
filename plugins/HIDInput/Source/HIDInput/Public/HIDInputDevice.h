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

};