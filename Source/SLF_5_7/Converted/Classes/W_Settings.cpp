#include "W_Settings.h"

void UW_Settings::NativeConstruct()
{
	Super::NativeConstruct();
	SwitchCategory(0);
}

void UW_Settings::SwitchCategory(int32 CategoryIndex)
{
	CurrentCategoryIndex = CategoryIndex;

	if (CategorySwitcher)
	{
		CategorySwitcher->SetActiveWidgetIndex(CategoryIndex);
	}
}

void UW_Settings::ApplySettings()
{
	// Apply all settings changes
	OnSettingsSaved.Broadcast();
}

void UW_Settings::RevertSettings()
{
	// Revert to previous settings
}

void UW_Settings::CloseSettings()
{
	OnSettingsCancelled.Broadcast();
	RemoveFromParent();
}
