#include "AC_StatManager.h"

UAC_StatManager::UAC_StatManager()
{
    PrimaryComponentTick.bCanEverTick = false;
    CurrentLevel = 1;
}

void UAC_StatManager::BeginPlay()
{
    Super::BeginPlay();
    InitializeStats();
}

void UAC_StatManager::InitializeStats()
{
    // Initialize common stats using GameplayTags.
    // In a real scenario, these tags would be defined in a DataAsset or Config.
    // For now, using loose tags for demonstration/compilation.
    
    // Example Tags: "Stat.Health", "Stat.Stamina", "Stat.Attribute.Strength", etc.
    // Ensure tags exist or are added.
    
    const TArray<FName> StatNames = {
        FName("Stat.Health"),
        FName("Stat.Stamina"),
        FName("Stat.Mana"),
        FName("Stat.Attribute.Strength"),
        FName("Stat.Attribute.Dexterity")
    };

    for (const FName& Name : StatNames)
    {
        FGameplayTag Tag = FGameplayTag::RequestGameplayTag(Name);
        if (Tag.IsValid() && !Stats.Contains(Tag))
        {
            UB_Stat* NewStat = NewObject<UB_Stat>(this);
            NewStat->Initialize(10.0f, 10.0f); // Default
            Stats.Add(Tag, NewStat);
        }
    }

    OnStatsInitialized.Broadcast();
}

UB_Stat* UAC_StatManager::GetStat(FGameplayTag StatTag)
{
    if (Stats.Contains(StatTag))
    {
        return Stats[StatTag];
    }
    return nullptr;
}

void UAC_StatManager::ModifyStat(FGameplayTag StatTag, float Value, E_ValueType ValueType)
{
    UB_Stat* Stat = GetStat(StatTag);
    if (!Stat) return;

    // Handle ValueType (Flat vs Percent)
    float Change = Value;
    if (ValueType == E_ValueType::Percentage)
    {
        Change = Stat->MaxValue * (Value / 100.0f);
    }
    
    Stat->ModifyStat(Change);
    AdjustAffectedStats(Stat, Change, ValueType);
}

void UAC_StatManager::AdjustAffectedStats(UB_Stat* Stat, float Change, E_ValueType ValueType)
{
    // Logic to update dependent stats (e.g. Vigor increases Health)
    // Needs FStatBehavior or Data Table lookup map.
    // TODO: Implement dependency graph.
}

void UAC_StatManager::AdjustLevel(int32 Delta)
{
    CurrentLevel = FMath::Max(1, CurrentLevel + Delta);
    OnLevelUpRequested.Broadcast(CurrentLevel);
}
