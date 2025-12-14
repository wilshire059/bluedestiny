#include "AC_StatusEffectManager.h"
#include "DataAssets/PDA_StatusEffect.h"

UAC_StatusEffectManager::UAC_StatusEffectManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAC_StatusEffectManager::BeginPlay()
{
	Super::BeginPlay();
}

void UAC_StatusEffectManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Handle decay for all tracked effects
	TArray<FGameplayTag> TagsToRemove;
	for (auto& Elem : EffectBuildup)
	{
		// Decay logic would go here
	}
}

void UAC_StatusEffectManager::TryAddStatusEffect(UPDA_StatusEffect* EffectClass, int32 Rank, bool bStartBuildup, double StartAmount)
{
	if (!EffectClass) return;

	// Add buildup for this effect
	FGameplayTag EffectTag = EffectClass->Tag;
	if (bStartBuildup)
	{
		EffectBuildup.FindOrAdd(EffectTag) += StartAmount;
	}

	// Check if buildup threshold reached
	// Implementation depends on effect configuration

	OnStatusEffectChanged.Broadcast(EffectClass, true);
}

void UAC_StatusEffectManager::RemoveStatusEffect(UPDA_StatusEffect* Effect)
{
	if (!Effect) return;

	EffectBuildup.Remove(Effect->Tag);
	OnStatusEffectChanged.Broadcast(Effect, false);
}

void UAC_StatusEffectManager::AddBuildup(UPDA_StatusEffect* Effect, double Amount)
{
	if (!Effect) return;

	double& CurrentBuildup = EffectBuildup.FindOrAdd(Effect->Tag);
	CurrentBuildup += Amount;
	CurrentBuildup = FMath::Max(0.0, CurrentBuildup);

	OnStatusEffectBuildupChanged.Broadcast(Effect, CurrentBuildup, 100.0);
}

void UAC_StatusEffectManager::DecayBuildup(UPDA_StatusEffect* Effect, double Amount)
{
	if (!Effect) return;

	if (double* CurrentBuildup = EffectBuildup.Find(Effect->Tag))
	{
		*CurrentBuildup = FMath::Max(0.0, *CurrentBuildup - Amount);
		OnStatusEffectBuildupChanged.Broadcast(Effect, *CurrentBuildup, 100.0);
	}
}

double UAC_StatusEffectManager::GetBuildup(UPDA_StatusEffect* Effect) const
{
	if (!Effect) return 0.0;

	if (const double* CurrentBuildup = EffectBuildup.Find(Effect->Tag))
	{
		return *CurrentBuildup;
	}
	return 0.0;
}

bool UAC_StatusEffectManager::HasStatusEffect(UPDA_StatusEffect* Effect) const
{
	if (!Effect) return false;
	return EffectBuildup.Contains(Effect->Tag);
}

void UAC_StatusEffectManager::ClearAllEffects()
{
	ActiveEffects.Empty();
	EffectBuildup.Empty();
}
