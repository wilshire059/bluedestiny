#include "W_StatEntry_LevelUp.h"

void UW_StatEntry_LevelUp::SetupEntry(FGameplayTag InStatTag, int32 CurrentValue, int32 NewValue, bool bCanUpgrade)
{
	StatTag = InStatTag;

	if (CurrentValueText)
	{
		CurrentValueText->SetText(FText::AsNumber(CurrentValue));
	}

	if (NewValueText)
	{
		NewValueText->SetText(FText::AsNumber(NewValue));
	}

	if (UpgradeButton)
	{
		UpgradeButton->SetIsEnabled(bCanUpgrade);
		if (!UpgradeButton->OnClicked.IsBound())
		{
			UpgradeButton->OnClicked.AddDynamic(this, &UW_StatEntry_LevelUp::HandleUpgradeClicked);
		}
	}
}

void UW_StatEntry_LevelUp::HandleUpgradeClicked()
{
	OnStatUpgradeRequested.Broadcast(StatTag);
}
