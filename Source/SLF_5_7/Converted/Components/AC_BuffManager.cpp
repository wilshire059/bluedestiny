#include "AC_BuffManager.h"
#include "DataAssets/PDA_Buff.h"

UAC_BuffManager::UAC_BuffManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAC_BuffManager::BeginPlay()
{
	Super::BeginPlay();
}

void UAC_BuffManager::TryAddBuff(UPDA_Buff* Buff, int32 Rank, bool bIsLoading)
{
	if (!Buff) return;

	// Load the buff class asynchronously and create instance
	// Note: Full implementation requires B_Buff class
	OnBuffDetected.Broadcast(Buff, true);
}

void UAC_BuffManager::DelayedRemoveBuff(float DelayDuration, UPDA_Buff* Buff)
{
	if (!Buff) return;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Buff]()
	{
		RemoveBuffOfType(Buff);
	}, DelayDuration, false);
}

TArray<UObject*> UAC_BuffManager::GetBuffsWithTag(FGameplayTag Tag)
{
	TArray<UObject*> Result;
	for (UObject* BuffObj : ActiveBuffs)
	{
		// Check if buff has matching tag
		// Full implementation requires B_Buff class with BuffData property
	}
	return Result;
}

void UAC_BuffManager::RemoveAllBuffsWithTag(FGameplayTag Tag)
{
	TArray<UObject*> MatchingBuffs = GetBuffsWithTag(Tag);
	for (UObject* BuffObj : MatchingBuffs)
	{
		ActiveBuffs.Remove(BuffObj);
	}
}

void UAC_BuffManager::RemoveBuffWithTag(FGameplayTag Tag)
{
	TArray<UObject*> MatchingBuffs = GetBuffsWithTag(Tag);
	if (MatchingBuffs.Num() > 0)
	{
		ActiveBuffs.Remove(MatchingBuffs[0]);
	}
}

void UAC_BuffManager::RemoveAllBuffsOfType(UPDA_Buff* Buff)
{
	if (!Buff) return;

	// Remove all buffs matching this type
	// Full implementation requires B_Buff class
}

void UAC_BuffManager::RemoveBuffOfType(UPDA_Buff* Buff)
{
	if (!Buff) return;

	// Remove first buff matching this type
	// Full implementation requires B_Buff class
	OnBuffDetected.Broadcast(Buff, false);
}

void UAC_BuffManager::TryGrantBuffs(const FGameplayTagContainer& BuffTags)
{
	// Grant buffs based on tags
	// Full implementation would look up buff data assets by tag and call TryAddBuff
	for (const FGameplayTag& Tag : BuffTags)
	{
		// Look up and grant buff for each tag
		// This is a placeholder - full implementation would use data registry or asset manager
	}
}

void UAC_BuffManager::TryRemoveBuffs(const FGameplayTagContainer& BuffTags)
{
	// Remove buffs based on tags
	for (const FGameplayTag& Tag : BuffTags)
	{
		RemoveAllBuffsWithTag(Tag);
	}
}
