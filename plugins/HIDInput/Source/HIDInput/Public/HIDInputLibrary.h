#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GenericPlatform/GenericApplicationMessageHandler.h"
#include "HIDInputEnum.h"
//#include "HIDInputLibrary.generated.h"

namespace HIDInputLibrary
{
	void AddHIDInputKeys();

	void BindAnalogForDevice(const int32 DeviceHandle, const FName KeyName, const int32 AxisIndex);
};