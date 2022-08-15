#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GenericPlatform/GenericApplicationMessageHandler.h"
#include "HIDInputLibrary.generated.h"

namespace HIDInputLibrary
{
	void AddHIDInputKeys();
};

// Look at the other 2 repos and not the RAW input one. THese is getting confusing using the
// raw input one because there are probably hidden shit that it's looking up and unreal engine
// documentation for c++ is total shit 

struct RAWINPUT_API FRawInputKeyNames
{
	static const FGamepadKeyNames::Type HIDInput_Axis1;
};

struct RAWINPUT_API FRawInputKeys
{
	static const FKey HIDInput_Axis1;
};

UCLASS()
class RAWINPUT_API URawInputFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

};