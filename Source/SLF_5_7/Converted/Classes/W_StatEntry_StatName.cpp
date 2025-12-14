#include "W_StatEntry_StatName.h"

void UW_StatEntry_StatName::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (StatNameText && !StatDisplayName.IsEmpty())
	{
		StatNameText->SetText(StatDisplayName);
	}
}

void UW_StatEntry_StatName::SetupStatName(FGameplayTag InStatTag, FText InDisplayName)
{
	StatTag = InStatTag;
	StatDisplayName = InDisplayName;

	if (StatNameText)
	{
		StatNameText->SetText(StatDisplayName);
	}
}
