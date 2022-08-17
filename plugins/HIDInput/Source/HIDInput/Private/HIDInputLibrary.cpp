
#include "HIDInputLibrary.h"


const FKey EKeysHIDInput::HIDAxis1("HIDAxis1");
const FKey EKeysHIDInput::HIDAxis2("HIDAxis2");
const FKey EKeysHIDInput::HIDAxis3("HIDAxis3");
const FKey EKeysHIDInput::HIDAxis4("HIDAxis4");



#define LOCTEXT_NAMESPACE "HIDInput"


void HIDInputLibrary::AddHIDInputKeys()
{
	
	const FName NAME_HIDInput(TEXT("HIDInput"));

	EKeys::AddMenuCategoryDisplayInfo(NAME_HIDInput, LOCTEXT("HIDInputSubCateogry", "HIDInput"), TEXT("GraphEditor.KeyEvent_16x"));

	EKeys::AddKey(FKeyDetails(EKeysHIDInput::HIDAxis1, LOCTEXT("HIDAxis1", "HID Axis 1"), FKeyDetails::Axis1D, NAME_HIDInput));
	EKeys::AddKey(FKeyDetails(EKeysHIDInput::HIDAxis2, LOCTEXT("HIDAxis2", "HID Axis 2"), FKeyDetails::Axis1D, NAME_HIDInput));
	EKeys::AddKey(FKeyDetails(EKeysHIDInput::HIDAxis3, LOCTEXT("HIDAxis3", "HID Axis 3"), FKeyDetails::Axis1D, NAME_HIDInput));
	EKeys::AddKey(FKeyDetails(EKeysHIDInput::HIDAxis4, LOCTEXT("HIDAxis4", "HID Axis 4"), FKeyDetails::Axis1D, NAME_HIDInput));

}

void HIDInputLibrary::BindAnalogForDevice(const int32 DeviceHandle, const FName KeyName, const int32 AxisIndex)
{
	// Bind the data to the input key
}


#undef LOCTEXT_NAMESPACE

