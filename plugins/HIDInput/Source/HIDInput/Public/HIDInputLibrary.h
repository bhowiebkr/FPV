#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GenericPlatform/GenericApplicationMessageHandler.h"
//#include "RAWControllerFuncLibrary.generated.h"


/*

struct RAWController_API FRawControllerKeyNames
{
	static const FGamepadKeyNames::Type GenericUSBController_Axis2;
};


struct RAWController_API FRawControllerKeys
{
	static const FKey GenericUSBController_Axis1;
};


USTRUCT(BlueprintType)
struct RAWController_API FRegisteredDeviceInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "RawInput")
	int32 Handle = 0;

	// Driver supplied device name
	UPROPERTY(BlueprintReadOnly, Category = "RawInput")
	FString DeviceName;
};



UCLASS()
class RAWController_API URAWControllerFuncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "RawController")
	static TArray<FRegisteredDeviceInfo> GetRegisteredDevices();
};

*/