#include "W_CharacterSelection_StatEntry.h"

void UW_CharacterSelection_StatEntry::SetupStatEntry(FText StatName, int32 StatValue)
{
	if (StatNameText)
	{
		StatNameText->SetText(StatName);
	}

	if (StatValueText)
	{
		StatValueText->SetText(FText::AsNumber(StatValue));
	}
}
