#include "W_Settings_ControlEntry.h"

void UW_Settings_ControlEntry::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ActionNameText && !ActionName.IsEmpty())
	{
		ActionNameText->SetText(ActionName);
	}
}

void UW_Settings_ControlEntry::SetupEntry(FText InActionName, FKey InKey)
{
	ActionName = InActionName;
	BoundKey = InKey;

	if (ActionNameText)
	{
		ActionNameText->SetText(ActionName);
	}

	if (KeyText)
	{
		KeyText->SetText(FText::FromString(BoundKey.ToString()));
	}
}
