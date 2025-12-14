#include "W_Settings_ControlsDisplay.h"

void UW_Settings_ControlsDisplay::NativeConstruct()
{
	Super::NativeConstruct();
	SetupControlsDisplay();
}

void UW_Settings_ControlsDisplay::SetupControlsDisplay()
{
	OnSetupControls();
}
