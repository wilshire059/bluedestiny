#include "W_Settings_Entry.h"

void UW_Settings_Entry::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (SettingNameText && !SettingName.IsEmpty())
	{
		SettingNameText->SetText(SettingName);
	}
}

void UW_Settings_Entry::SetupEntry(E_SettingEntry InSettingType, FText InSettingName, float InitialValue)
{
	SettingType = InSettingType;
	SettingName = InSettingName;
	CurrentValue = InitialValue;

	if (SettingNameText)
	{
		SettingNameText->SetText(SettingName);
	}

	UpdateValue(InitialValue);
}

void UW_Settings_Entry::UpdateValue(float NewValue)
{
	CurrentValue = FMath::Clamp(NewValue, MinValue, MaxValue);

	if (SettingValueText)
	{
		SettingValueText->SetText(FText::AsNumber(FMath::RoundToInt(CurrentValue)));
	}

	OnSettingValueChanged.Broadcast(SettingType, CurrentValue);
}

void UW_Settings_Entry::IncrementValue()
{
	UpdateValue(CurrentValue + StepSize);
}

void UW_Settings_Entry::DecrementValue()
{
	UpdateValue(CurrentValue - StepSize);
}
