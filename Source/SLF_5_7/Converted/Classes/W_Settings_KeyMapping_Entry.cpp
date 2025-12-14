#include "W_Settings_KeyMapping_Entry.h"

void UW_Settings_KeyMapping_Entry::NativeConstruct()
{
	Super::NativeConstruct();

	if (KeyButton)
	{
		KeyButton->OnClicked.AddDynamic(this, &UW_Settings_KeyMapping_Entry::HandleButtonClicked);
	}
}

void UW_Settings_KeyMapping_Entry::SetupEntry(FName InActionName, FText InDisplayName, FKey InCurrentKey)
{
	ActionName = InActionName;
	ActionDisplayName = InDisplayName;
	CurrentKey = InCurrentKey;

	if (ActionNameText)
	{
		ActionNameText->SetText(ActionDisplayName);
	}

	UpdateKey(InCurrentKey);
}

void UW_Settings_KeyMapping_Entry::UpdateKey(FKey NewKey)
{
	CurrentKey = NewKey;

	if (KeyText)
	{
		KeyText->SetText(FText::FromString(NewKey.ToString()));
	}
}

void UW_Settings_KeyMapping_Entry::HandleButtonClicked()
{
	OnKeyMappingEntryClicked.Broadcast(ActionName);
}

void UW_Settings_KeyMapping_Entry::SetWaitingForInput(bool bWaiting)
{
	if (KeyText)
	{
		if (bWaiting)
		{
			KeyText->SetText(FText::FromString(TEXT("Press any key...")));
		}
		else
		{
			KeyText->SetText(FText::FromString(CurrentKey.ToString()));
		}
	}
}
