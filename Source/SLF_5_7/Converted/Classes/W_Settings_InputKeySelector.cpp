#include "W_Settings_InputKeySelector.h"

void UW_Settings_InputKeySelector::NativeConstruct()
{
	Super::NativeConstruct();

	if (KeySelector)
	{
		KeySelector->OnKeySelected.AddDynamic(this, &UW_Settings_InputKeySelector::HandleKeySelected);
	}
}

void UW_Settings_InputKeySelector::SetupKeySelector(FName InActionName, FText InDisplayName, FKey CurrentKey)
{
	ActionName = InActionName;
	ActionDisplayName = InDisplayName;

	if (ActionNameText)
	{
		ActionNameText->SetText(ActionDisplayName);
	}

	if (KeySelector)
	{
		KeySelector->SetSelectedKey(FInputChord(CurrentKey));
	}
}

void UW_Settings_InputKeySelector::HandleKeySelected(FInputChord SelectedKey)
{
	OnKeySelected.Broadcast(ActionName, SelectedKey.Key);
}
