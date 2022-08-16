
#include "HIDInputLibrary.h"


const FKey EKeysHIDInput::HIDAxis1("MyoAccelerationX");



#define LOCTEXT_NAMESPACE "HIDInput"


void HIDInputLibrary::AddHIDInputKeys()
{
	EKeys::AddKey(FKeyDetails(EKeysHIDInput::HIDAxis1, LOCTEXT("HIDAxis1", "HID Axis 1"), FKeyDetails::FloatAxis));

}


#undef LOCTEXT_NAMESPACE

