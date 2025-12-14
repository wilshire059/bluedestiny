#include "W_StatEntry_Status.h"

void UW_StatEntry_Status::SetupStatusEntry(FGameplayTag InStatTag, FText StatName, int32 StatValue)
{
	StatTag = InStatTag;

	if (StatNameText)
	{
		StatNameText->SetText(StatName);
	}

	if (StatValueText)
	{
		StatValueText->SetText(FText::AsNumber(StatValue));
	}
}

void UW_StatEntry_Status::UpdateStatValue(int32 NewValue)
{
	if (StatValueText)
	{
		StatValueText->SetText(FText::AsNumber(NewValue));
	}
}
