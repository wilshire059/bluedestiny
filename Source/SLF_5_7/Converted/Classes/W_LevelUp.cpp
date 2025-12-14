#include "W_LevelUp.h"

void UW_LevelUp::NativeConstruct()
{
	Super::NativeConstruct();
	PendingStatUpgrades.Empty();
}

void UW_LevelUp::AddStatUpgrade(FGameplayTag StatTag)
{
	int32& Count = PendingStatUpgrades.FindOrAdd(StatTag);
	Count++;
	OnStatUpgradesChanged();
}

void UW_LevelUp::RemoveStatUpgrade(FGameplayTag StatTag)
{
	if (int32* Count = PendingStatUpgrades.Find(StatTag))
	{
		(*Count)--;
		if (*Count <= 0)
		{
			PendingStatUpgrades.Remove(StatTag);
		}
		OnStatUpgradesChanged();
	}
}

void UW_LevelUp::ConfirmLevelUp()
{
	OnLevelUpConfirmed.Broadcast();
}

void UW_LevelUp::CancelLevelUp()
{
	PendingStatUpgrades.Empty();
	OnLevelUpCancelled.Broadcast();
}

int64 UW_LevelUp::CalculateTotalCost() const
{
	// Cost calculation would use stat manager and leveling curves
	// Implemented in Blueprint for flexibility
	return 0;
}

int32 UW_LevelUp::CalculateNewLevel() const
{
	int32 TotalUpgrades = 0;
	for (const auto& Pair : PendingStatUpgrades)
	{
		TotalUpgrades += Pair.Value;
	}
	// New level = current level + total upgrades
	return TotalUpgrades;
}
